# Decompilation workflow

This fork uses WSL2 for deterministic ARM builds and Windows applications for interactive analysis.
The checked-in configuration assumes the repository is available to WSL, as it is under `D:\mlss`.

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
Git. Run `scripts/setup-tools.sh` from WSL to recreate them at their pinned revisions.

## Routine commands

From WSL, in the project directory:

```sh
make
.decomp-tools/venv/bin/python scripts/progress.py
.decomp-tools/venv/bin/asm-differ -mwo sub_8056224
scripts/decompile-function.sh asm/text08057568.s sub_8057568 > scratch.c
```

From Windows, `scripts/build-wsl.ps1` performs the same verified WSL build. The `objdiff.json`
configuration uses that wrapper automatically. objdiff compares the complete current ELF with the frozen,
matching reference ELF, so it is the primary diff view when moving new functions out of the large assembly
files. `asm-differ` is ready for functions in the C translation units represented in its frozen expected-object
directory.

To rebuild, verify the ROM, and print the current decompilation percentage in one step, run:

```powershell
.\scripts\progress-wsl.ps1
```

From WSL, the equivalent command is `make progress`. The report also shows the change from
`upstream/master`, which is the untouched project baseline.

## Function workflow

1. Choose one reasonably small function from an assembly file.
2. Study its callers, callees, globals, and runtime behavior in Ghidra and mGBA.
3. Give the function and related data meaningful provisional names in `symbols.txt` and headers.
4. Generate a rough translation with `m2c`, then correct its types and control flow by hand.
5. Add the C function to the appropriate source module and remove only its original assembly range.
6. Run `asm-differ` until the function matches.
7. Run `make` and require `mlss.gba: OK` before committing.

Do not commit the ROM, BIOS, Ghidra databases, generated build products, or `.decomp-tools`.
