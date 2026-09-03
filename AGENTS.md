# Project guidance

This repository is a matching decompilation of the US release of Mario & Luigi: Superstar Saga.
Every source change must preserve the reference ROM unless a task explicitly says otherwise.

## Portability

- Keep repository content independent of any contributor, assistant, machine, drive letter, shell, IDE, or reverse-engineering workspace.
- Do not put personal names, agent names, session numbers, dates, or machine-local paths in filenames, symbols, linker sections, comments, or generated artifact names.
- Document commands from the repository root. Prefer portable commands and scripts. If a platform-specific wrapper is useful, describe it as an optional wrapper rather than the canonical workflow.
- Keep ROMs, BIOS files, build products, tool environments, disassembler databases, and other machine-local material out of Git.

## Decompilation conventions

- Preserve unknown function names such as `sub_8057568` until there is enough evidence for a semantic name. An address-based placeholder is more honest than a confident guess.
- Name source files and linker-section groups by game subsystem when known. When it is not known, use a neutral address range or a plain structural description.
- Do not use workflow history in permanent names. Terms such as `batch`, `wave`, `push`, `expansion`, `compact`, and numbered author passes describe how code was produced, not what it does.
- Replace generated identifiers (`arg0`, `var_r0`, `M2C_UNK`, raw field offsets) when types and behavior are understood. Do not invent types merely to make code look finished.
- Add short comments for confirmed behavior, invariants, hardware registers, fixed-point units, table layouts, and deliberate matching constraints. Avoid comments that only restate the C expression.
- Keep declarations in headers when they are shared. Temporary local declarations are acceptable while a subsystem is still being reconstructed, but should not spread between files.
- Keep disabled, rejected, and nonmatching drafts under the ignored `scratch/` directory. Files under `src/` are part of the build and should contain accepted code.

## Verification

1. Build the ROM with `make` in a compatible Unix-like environment.
2. Require the SHA-1 comparison to report `mlss.gba: OK`.
3. Run `make verify` when functions or linker placement change.
4. Use `make progress` only for reporting; function count is not a substitute for readable, evidence-based source.

Windows users may invoke the same workflow through WSL with the PowerShell wrappers in `scripts/`.
