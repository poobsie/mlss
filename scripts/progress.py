#!/usr/bin/env python3
from __future__ import annotations

import re
import subprocess
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
C_FUNCTION = re.compile(
    r"^[A-Za-z_][A-Za-z0-9_\s*]*\s+[A-Za-z_][A-Za-z0-9_]*\([^;]*\)\s*\{",
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


c_files = tracked("src/*.c")
asm_files = tracked("*.s")
c_functions = sum(len(C_FUNCTION.findall(path.read_text(encoding="utf-8"))) for path in c_files)
asm_functions = sum(len(ASM_FUNCTION.findall(path.read_text(encoding="utf-8"))) for path in asm_files)

print(f"Tracked C files:          {len(c_files):8d}")
print(f"Tracked C lines:          {line_count(c_files):8d}")
print(f"C function definitions:   {c_functions:8d}")
print(f"Assembly files:           {len(asm_files):8d}")
print(f"Assembly lines/data:      {line_count(asm_files):8d}")
print(f"Assembly function starts: {asm_functions:8d}")
