#!/usr/bin/env python3
"""Report the persistent detangling queue and source-level uncertainty signals."""

from __future__ import annotations

import argparse
import json
import re
import sys
from dataclasses import dataclass
from pathlib import Path
from typing import Iterable


ROOT = Path(__file__).resolve().parent.parent
CONFIG = ROOT / "config" / "detangling.json"

ADDRESS_NAME = re.compile(r"\b(?:sub|nullsub|loc)_[0-9A-Fa-f]+\b")
ADDRESS_SUFFIX = re.compile(r"\b[A-Za-z_]\w*_[0-9A-Fa-f]{7,8}\b")
RAW_FIELD = re.compile(r"\b(?:field|gap)[0-9A-Fa-f_]*\b")
RAW_ACCESS = re.compile(r"\b(?:FIELD|FIELD_AT|M2C_UNK|UnknownWord)\b")
LOCAL_EXTERN = re.compile(r"^\s*extern\s+.*[;(]", re.MULTILINE)
ADDRESS_SYMBOL = re.compile(r"^(?:sub|nullsub|loc)_[0-9A-Fa-f]+$")
MAP_INPUT = re.compile(r"^\s+(src/[^\s()]+\.o)\((\.text(?:\.[^)]+)?)\)")
MAP_ANY_INPUT = re.compile(r"^\s+(?:src|asm)/[^\s()]+\.o\(")
MAP_SIZE = re.compile(
    r"^\s+(0x[0-9A-Fa-f]+)\s+(0x[0-9A-Fa-f]+)\s+src/[^\s]+\.o\s*$"
)
MAP_NAMED_SIZE = re.compile(
    r"^\s+\.text(?:\.[^\s]+)?\s+(0x[0-9A-Fa-f]+)\s+(0x[0-9A-Fa-f]+)\s+src/[^\s]+\.o\s*$"
)
MAP_SYMBOL = re.compile(r"^\s+(0x[0-9A-Fa-f]+)\s+([A-Za-z_]\w*)\s*$")
PUBLIC_ALIAS = re.compile(
    r"^\s*#define\s+([A-Za-z_]\w*)\s+((?:sub|nullsub|loc)_[0-9A-Fa-f]+)\s*$",
    re.MULTILINE,
)
NEUTRAL_MEMBER = re.compile(
    r"(?:->|\.)\s*(?:unknown[0-9A-Fa-f_]+|field_[0-9A-Fa-f_]+|"
    r"gap[0-9A-Fa-f_]+|value[0-9A-Fa-f_]+)\b",
    re.IGNORECASE,
)
RAW_ACCESSOR = re.compile(
    r"\b(?:FIELD|FIELD_AT|M2C_UNK|UnknownWord|U8AT|U16AT|U32AT|U32PTRAT)\b"
)
RAW_BYTE_OFFSET = re.compile(
    r"\(\s*(?:const\s+)?(?:u8|s8|char)\s*\*\s*\)\s*[A-Za-z_(]"
    r"[^;\n]{0,100}?(?:\+\s*(?:0x[0-9A-Fa-f]+|\d+)|\[\s*(?:0x[0-9A-Fa-f]+|\d+)\s*\])"
)


@dataclass
class Metrics:
    files: int = 0
    lines: int = 0
    address_names: int = 0
    raw_fields: int = 0
    raw_accesses: int = 0
    local_externs: int = 0

    @property
    def uncertainty(self) -> int:
        return self.address_names + self.raw_fields + self.raw_accesses + self.local_externs

    def add_source(self, text: str) -> None:
        self.files += 1
        self.lines += len(text.splitlines())
        self.address_names += len(set(ADDRESS_NAME.findall(text)) | set(ADDRESS_SUFFIX.findall(text)))
        self.raw_fields += len(set(RAW_FIELD.findall(text)))
        self.raw_accesses += len(RAW_ACCESS.findall(text))
        self.local_externs += len(LOCAL_EXTERN.findall(text))


@dataclass(frozen=True)
class LinkedFunction:
    name: str
    size: int
    source: Path


@dataclass(frozen=True)
class FunctionBody:
    name: str
    text: str


@dataclass
class DetanglingReport:
    total: int
    semantic: set[str]
    address_only: set[str]
    alias_unverified: set[str]
    alias_conflict: set[str]
    neutral_member: set[str]
    raw_object_offset: set[str]
    local_extern: set[str]
    unscanned: set[str]
    placed: set[str]
    unplaced: set[str]
    ambiguous: set[str]
    deferred: set[str]
    strict: set[str]

    def as_dict(self) -> dict:
        categories = {
            "semantic": self.semantic,
            "address_only": self.address_only,
            "alias_unverified": self.alias_unverified,
            "alias_conflict": self.alias_conflict,
            "neutral_member": self.neutral_member,
            "raw_object_offset": self.raw_object_offset,
            "local_extern": self.local_extern,
            "unscanned": self.unscanned,
            "placed": self.placed,
            "unplaced": self.unplaced,
            "ambiguous": self.ambiguous,
            "deferred": self.deferred,
            "strict_detangled": self.strict,
        }
        return {
            "schema_version": 1,
            "linked_c_functions": self.total,
            "counts": {name: len(values) for name, values in categories.items()},
            "percentages": {
                "semantic": percentage(len(self.semantic), self.total),
                "structured": percentage(
                    self.total
                    - len(self.neutral_member | self.raw_object_offset | self.unscanned),
                    self.total,
                ),
                "placement": percentage(len(self.placed), self.total),
                "strict_detangled": percentage(len(self.strict), self.total),
            },
            "symbols": {name: sorted(values) for name, values in categories.items()},
        }


def percentage(numerator: int, denominator: int) -> float:
    return round(100.0 * numerator / denominator, 4) if denominator else 0.0


def linked_c_functions_from_map(path: Path) -> list[LinkedFunction]:
    """Read linked nonzero C text input sections from a GNU linker map."""
    lines = path.read_text(encoding="utf-8", errors="replace").splitlines()
    functions: dict[str, LinkedFunction] = {}
    for index, line in enumerate(lines):
        marker = MAP_INPUT.match(line)
        if marker is None:
            continue
        address: int | None = None
        section_size: int | None = None
        for following in lines[index + 1 : index + 5]:
            size_match = MAP_SIZE.match(following) or MAP_NAMED_SIZE.match(following)
            if size_match is not None:
                address = int(size_match.group(1), 16)
                section_size = int(size_match.group(2), 16)
                break
        if (
            not section_size
            or address is None
            or not 0x08000000 <= address < 0x0A000000
        ):
            continue
        source = Path(marker.group(1)[:-2] + ".c")
        section_end = address + section_size
        section_symbols: list[tuple[int, str]] = []
        for following in lines[index + 1 :]:
            if MAP_ANY_INPUT.match(following):
                break
            symbol_match = MAP_SYMBOL.match(following)
            if symbol_match is None:
                continue
            symbol_address = int(symbol_match.group(1), 16)
            if address <= symbol_address <= section_end:
                section_symbols.append((symbol_address, symbol_match.group(2)))
        for symbol_index, (symbol_address, symbol) in enumerate(section_symbols):
            if symbol.endswith("_padding") or symbol.startswith(("draft_", "rejected_")):
                continue
            later_addresses = [
                later_address
                for later_address, _ in section_symbols[symbol_index + 1 :]
                if later_address > symbol_address
            ]
            symbol_end = min(later_addresses, default=section_end)
            size = symbol_end - symbol_address
            if not size:
                continue
            if symbol in functions:
                raise ValueError(f"duplicate linked C symbol in map: {symbol}")
            functions[symbol] = LinkedFunction(symbol, size, source)
    if not functions:
        raise ValueError(f"no linked C functions found in {path}")
    return [functions[name] for name in sorted(functions)]


def mask_comments_and_literals(text: str) -> str:
    """Replace comments and literals with spaces while preserving newlines."""
    result = list(text)
    index = 0
    while index < len(result):
        if index + 1 < len(result) and result[index] == "/" and result[index + 1] == "/":
            end = text.find("\n", index + 2)
            end = len(text) if end < 0 else end
            for offset in range(index, end):
                result[offset] = " "
            index = end
        elif index + 1 < len(result) and result[index] == "/" and result[index + 1] == "*":
            end = text.find("*/", index + 2)
            end = len(text) - 2 if end < 0 else end
            for offset in range(index, min(end + 2, len(result))):
                if result[offset] != "\n":
                    result[offset] = " "
            index = end + 2
        elif result[index] in {'"', "'"}:
            quote = result[index]
            result[index] = " "
            index += 1
            while index < len(result):
                if result[index] == "\\":
                    result[index] = " "
                    if index + 1 < len(result) and result[index + 1] != "\n":
                        result[index + 1] = " "
                    index += 2
                elif result[index] == quote:
                    result[index] = " "
                    index += 1
                    break
                else:
                    if result[index] != "\n":
                        result[index] = " "
                    index += 1
        else:
            index += 1
    return "".join(result)


def mask_preprocessor(text: str) -> str:
    result: list[str] = []
    continuation = False
    for line in text.splitlines(keepends=True):
        directive = continuation or line.lstrip().startswith("#")
        continuation = directive and line.rstrip("\r\n").rstrip().endswith("\\")
        if directive:
            result.append(
                "".join(
                    "\n" if char == "\n" else "\r" if char == "\r" else " "
                    for char in line
                )
            )
        else:
            result.append(line)
    return "".join(result)


def matching_delimiter(text: str, start: int, opening: str, closing: str) -> int | None:
    depth = 0
    for index in range(start, len(text)):
        if text[index] == opening:
            depth += 1
        elif text[index] == closing:
            depth -= 1
            if depth == 0:
                return index
    return None


def function_bodies(text: str) -> dict[str, list[FunctionBody]]:
    """Find direct, file-scope C function definitions in unpreprocessed source."""
    clean = mask_preprocessor(mask_comments_and_literals(text))
    found: dict[str, list[FunctionBody]] = {}
    depth = 0
    index = 0
    identifier = re.compile(r"\b([A-Za-z_]\w*)\s*\(")
    controls = {"if", "for", "while", "switch", "sizeof", "return"}
    while index < len(clean):
        if clean[index] == "{":
            depth += 1
            index += 1
            continue
        if clean[index] == "}":
            depth = max(0, depth - 1)
            index += 1
            continue
        if depth:
            index += 1
            continue
        match = identifier.search(clean, index)
        if match is None:
            break
        index = match.end()
        name = match.group(1)
        if name in controls:
            continue
        opening = clean.find("(", match.start(1) + len(name))
        closing = matching_delimiter(clean, opening, "(", ")")
        if closing is None:
            break
        after = closing + 1
        while after < len(clean) and clean[after].isspace():
            after += 1
        if after >= len(clean) or clean[after] != "{":
            index = closing + 1
            continue
        body_end = matching_delimiter(clean, after, "{", "}")
        if body_end is None:
            break
        body = FunctionBody(name, clean[after : body_end + 1])
        found.setdefault(name, []).append(body)
        index = body_end + 1
    return found


def public_aliases(headers: Iterable[Path]) -> tuple[dict[str, set[str]], set[str]]:
    aliases: dict[str, set[str]] = {}
    prototypes: set[str] = set()
    identifier = re.compile(r"\b([A-Za-z_]\w*)\s*\(")
    for header in headers:
        text = header.read_text(encoding="utf-8")
        for match in PUBLIC_ALIAS.finditer(text):
            aliases.setdefault(match.group(2), set()).add(match.group(1))
        clean = mask_preprocessor(mask_comments_and_literals(text))
        for match in identifier.finditer(clean):
            opening = clean.find("(", match.start(1) + len(match.group(1)))
            closing = matching_delimiter(clean, opening, "(", ")")
            if closing is None:
                continue
            after = closing + 1
            while after < len(clean) and clean[after].isspace():
                after += 1
            if after < len(clean) and clean[after] == ";":
                prototypes.add(match.group(1))
    return aliases, prototypes


def subsystem_file_sets(root: Path, subsystems: list[dict]) -> dict[str, set[Path]]:
    result: dict[str, set[Path]] = {}
    for item in subsystems:
        if item["id"] == "unclassified":
            continue
        paths: set[Path] = set()
        for pattern in item["patterns"]:
            paths.update(
                path.relative_to(root)
                for path in root.glob(pattern)
                if path.suffix == ".c"
            )
        result[item["id"]] = paths
    return result


def detangling_report(root: Path, map_path: Path, subsystems: list[dict]) -> DetanglingReport:
    inventory = linked_c_functions_from_map(map_path)
    aliases, prototypes = public_aliases(sorted((root / "include").rglob("*.h")))
    subsystem_paths = subsystem_file_sets(root, subsystems)
    states = {item["id"]: item["state"] for item in subsystems}
    source_bodies: dict[Path, dict[str, list[FunctionBody]]] = {}

    semantic: set[str] = set()
    address_only: set[str] = set()
    alias_unverified: set[str] = set()
    alias_conflict: set[str] = set()
    neutral_member: set[str] = set()
    raw_object_offset: set[str] = set()
    local_extern: set[str] = set()
    unscanned: set[str] = set()
    placed: set[str] = set()
    unplaced: set[str] = set()
    ambiguous: set[str] = set()
    deferred: set[str] = set()

    for function in inventory:
        source_path = root / function.source
        if not source_path.is_file():
            raise ValueError(f"linked C source is missing: {function.source}")
        if function.source not in source_bodies:
            source_bodies[function.source] = function_bodies(
                source_path.read_text(encoding="utf-8")
            )
        bodies = source_bodies[function.source]

        definition_names: list[str] = []
        if ADDRESS_SYMBOL.fullmatch(function.name):
            candidates = sorted(aliases.get(function.name, set()))
            associated = [name for name in candidates if len(bodies.get(name, [])) == 1]
            qualified = [
                name for name in candidates
                if name in prototypes and len(bodies.get(name, [])) == 1
            ]
            if len(qualified) == 1 and len(candidates) == 1:
                semantic.add(function.name)
                definition_names = qualified
            else:
                address_only.add(function.name)
                if candidates:
                    alias_unverified.add(function.name)
                if len(candidates) > 1 or len(qualified) > 1:
                    alias_conflict.add(function.name)
                if len(associated) == 1 and len(candidates) == 1:
                    definition_names = associated
                elif len(bodies.get(function.name, [])) == 1:
                    definition_names = [function.name]
        elif function.name in prototypes and len(bodies.get(function.name, [])) == 1:
            semantic.add(function.name)
            definition_names = [function.name]
        else:
            address_only.add(function.name)
            if len(bodies.get(function.name, [])) == 1:
                definition_names = [function.name]

        if len(definition_names) != 1:
            unscanned.add(function.name)
        else:
            body = bodies[definition_names[0]][0].text
            if NEUTRAL_MEMBER.search(body):
                neutral_member.add(function.name)
            if RAW_ACCESSOR.search(body) or RAW_BYTE_OFFSET.search(body):
                raw_object_offset.add(function.name)
            if LOCAL_EXTERN.search(body):
                local_extern.add(function.name)

        matches = [
            subsystem for subsystem, paths in subsystem_paths.items()
            if function.source in paths
        ]
        if len(matches) == 1:
            placed.add(function.name)
            if states[matches[0]] == "deferred":
                deferred.add(function.name)
        elif not matches:
            unplaced.add(function.name)
        else:
            ambiguous.add(function.name)

    all_names = {function.name for function in inventory}
    structured = all_names - neutral_member - raw_object_offset - unscanned
    strict = semantic & structured & placed
    return DetanglingReport(
        len(inventory), semantic, address_only, alias_unverified, alias_conflict,
        neutral_member, raw_object_offset, local_extern, unscanned, placed,
        unplaced, ambiguous, deferred, strict,
    )


def load_config() -> dict:
    data = json.loads(CONFIG.read_text(encoding="utf-8"))
    if data.get("version") != 1 or not isinstance(data.get("subsystems"), list):
        raise SystemExit(f"unsupported detangling config: {CONFIG}")
    return data


def matching_files(patterns: list[str]) -> list[Path]:
    found: set[Path] = set()
    for pattern in patterns:
        found.update(path for path in ROOT.glob(pattern) if path.suffix == ".c")
    return sorted(found)


def measure(files: list[Path]) -> Metrics:
    result = Metrics()
    for path in files:
        result.add_source(path.read_text(encoding="utf-8"))
    return result


def partition_files(subsystems: list[dict]) -> dict[str, list[Path]]:
    """Assign each source file to the first matching subsystem exactly once."""
    claimed: set[Path] = set()
    assignments: dict[str, list[Path]] = {}
    for item in subsystems:
        files = [path for path in matching_files(item["patterns"]) if path not in claimed]
        assignments[item["id"]] = files
        claimed.update(files)
    return assignments


def next_subsystem(subsystems: list[dict]) -> dict | None:
    active = [item for item in subsystems if item["state"] == "active"]
    if active:
        return active[0]
    queued = [item for item in subsystems if item["state"] == "queued"]
    return queued[0] if queued else None


def acceptance_errors(subsystems: list[dict], assignments: dict[str, list[Path]]) -> list[str]:
    """Return queue conditions that prevent accepting a decompilation slice."""
    errors: list[str] = []
    for item in subsystems:
        state = item["state"]
        files = assignments[item["id"]]
        if state in {"active", "queued"}:
            errors.append(f"{item['id']} is still {state}")
        if item["id"] == "unclassified" and files:
            relative = ", ".join(str(path.relative_to(ROOT)) for path in files)
            errors.append(f"unclassified source remains: {relative}")
        if state == "deferred" and not item.get("next_action", "").strip():
            errors.append(f"{item['id']} is deferred without a concrete next action")
    return errors


def print_summary(subsystems: list[dict], assignments: dict[str, list[Path]]) -> None:
    header = f"{'state':10} {'subsystem':18} {'files':>5} {'lines':>7} {'unknown':>8}  next action"
    print(header)
    print("-" * len(header))
    for item in subsystems:
        metrics = measure(assignments[item["id"]])
        print(
            f"{item['state']:10} {item['id']:18} {metrics.files:5d} "
            f"{metrics.lines:7d} {metrics.uncertainty:8d}  {item['next_action']}"
        )


def print_next(subsystems: list[dict], assignments: dict[str, list[Path]]) -> None:
    item = next_subsystem(subsystems)
    if item is None:
        print("No active or queued subsystem remains.")
        return
    metrics = measure(assignments[item["id"]])
    print(item["id"])
    print(f"  state: {item['state']}")
    print(f"  source files: {metrics.files}")
    print(f"  source lines: {metrics.lines}")
    print(f"  uncertainty signals: {metrics.uncertainty}")
    print(f"  action: {item['next_action']}")
    print(f"  documentation: {item['documentation']}")


def check_acceptance(subsystems: list[dict], assignments: dict[str, list[Path]]) -> None:
    errors = acceptance_errors(subsystems, assignments)
    if errors:
        for error in errors:
            print(f"error: {error}", file=sys.stderr)
        raise SystemExit(1)
    print("Detangling acceptance: OK")


def print_metrics(report: DetanglingReport, json_output: bool) -> None:
    data = report.as_dict()
    if json_output:
        print(json.dumps(data, indent=2, sort_keys=True))
        return
    counts = data["counts"]
    percents = data["percentages"]
    structured = report.total - len(
        report.neutral_member | report.raw_object_offset | report.unscanned
    )
    print("Detangling metrics")
    print(f"  Linked C functions:     {report.total:4d}")
    print(
        f"  Semantic API:          {counts['semantic']:4d} / {report.total} "
        f"({percents['semantic']:.4f}%)"
    )
    print(
        f"  Structured access:     {structured:4d} / {report.total} "
        f"({percents['structured']:.4f}%)"
    )
    print(
        f"  Unique placement:      {counts['placed']:4d} / {report.total} "
        f"({percents['placement']:.4f}%)"
    )
    print(
        f"  Strict detangled:      {counts['strict_detangled']:4d} / {report.total} "
        f"({percents['strict_detangled']:.4f}%)"
    )
    print("  Debt (functions, categories may overlap)")
    print(f"    address only:        {counts['address_only']:4d}")
    print(f"    alias unverified:    {counts['alias_unverified']:4d}")
    print(f"    alias conflicts:     {counts['alias_conflict']:4d}")
    print(f"    neutral members:     {counts['neutral_member']:4d}")
    print(f"    raw object offsets:  {counts['raw_object_offset']:4d}")
    print(f"    local externs:       {counts['local_extern']:4d}")
    print(f"    unscanned bodies:    {counts['unscanned']:4d}")
    print(f"    unplaced:            {counts['unplaced']:4d}")
    print(f"    ambiguous placement: {counts['ambiguous']:4d}")
    print(f"    deferred:            {counts['deferred']:4d}")


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "command", nargs="?", choices=("summary", "next", "check", "metrics"), default="summary"
    )
    parser.add_argument("--json", action="store_true", help="emit machine-readable metrics")
    parser.add_argument("--map", type=Path, default=ROOT / "mlss.map", help="linked GNU map")
    args = parser.parse_args()
    subsystems = load_config()["subsystems"]
    assignments = partition_files(subsystems)
    if args.command == "next":
        print_next(subsystems, assignments)
    elif args.command == "check":
        check_acceptance(subsystems, assignments)
    elif args.command == "metrics":
        if not args.map.is_file():
            raise SystemExit(f"linked map is required: {args.map}")
        print_metrics(detangling_report(ROOT, args.map, subsystems), args.json)
    else:
        print_summary(subsystems, assignments)


if __name__ == "__main__":
    main()
