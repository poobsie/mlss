#!/usr/bin/env python3
"""Verify every linked C function directly against the reference ROM."""

from __future__ import annotations

import argparse
import shutil
import subprocess
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent


def symbols(path: Path) -> dict[str, tuple[int, int]]:
    nm = shutil.which("arm-none-eabi-nm")
    if nm is None:
        raise SystemExit("arm-none-eabi-nm is not available")
    output = subprocess.check_output(
        [nm, "-S", "--defined-only", str(path)], text=True
    )
    found: dict[str, tuple[int, int]] = {}
    for line in output.splitlines():
        fields = line.split()
        if len(fields) >= 4 and fields[2] in {"T", "t"}:
            found[fields[3]] = (int(fields[0], 16), int(fields[1], 16))
    return found


def current_c_objects() -> list[Path]:
    """Return existing objects for source files present in the current tree."""
    objects = []
    for source in (ROOT / "src").rglob("*.c"):
        relative = source.relative_to(ROOT).with_suffix(".o")
        obj = ROOT / "build" / relative
        if obj.exists():
            objects.append(obj)
    return sorted(objects)


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--reference", default=".decomp-tools/reference/mlss.gba"
    )
    parser.add_argument("--elf", default="mlss.elf")
    args = parser.parse_args()

    reference_path = ROOT / args.reference
    elf_path = ROOT / args.elf
    if not reference_path.exists() or not elf_path.exists():
        raise SystemExit("reference ROM and linked ELF are required")

    object_symbols: set[str] = set()
    for obj in current_c_objects():
        object_symbols.update(symbols(obj))

    linked = symbols(elf_path)
    reference = reference_path.read_bytes()
    built = (ROOT / "mlss.gba").read_bytes()
    mismatches: list[tuple[int, int, str]] = []
    checked = 0
    for name in sorted(object_symbols & linked.keys()):
        if name.endswith("_padding") or name.startswith(("draft_", "rejected_")):
            continue
        address, size = linked[name]
        if size == 0 or not 0x08000000 <= address < 0x0A000000:
            continue
        offset = address - 0x08000000
        checked += 1
        if built[offset : offset + size] != reference[offset : offset + size]:
            mismatches.append((address, size, name))

    print(f"Linked C functions checked: {checked}")
    print(f"Exact functions:          {checked - len(mismatches)}")
    print(f"Mismatched functions:     {len(mismatches)}")
    for address, size, name in mismatches:
        print(f"  0x{address:08X} {size:4d} {name}")
    raise SystemExit(1 if mismatches else 0)


if __name__ == "__main__":
    main()
