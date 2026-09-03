#!/usr/bin/env python3
"""Create small, reproducible work packets for matching decompilation."""

from __future__ import annotations

import argparse
import json
import re
import subprocess
import sys
import tempfile
from dataclasses import asdict, dataclass
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
FUNCTION_START = re.compile(
    r"^\s*(?P<mode>thumb|arm)_func_start\s+(?P<name>\S+)", re.MULTILINE
)
MAP_SYMBOL = re.compile(r"^\s*(0x[0-9a-fA-F]+)\s+(\S+)\s*$")
CALL = re.compile(r"^\s*blx?\s+(\S+)", re.MULTILINE)
BRANCH = re.compile(r"^\s*b(?:eq|ne|gt|ge|lt|le|hi|hs|lo|ls|cc|cs|mi|pl|vs|vc)\s+", re.MULTILINE)
BYTE = re.compile(r"\.byte\s+(.+)$", re.MULTILINE)
SWI = re.compile(r"^\s*swi\s+", re.MULTILINE)
INSTRUCTION = re.compile(r"^\s*([a-z][a-z0-9.]*)\s+", re.MULTILINE)
DISABLED_IF = re.compile(r"^\s*\.if\s+0(?:\s|$)")
ASSEMBLER_IF = re.compile(r"^\s*\.if(?:n?def|c|nc|eq|ne|gt|ge|lt|le|b|nb)?(?:\s|$)")
ASSEMBLER_ENDIF = re.compile(r"^\s*\.endif(?:\s|$)")


@dataclass(frozen=True)
class Candidate:
    name: str
    mode: str
    source: str
    start_line: int
    end_line: int
    address: int
    size: int
    calls: int
    branches: int
    raw_bytes: int
    repeated_shape: int
    score: int

    @property
    def address_hex(self) -> str:
        return f"0x{self.address:08X}"


def git_tracked_assembly() -> list[Path]:
    output = subprocess.check_output(
        ["git", "ls-files", "asm/*.s"], cwd=ROOT, text=True
    )
    return [ROOT / line for line in output.splitlines()]


def map_addresses(path: Path) -> dict[str, int]:
    addresses: dict[str, int] = {}
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        match = MAP_SYMBOL.match(line)
        if match:
            addresses.setdefault(match.group(2), int(match.group(1), 16))
    return addresses


def function_blocks(path: Path) -> list[tuple[str, str, int, int, str]]:
    source = path.read_text(encoding="utf-8", errors="replace")
    lines = source.splitlines(keepends=True)
    active_lines: list[str] = []
    disabled_depth = 0
    for line in lines:
        if disabled_depth:
            if ASSEMBLER_IF.match(line):
                disabled_depth += 1
            elif ASSEMBLER_ENDIF.match(line):
                disabled_depth -= 1
            active_lines.append("\n" if line.endswith("\n") else "")
            continue
        if DISABLED_IF.match(line):
            disabled_depth = 1
            active_lines.append("\n" if line.endswith("\n") else "")
        else:
            active_lines.append(line)

    starts: list[tuple[str, str, int]] = []
    for index, line in enumerate(active_lines):
        match = FUNCTION_START.match(line)
        if match:
            starts.append((match.group("name"), match.group("mode"), index))

    blocks = []
    for position, (name, mode, start) in enumerate(starts):
        end = starts[position + 1][2] if position + 1 < len(starts) else len(lines)
        blocks.append((name, mode, start + 1, end, "".join(active_lines[start:end])))
    return blocks


def shape(block: str) -> str:
    mnemonics = []
    for line in block.splitlines():
        stripped = line.split("@", 1)[0].strip()
        if not stripped or stripped.endswith(":") or "func_start" in stripped:
            continue
        match = INSTRUCTION.match(stripped)
        if match and not match.group(1).startswith("."):
            mnemonics.append(match.group(1))
        elif stripped.startswith(".byte"):
            mnemonics.append(".byte")
    return " ".join(mnemonics)


def raw_byte_count(block: str) -> int:
    return sum(len(match.group(1).split(",")) for match in BYTE.finditer(block))


def discover(map_path: Path, assembly: list[Path]) -> list[Candidate]:
    addresses = map_addresses(map_path)
    parsed: list[tuple[Path, str, str, int, int, str]] = []
    shape_counts: dict[str, int] = {}
    for path in assembly:
        for name, mode, start, end, block in function_blocks(path):
            if (
                name not in addresses
                or SWI.search(block)
                or name.startswith(("_call_via_", "__"))
            ):
                continue
            parsed.append((path, name, mode, start, end, block))
            block_shape = shape(block)
            shape_counts[block_shape] = shape_counts.get(block_shape, 0) + 1

    by_source: dict[Path, list[tuple[str, str, int, int, str]]] = {}
    for path, name, mode, start, end, block in parsed:
        by_source.setdefault(path, []).append((name, mode, start, end, block))

    candidates: list[Candidate] = []
    for path, blocks in by_source.items():
        for index, (name, mode, start, end, block) in enumerate(blocks):
            address = addresses[name]
            if index + 1 >= len(blocks):
                continue
            next_address = addresses[blocks[index + 1][0]]
            size = next_address - address
            if size <= 0:
                continue
            calls = len(CALL.findall(block))
            branches = len(BRANCH.findall(block))
            raw_bytes = raw_byte_count(block)
            repeats = shape_counts.get(shape(block), 1)
            score = size + calls * 24 + branches * 10 + raw_bytes * 2 - min(repeats, 10) * 3
            candidates.append(
                Candidate(
                    name=name,
                    mode=mode,
                    source=str(path.relative_to(ROOT)).replace("\\", "/"),
                    start_line=start,
                    end_line=end,
                    address=address,
                    size=size,
                    calls=calls,
                    branches=branches,
                    raw_bytes=raw_bytes,
                    repeated_shape=repeats,
                    score=score,
                )
            )
    return candidates


def selected_candidates(args: argparse.Namespace) -> list[Candidate]:
    map_path = ROOT / args.map
    if not map_path.exists():
        raise SystemExit(f"Missing {map_path}. Build the project first.")
    assembly = [ROOT / args.asm] if args.asm else git_tracked_assembly()
    candidates = discover(map_path, assembly)
    candidates = [item for item in candidates if item.size <= args.max_bytes]
    candidates.sort(key=lambda item: (item.score, item.size, item.address))
    return candidates[: args.limit]


def candidate_by_name(name: str, map_path: Path) -> tuple[Candidate, str]:
    candidates = discover(map_path, git_tracked_assembly())
    for candidate in candidates:
        if candidate.name == name:
            path = ROOT / candidate.source
            for block_name, _, _, _, block in function_blocks(path):
                if block_name == name:
                    return candidate, block
    raise SystemExit(f"Assembly function not found: {name}")


def assembly_context(name: str) -> tuple[list[str], list[str]]:
    """Return active assembly callers and adjacent functions for a symbol."""
    callers: set[str] = set()
    neighbors: list[str] = []
    for path in git_tracked_assembly():
        blocks = function_blocks(path)
        for index, (block_name, _, _, _, block) in enumerate(blocks):
            if name in CALL.findall(block):
                callers.add(block_name)
            if block_name == name:
                if index:
                    neighbors.append(blocks[index - 1][0])
                if index + 1 < len(blocks):
                    neighbors.append(blocks[index + 1][0])
    return sorted(callers), neighbors


def m2c_draft(candidate: Candidate, block: str) -> str:
    executable = ROOT / ".decomp-tools" / "venv" / "bin" / "m2c"
    if not executable.exists():
        return "(m2c unavailable; run scripts/setup-tools.sh)"
    with tempfile.NamedTemporaryFile(
        mode="w", suffix=".s", encoding="utf-8", delete=False
    ) as temporary:
        temporary.write("\t.syntax unified\n\t.text\n")
        temporary.write(block)
        temporary_path = Path(temporary.name)
    command = [
        str(executable),
        "--target",
        "gba",
        "--function",
        candidate.name,
        "--valid-syntax",
        str(temporary_path),
    ]
    if sys.platform == "win32":
        def wsl_path(path: Path) -> str:
            resolved = str(path.resolve())
            if len(resolved) < 3 or resolved[1:3] != ":\\":
                raise ValueError(f"cannot translate Windows path: {resolved}")
            drive = resolved[0].lower()
            relative = resolved[3:].replace("\\", "/")
            return f"/mnt/{drive}/{relative}"

        try:
            linux_executable = wsl_path(executable)
            linux_temporary = wsl_path(temporary_path)
            command = [
                "wsl",
                "--",
                linux_executable,
                "--target",
                "gba",
                "--function",
                candidate.name,
                "--valid-syntax",
                linux_temporary,
            ]
        except (OSError, ValueError) as error:
            temporary_path.unlink(missing_ok=True)
            return f"(m2c unavailable through WSL: {error})"
    try:
        result = subprocess.run(command, cwd=ROOT, text=True, capture_output=True)
    finally:
        temporary_path.unlink(missing_ok=True)
    if result.returncode:
        detail = result.stderr.strip() or result.stdout.strip() or f"exit {result.returncode}"
        return f"(m2c failed: {detail})"
    return result.stdout.strip()


def render_packet(name: str, map_name: str, rom_name: str, include_m2c: bool) -> str:
    candidate, block = candidate_by_name(name, ROOT / map_name)
    rom_path = ROOT / rom_name
    if not rom_path.exists():
        raise SystemExit(f"Missing {rom_path}. Build the exact ROM first.")
    offset = candidate.address - 0x08000000
    rom = rom_path.read_bytes()
    if offset < 0 or offset + candidate.size > len(rom):
        raise SystemExit(f"{candidate.address_hex} is outside {rom_path.name}")
    target = rom[offset : offset + candidate.size].hex(" ")
    calls = sorted(set(CALL.findall(block)))
    callers, neighbors = assembly_context(name)
    draft = m2c_draft(candidate, block) if include_m2c else "(omitted)"
    return f"""# Matching-decompilation packet

Function: `{candidate.name}`
Address: `{candidate.address_hex}`
Size: `{candidate.size}` bytes
Source: `{candidate.source}:{candidate.start_line}`
Assembly callers: `{', '.join(callers) if callers else 'none found'}`
Callees: `{', '.join(calls) if calls else 'none'}`
Adjacent functions: `{', '.join(neighbors) if neighbors else 'none'}`
Target bytes: `{target}`

## Assembly

```asm
{block.rstrip()}
```

## m2c draft

```c
{draft}
```

## Contract

Matching and detangling are one acceptance unit. Inspect the listed callers,
callees, adjacent functions, shared data, and existing C interfaces before editing.
Classify the function into a defensible subsystem and use its canonical source file
and header. Do not create a root-level holding file. Keep an address-based name or
raw field offset when the available evidence does not support a semantic name, and
record that uncertainty explicitly.

The assigned address range is the write boundary. If a caller-connected family is
needed to recover a sound interface, report the proposed expansion instead of
editing outside that boundary. Compile with the repository's pinned agbcc, compare
the linked bytes against the target bytes above, and reject any mismatch. A raw m2c
translation, an exact function in an unclassified file, or a semantic rename without
evidence is incomplete.

Report: functions, subsystem, evidence, semantic_names, retained_unknowns,
shared_interfaces, exact_match, byte_count, changed_files, and follow_up.
"""


def token_count(text: str, encoding_name: str) -> int:
    try:
        import tiktoken
    except ImportError as error:
        raise SystemExit(
            "tiktoken is missing. Run scripts/setup-tools.sh before benchmarking."
        ) from error
    return len(tiktoken.get_encoding(encoding_name).encode(text))


def scan_command(args: argparse.Namespace) -> None:
    candidates = selected_candidates(args)
    if args.json:
        print(json.dumps([{**asdict(item), "address_hex": item.address_hex} for item in candidates], indent=2))
        return
    print("address     bytes score repeats calls branches source:line function")
    for item in candidates:
        print(
            f"{item.address_hex} {item.size:5d} {item.score:5d} {item.repeated_shape:7d} "
            f"{item.calls:5d} {item.branches:8d} {item.source}:{item.start_line} {item.name}"
        )


def packet_command(args: argparse.Namespace) -> None:
    packet = render_packet(args.function, args.map, args.rom, not args.no_m2c)
    if args.output:
        output = ROOT / args.output
        output.parent.mkdir(parents=True, exist_ok=True)
        output.write_text(packet, encoding="utf-8")
        print(output)
    else:
        print(packet, end="")


def benchmark_command(args: argparse.Namespace) -> None:
    candidate, _ = candidate_by_name(args.function, ROOT / args.map)
    packet = render_packet(args.function, args.map, args.rom, not args.no_m2c)
    full_source = (ROOT / candidate.source).read_text(encoding="utf-8", errors="replace")
    source_lines = full_source.splitlines(keepends=True)
    half_window = args.window_lines // 2
    window_start = max(0, candidate.start_line - 1 - half_window)
    window_end = min(len(source_lines), window_start + args.window_lines)
    local_window = "".join(source_lines[window_start:window_end])
    full_tokens = token_count(full_source, args.encoding)
    window_tokens = token_count(local_window, args.encoding)
    packet_tokens = token_count(packet, args.encoding)
    saved = full_tokens - packet_tokens
    reduction = 100.0 * saved / full_tokens
    window_saved = window_tokens - packet_tokens
    window_reduction = 100.0 * window_saved / window_tokens
    result = {
        "function": args.function,
        "encoding": args.encoding,
        "baseline": "entire assembly source file",
        "full_file_tokens": full_tokens,
        "local_window_lines": args.window_lines,
        "local_window_tokens": window_tokens,
        "packet_tokens": packet_tokens,
        "tokens_saved": saved,
        "reduction_percent": round(reduction, 4),
        "window_tokens_saved": window_saved,
        "window_reduction_percent": round(window_reduction, 4),
    }
    if args.json:
        print(json.dumps(result, indent=2))
    else:
        print(f"Function:          {args.function}")
        print(f"Tokenizer:         {args.encoding}")
        print(f"Full-file tokens:  {full_tokens:,}")
        print(f"{args.window_lines}-line tokens:   {window_tokens:,}")
        print(f"Packet tokens:     {packet_tokens:,}")
        print(f"Tokens saved:      {saved:,}")
        print(f"Full reduction:    {reduction:.4f}%")
        print(f"Window reduction:  {window_reduction:.4f}%")


def parser() -> argparse.ArgumentParser:
    result = argparse.ArgumentParser(description=__doc__)
    subparsers = result.add_subparsers(dest="command", required=True)

    scan = subparsers.add_parser("scan", help="rank compact assembly candidates")
    scan.add_argument("--map", default="mlss.map")
    scan.add_argument("--asm", help="limit scanning to one assembly file")
    scan.add_argument("--max-bytes", type=int, default=96)
    scan.add_argument("--limit", type=int, default=25)
    scan.add_argument("--json", action="store_true")
    scan.set_defaults(handler=scan_command)

    packet = subparsers.add_parser("packet", help="emit one compact worker packet")
    packet.add_argument("function")
    packet.add_argument("--map", default="mlss.map")
    packet.add_argument("--rom", default="mlss.gba")
    packet.add_argument("--output")
    packet.add_argument("--no-m2c", action="store_true")
    packet.set_defaults(handler=packet_command)

    benchmark = subparsers.add_parser("benchmark", help="measure packet token reduction")
    benchmark.add_argument("function")
    benchmark.add_argument("--map", default="mlss.map")
    benchmark.add_argument("--rom", default="mlss.gba")
    benchmark.add_argument("--encoding", default="o200k_base")
    benchmark.add_argument("--window-lines", type=int, default=200)
    benchmark.add_argument("--no-m2c", action="store_true")
    benchmark.add_argument("--json", action="store_true")
    benchmark.set_defaults(handler=benchmark_command)
    return result


def main() -> None:
    args = parser().parse_args()
    args.handler(args)


if __name__ == "__main__":
    main()
