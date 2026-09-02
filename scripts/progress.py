#!/usr/bin/env python3
from __future__ import annotations

import argparse
import re
import shutil
import subprocess
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
C_FUNCTION = re.compile(
    r"^[A-Za-z_][A-Za-z0-9_ \t*]*[ \t]+[A-Za-z_][A-Za-z0-9_]*\([^;{]*\)[ \t]*\{",
    re.MULTILINE,
)
ASM_FUNCTION = re.compile(r"^\s*(?:thumb|arm)_func_start\s+\S+", re.MULTILINE)


def tracked(pattern: str) -> list[Path]:
    output = subprocess.check_output(
        ["git", "ls-files", pattern], cwd=ROOT, text=True
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
            c_count += len(C_FUNCTION.findall(contents))
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
            if len(fields) >= 2 and fields[0] == ".text":
                total += int(fields[1])
                break
    return total


parser = argparse.ArgumentParser(description="Report decompilation progress")
parser.add_argument("--base", default="upstream/master", help="Git ref used for the delta")
args = parser.parse_args()

c_files = tracked("src/*.c")
asm_files = tracked("*.s")
c_functions = sum(len(C_FUNCTION.findall(path.read_text(encoding="utf-8"))) for path in c_files)
asm_functions = sum(len(ASM_FUNCTION.findall(path.read_text(encoding="utf-8"))) for path in asm_files)
total_functions = c_functions + asm_functions
percent = 100.0 * c_functions / total_functions

print("Decompilation progress")
print(f"  Functions in C:         {c_functions:4d} / {total_functions} ({percent:.4f}%)")
print(f"  Functions in assembly:  {asm_functions:4d} / {total_functions} ({100.0 - percent:.4f}%)")

text_size = c_text_size()
if text_size is not None:
    print(f"  Matched C .text:        {text_size:8d} bytes")

base_counts = function_counts_at_ref(args.base)
if base_counts is not None:
    base_c, base_asm = base_counts
    base_total = base_c + base_asm
    base_percent = 100.0 * base_c / base_total
    print(
        f"  Change vs {args.base}:  {c_functions - base_c:+4d} C functions, "
        f"{percent - base_percent:+.4f} percentage points"
    )

print(f"  Tracked C source:       {len(c_files):4d} files, {line_count(c_files)} lines")
