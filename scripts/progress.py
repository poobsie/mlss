#!/usr/bin/env python3
from __future__ import annotations

import argparse
import re
import shutil
import subprocess
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
C_FUNCTION = re.compile(
    r"^(?:[A-Z_][A-Z0-9_]*\([^()\n]*\)[ \t]+)?"
    r"[A-Za-z_][A-Za-z0-9_ \t*]*[ \t]+(?P<name>[A-Za-z_][A-Za-z0-9_]*)"
    r"\([^;{}]*\)\s*\{",
    re.MULTILINE,
)
GENERATED_FUNCTION = re.compile(
    r"^\s*DEFINE_[A-Z0-9_]+\(\s*(?P<name>[A-Za-z_][A-Za-z0-9_]*)\s*[,)]",
    re.MULTILINE,
)
ASM_FUNCTION = re.compile(r"^\s*(?:thumb|arm)_func_start\s+\S+", re.MULTILINE)
NONMATCHING_BLOCK = re.compile(
    r"#ifndef\s+NONMATCHING(?P<active>.*?)#else.*?#endif", re.DOTALL
)


def active_c_source(source: str) -> str:
    """Remove fallback C bodies that are disabled in matching builds."""
    return NONMATCHING_BLOCK.sub(lambda match: match.group("active"), source)


def c_function_count(source: str) -> int:
    return len(c_function_names(source))


def c_function_names(source: str) -> set[str]:
    source = active_c_source(source)
    return {match.group("name") for match in C_FUNCTION.finditer(source)} | {
        match.group("name") for match in GENERATED_FUNCTION.finditer(source)
    }


def tracked(pattern: str) -> list[Path]:
    output = subprocess.check_output(
        ["git", "ls-files", "--cached", "--others", "--exclude-standard", "--", pattern],
        cwd=ROOT,
        text=True,
    )
    return [ROOT / line for line in output.splitlines() if line]


def line_count(paths: list[Path]) -> int:
    return sum(len(path.read_text(encoding="utf-8").splitlines()) for path in paths)


def function_counts_at_ref(ref: str) -> tuple[int, int] | None:
    try:
        names = subprocess.check_output(
            ["git", "ls-tree", "-r", "--name-only", ref], cwd=ROOT, text=True
        ).splitlines()
    except subprocess.CalledProcessError:
        return None

    c_count = 0
    asm_count = 0
    for name in names:
        if not (name.endswith(".s") or (name.startswith("src/") and name.endswith(".c"))):
            continue
        contents = subprocess.check_output(
            ["git", "show", f"{ref}:{name}"], cwd=ROOT, text=True
        )
        if name.endswith(".c"):
            c_count += c_function_count(contents)
        else:
            asm_count += len(ASM_FUNCTION.findall(contents))
    return c_count, asm_count


def c_text_size() -> int | None:
    size_tool = shutil.which("arm-none-eabi-size")
    objects = sorted((ROOT / "build" / "src").glob("*.o"))
    if size_tool is None or not objects:
        return None

    total = 0
    for obj in objects:
        output = subprocess.check_output([size_tool, "-A", obj], text=True)
        for line in output.splitlines():
            fields = line.split()
            if len(fields) >= 2 and fields[0].startswith(".text"):
                total += int(fields[1])
    return total


def linked_function_counts(c_files: list[Path], asm_files: list[Path]) -> tuple[int, int, int] | None:
    """Count only function symbols that survived the final link."""
    elf = ROOT / "mlss.elf"
    nm_tool = shutil.which("arm-none-eabi-nm")
    if nm_tool is None or not elf.exists() or elf.stat().st_size == 0:
        return None

    source_c_names: set[str] = set()
    for path in c_files:
        source_c_names |= c_function_names(path.read_text(encoding="utf-8"))
    object_c_names: set[str] = set()
    for obj in sorted((ROOT / "build" / "src").glob("*.o")):
        output = subprocess.check_output([nm_tool, "-S", "--defined-only", obj], text=True)
        for line in output.splitlines():
            fields = line.split()
            if len(fields) < 4 or fields[2] not in {"T", "t"}:
                continue
            name = fields[3]
            if not name.endswith("_padding") and not name.startswith(("draft_", "rejected_")):
                object_c_names.add(name)
    c_names = source_c_names & object_c_names
    asm_names: set[str] = set()
    for path in asm_files:
        asm_names |= {
            match.group(0).split()[-1]
            for match in ASM_FUNCTION.finditer(path.read_text(encoding="utf-8"))
        }

    output = subprocess.check_output([nm_tool, "-S", "--defined-only", elf], text=True)
    linked_text: dict[str, int] = {}
    for line in output.splitlines():
        fields = line.split()
        if len(fields) >= 4 and fields[2] in {"T", "t"}:
            linked_text[fields[3]] = int(fields[1], 16)
        elif len(fields) >= 3 and fields[1] in {"T", "t"}:
            linked_text[fields[2]] = 0
    linked_names = set(linked_text)
    linked_c = linked_names & c_names
    return (
        len(linked_c),
        len(linked_names & asm_names),
        sum(linked_text[name] for name in linked_c),
    )


parser = argparse.ArgumentParser(description="Report decompilation progress")
parser.add_argument("--base", default="upstream/master", help="Git ref used for the delta")
args = parser.parse_args()

c_files = tracked("src/*.c")
asm_files = tracked("*.s")
linked_counts = linked_function_counts(c_files, asm_files)
if linked_counts is None:
    c_functions = sum(c_function_count(path.read_text(encoding="utf-8")) for path in c_files)
    asm_functions = sum(len(ASM_FUNCTION.findall(path.read_text(encoding="utf-8"))) for path in asm_files)
    count_mode = "source fallback"
    text_size = c_text_size()
else:
    c_functions, asm_functions, text_size = linked_counts
    count_mode = "linked symbols"
total_functions = c_functions + asm_functions
percent = 100.0 * c_functions / total_functions

print("Decompilation progress")
print(f"  Functions in C:         {c_functions:4d} / {total_functions} ({percent:.4f}%)")
print(f"  Functions in assembly:  {asm_functions:4d} / {total_functions} ({100.0 - percent:.4f}%)")
print(f"  Count mode:             {count_mode}")

if text_size is not None:
    print(f"  Matched C .text:        {text_size:8d} bytes")

base_counts = function_counts_at_ref(args.base)
if base_counts is not None and count_mode == "source fallback":
    base_c, base_asm = base_counts
    base_total = base_c + base_asm
    base_percent = 100.0 * base_c / base_total
    print(
        f"  Change vs {args.base}:  {c_functions - base_c:+4d} C functions, "
        f"{percent - base_percent:+.4f} percentage points"
    )

print(f"  Tracked C source:       {len(c_files):4d} files, {line_count(c_files)} lines")
