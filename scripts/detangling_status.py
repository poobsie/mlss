#!/usr/bin/env python3
"""Report the persistent detangling queue and source-level uncertainty signals."""

from __future__ import annotations

import argparse
import json
import re
import sys
from dataclasses import dataclass
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
CONFIG = ROOT / "config" / "detangling.json"

ADDRESS_NAME = re.compile(r"\b(?:sub|nullsub|loc)_[0-9A-Fa-f]+\b")
ADDRESS_SUFFIX = re.compile(r"\b[A-Za-z_]\w*_[0-9A-Fa-f]{7,8}\b")
RAW_FIELD = re.compile(r"\b(?:field|gap)[0-9A-Fa-f_]*\b")
RAW_ACCESS = re.compile(r"\b(?:FIELD|FIELD_AT|M2C_UNK|UnknownWord)\b")
LOCAL_EXTERN = re.compile(r"^\s*extern\s+.*[;(]", re.MULTILINE)


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


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "command", nargs="?", choices=("summary", "next", "check"), default="summary"
    )
    args = parser.parse_args()
    subsystems = load_config()["subsystems"]
    assignments = partition_files(subsystems)
    if args.command == "next":
        print_next(subsystems, assignments)
    elif args.command == "check":
        check_acceptance(subsystems, assignments)
    else:
        print_summary(subsystems, assignments)


if __name__ == "__main__":
    main()
