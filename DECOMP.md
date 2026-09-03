# Decompilation workflow

The canonical build uses a Unix-like shell and GNU Make. Linux works directly; Windows users can run the
same toolchain through WSL. The repository may live at any path. The PowerShell wrappers resolve their
location from the checkout rather than relying on a particular drive or directory.

Ghidra, mGBA, objdiff, and similar interactive tools are optional. Their local workspaces do not belong in
the repository, and no checked-in source should depend on a particular disassembler, IDE, or machine.

## Installed tools

- `agbcc`, the matching compiler, is installed locally under `tools/agbcc`.
- GNU ARM binutils build and inspect ARM7TDMI objects.
- `m2c` produces a first-pass C translation from an assembly function.
- `asm-differ` compares the rebuilt ROM with the original ROM by symbol or address.
- `decomp-permuter` helps with late-stage instruction and register-allocation matching.
- objdiff provides an interactive whole-object comparison.
- Ghidra 12.0.2 with `gba-ghidra-loader` provides static analysis.
- mGBA provides runtime debugging, breakpoints, watchpoints, and GDB integration.

The Python tools and a frozen reference ELF live in `.decomp-tools`, which is intentionally ignored by
Git. Run `scripts/setup-tools.sh` from the repository root to recreate them at their pinned revisions.

## Routine commands

From the project root in a compatible Unix-like environment:

```sh
make
.decomp-tools/venv/bin/python scripts/progress.py
.decomp-tools/venv/bin/asm-differ -mwo sub_8056224
mkdir -p scratch
scripts/decompile-function.sh asm/text08057568.s sub_8057568 > scratch/sub_8057568.c
```

On Windows, `scripts/build-wsl.ps1` performs the same build through WSL and accepts ordinary Make targets,
for example `scripts/build-wsl.ps1 verify`. The default `objdiff.json` is shell-independent and expects
objdiff to run in the same Unix-like environment as Make. objdiff compares the complete current ELF with the frozen,
matching reference ELF, so it is the primary diff view when moving new functions out of the large assembly
files. `asm-differ` is ready for functions in the C translation units represented in its frozen expected-object
directory.

To rebuild, verify the ROM, and print the current decompilation percentage in one step, run:

```powershell
.\scripts\progress-wsl.ps1
```

The portable equivalent is `make progress`. Progress is calculated from symbols in the linked C and assembly
objects. It deliberately refuses to estimate a percentage when the linked ELF or build objects are missing.

## Slice workflow

1. Choose a bounded caller-connected slice, normally 5 to 25 related functions. A
   single leaf is reasonable when its ownership and interface are already clear.
2. Study its callers, callees, globals, adjacent functions, data tables, and runtime behavior.
3. Give the function and related data meaningful provisional names in `symbols.txt` and headers only when
   the evidence supports them. Otherwise retain address-based placeholders.
4. Generate a rough translation with `m2c`, then correct its types and control flow by hand.
5. Put the code directly in its subsystem module, recover shared declarations in one
   canonical header, and record retained unknowns. Do not use a root-level holding file.
6. Remove only the assigned assembly range and run `asm-differ` until every function matches.
7. Run `make decomp-acceptance` before committing.

For coordinated agent work, use the ownership and handoff rules in
`docs/decomp-workflow.md`. Exact bytes alone do not complete a slice.

Do not commit the ROM, BIOS, Ghidra databases, generated build products, or `.decomp-tools`.
