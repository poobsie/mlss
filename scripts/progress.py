#!/usr/bin/env python3
from __future__ import annotations

import shutil
import subprocess
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
def worktree_files(pattern: str) -> list[Path]:
    """Return tracked and untracked, non-ignored files used by the current build."""
    output = subprocess.check_output(
        ["git", "ls-files", "--cached", "--others", "--exclude-standard", "--", pattern],
        cwd=ROOT,
        text=True,
    )
    return [ROOT / line for line in output.splitlines() if line]


def line_count(paths: list[Path]) -> int:
    return sum(len(path.read_text(encoding="utf-8").splitlines()) for path in paths)


def built_objects(c_files: list[Path]) -> list[Path]:
    """Return build objects corresponding to the current C source files."""
    objects = []
    for source in c_files:
        relative = source.relative_to(ROOT).with_suffix(".o")
        obj = ROOT / "build" / relative
        if obj.exists():
            objects.append(obj)
    return objects


def parse_function_symbols(output: str) -> dict[str, int]:
    """Parse defined FUNC symbols and sizes from arm-none-eabi-readelf output."""
    found: dict[str, int] = {}
    for line in output.splitlines():
        fields = line.split()
        if len(fields) >= 8 and fields[3] == "FUNC" and fields[6] != "UND":
            found[fields[7]] = int(fields[2], 10)
    return found


def object_function_symbols(objects: list[Path], readelf_tool: str) -> set[str]:
    names: set[str] = set()
    for obj in objects:
        output = subprocess.check_output(
            [readelf_tool, "-sW", obj], text=True
        )
        names.update(parse_function_symbols(output))
    return names


def classify_linked_symbols(
    linked: dict[str, int], c_object_names: set[str], asm_object_names: set[str]
) -> tuple[set[str], set[str]]:
    """Classify final symbols by the object kind that actually defines them."""
    linked_names = set(linked)
    linked_c = {
        name
        for name in linked_names & c_object_names
        if not name.endswith("_padding")
        and not name.startswith(("draft_", "rejected_"))
    }
    linked_asm = linked_names & asm_object_names
    overlap = linked_c & linked_asm
    if overlap:
        names = ", ".join(sorted(overlap)[:5])
        raise RuntimeError(f"symbols classified as both C and assembly: {names}")
    return linked_c, linked_asm


def linked_function_counts(c_files: list[Path], asm_files: list[Path]) -> tuple[int, int, int] | None:
    """Count linked functions from their defining build objects."""
    elf = ROOT / "mlss.elf"
    readelf_tool = shutil.which("arm-none-eabi-readelf")
    if readelf_tool is None or not elf.exists() or elf.stat().st_size == 0:
        return None
    c_objects = built_objects(c_files)
    asm_objects = built_objects(asm_files)
    if not c_objects or not asm_objects:
        return None
    c_names = object_function_symbols(c_objects, readelf_tool)
    asm_names = object_function_symbols(asm_objects, readelf_tool)
    output = subprocess.check_output(
        [readelf_tool, "-sW", elf], text=True
    )
    linked_text = parse_function_symbols(output)
    linked_c, linked_asm = classify_linked_symbols(linked_text, c_names, asm_names)
    return (
        len(linked_c),
        len(linked_asm),
        sum(linked_text[name] for name in linked_c),
    )


def main() -> None:
    c_files = worktree_files("src/*.c")
    asm_files = worktree_files("asm/*.s")
    linked_counts = linked_function_counts(c_files, asm_files)
    if linked_counts is None:
        raise SystemExit("A current linked ELF and build objects are required; run `make progress`.")
    c_functions, asm_functions, text_size = linked_counts
    total_functions = c_functions + asm_functions
    percent = 100.0 * c_functions / total_functions

    print("Decompilation progress")
    print(f"  Functions in C:         {c_functions:4d} / {total_functions} ({percent:.4f}%)")
    print(f"  Functions in assembly:  {asm_functions:4d} / {total_functions} ({100.0 - percent:.4f}%)")
    print("  Count mode:             linked object symbols")
    print(f"  Matched C .text:        {text_size:8d} bytes")
    print(f"  C source in worktree:   {len(c_files):4d} files, {line_count(c_files)} lines")


if __name__ == "__main__":
    main()
