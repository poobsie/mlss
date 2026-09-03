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

## Subsystem recovery workflow

Work on one subsystem at a time. Matching and detangling are one acceptance unit.
Do not count raw C coverage as completed decompilation until the slice has a defensible
owner, interface, and uncertainty record.

For ongoing detangling work, use `config/detangling.json` as the persistent queue and follow `docs/detangling-workflow.md`. Resume an `active` subsystem first, otherwise take the first actionable `queued` subsystem. After an exact verified commit, update the queue and immediately continue to the next slice without waiting for another user prompt. Stop only when the current decompiled C is classified as `detangled` or `deferred`, an exact build cannot be restored, required evidence is unavailable for every remaining slice, or the user interrupts the work.

1. Identify a narrow boundary from behavior, callers, shared state, and data tables.
2. Move accepted code into a subsystem folder under `src/`, with a matching public header under `include/` when callers share an API.
3. Replace address-derived names only when the evidence supports a stable semantic name. Record uncertain meanings instead of guessing.
4. Recover function signatures, parameter names, constants, structures, and ownership together. A renamed function surrounded by raw offsets and conflicting declarations is not finished.
5. Update every caller to use the shared interface, then remove duplicate local declarations.
6. Preserve code and data order in the linker script, including deliberate alignment bytes required for an exact match.
7. Require an exact ROM comparison before proceeding to the next subsystem. If unrelated work makes a full link unavailable, verify the affected byte range against the most recent exact build and clearly record the limitation.

Newly decompiled code must enter its subsystem directly. Do not accumulate exact m2c
translations in root-level holding files for later cleanup. When the boundary genuinely
cannot be established, retain honest address names, assign the code to a neutral
address-range module in the `unclassified` queue, and record the concrete evidence
needed to move it. This is an exception state, not a normal pipeline stage.

## Multi-agent decompilation

The coordinator assigns bounded, caller-connected slices instead of unrelated symbol
lists. A slice should normally contain 5 to 25 related functions, or a smaller leaf plus
enough caller, callee, and data context to recover its interface.

- The coordinator owns slice boundaries, shared headers, linker order, queue state,
  subsystem documentation, final verification, and integration.
- Evidence workers trace callers, callees, globals, tables, likely ownership, signatures,
  and naming confidence. Their output includes sources of evidence and unresolved facts.
- Implementation workers receive disjoint address ranges and source ownership. They may
  edit in parallel only in isolated worktrees. When agents share a checkout, one
  integrator writes while the other agents perform read-only analysis.
- Workers do not independently edit common headers, linker scripts, symbols, or queue
  metadata unless the coordinator explicitly assigns ownership of those files.
- The coordinator rejects a result that lacks subsystem classification, evidence-backed
  interfaces, an explicit retained-unknown list, and an exact byte comparison. A proposed
  slice expansion returns to coordination before anyone edits outside the assigned range.

Run `make decomp-acceptance` before accepting a completed slice. This verifies the ROM
and every linked C function, then rejects active or queued cleanup work and any source
still assigned to the unclassified bucket. A deferred subsystem is acceptable only when
its `next_action` names the missing evidence.

## Verification

1. Build the ROM with `make` in a compatible Unix-like environment.
2. Require the SHA-1 comparison to report `mlss.gba: OK`.
3. Run `make decomp-acceptance` before accepting a completed decompilation slice.
4. Use `make progress` only for reporting; function count is not a substitute for readable, evidence-based source.

Windows users may invoke the same workflow through WSL with the PowerShell wrappers in `scripts/`.
