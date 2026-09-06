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

Work on one subsystem slice at a time. Matching and detangling share one acceptance
pipeline, but semantic refinement is progressive. Exact typed C in the correct
subsystem is acceptable with honest address-based function names, offset-based field
names, and an explicit retained-unknown note. Do not delay a whole slice while trying
to infer gameplay identities that its current callers and data do not prove.

For ongoing detangling work, use `config/detangling.json` as the persistent queue and follow `docs/detangling-workflow.md`. Resume an `active` subsystem first, otherwise take the first actionable `queued` subsystem. After an exact verified commit, update the queue and immediately continue to the next slice without waiting for another user prompt. Stop only when the current decompiled C is classified as `detangled` or `deferred`, an exact build cannot be restored, required evidence is unavailable for every remaining slice, or the user interrupts the work.

1. Identify a narrow boundary from behavior, callers, shared state, and data tables.
2. Move accepted code into a subsystem folder under `src/`, with a matching public header under `include/` when callers share an API.
3. Replace address-derived names only when the evidence supports a stable semantic name. Record uncertain meanings instead of guessing.
4. Recover the signatures, fields, constants, and ownership supported by current
   evidence. Prefer a checked partial structure with `field_XX` members over repeated
   pointer arithmetic. A semantic rename is optional until evidence makes it stable.
5. Update every caller to use the shared interface, then remove duplicate local declarations.
6. Preserve code and data order in the linker script, including deliberate alignment bytes required for an exact match.
7. Require exact linked bytes for every accepted function. Run the full ROM comparison
   at the batch checkpoint before integration; do not run a clean repository rebuild
   after every candidate.

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

Keep the pipeline implementation-bound. Evidence packets are inputs to a slice, not a
deliverable by themselves. Once a worker has enough evidence to define a safe boundary,
that worker should take the slice through C implementation, byte matching, documentation,
and a commit in its isolated worktree. Do not keep generating candidate lists while
previous candidates wait for a single coordinator to transcribe them.

- Start parallel worktrees from the same accepted commit and give each worker one
  subsystem, disjoint address range, and explicit file ownership.
- Measure throughput by exact functions and bytes integrated into the accepted branch.
  Candidate counts, draft bodies, and size-only matches are diagnostic data, not progress.
- Keep one active implementation slice per worker. Refill a worker only after its prior
  slice is committed, rejected with evidence, or returned for a boundary decision.
- Limit compiler-shaping work on one candidate to two informed attempts during a batch.
  Retain the diagnosis in ignored scratch space, restore its assembly, and continue with
  the rest of the slice instead of stalling the pipeline.
- Commit the exact accepted subset even when another candidate in the slice is rejected.
  The coordinator reviews and integrates worker commits sequentially, resolves shared
  interface and linker conflicts, reruns acceptance, pushes, and immediately starts the
  next worktree round.
- Keep volatile project-wide counts out of subsystem documents. Subsystem documentation
  records behavior, evidence, and retained unknowns; `make progress`, acceptance output,
  and explicit milestone audits own the changing global totals. This avoids needless
  documentation conflicts when independent worktrees integrate concurrently.

### Throughput policy

The default worker task is implementation, not an open-ended subsystem survey.

- Assign a contiguous caller-connected range with 10 to 30 plausible functions. Stop
  scouting as soon as the range and shared interfaces are understood well enough to
  implement; do not impose a quota such as surveying 50 or 70 routines.
- Prefer compiler-friendly families: repeated leaf callbacks, canonical library
  routines, sibling constructors/destructors, table readers, and short state
  transitions. Large controllers and known code-generation traps should not occupy an
  implementation lane while easier functions remain.
- Keep working after the first exact function. A normal packet target is at least 5
  functions or 256 executable bytes, and preferably 8 to 20 functions or 512 to 2048
  bytes. Close a smaller packet only when the local family is exhausted, an interface
  conflict requires coordinator review, or 30 minutes have elapsed with verified work.
- During shaping, rebuild the affected object and compare the candidate bytes. Run one
  incremental `make decomp-acceptance` for the finished packet. The coordinator may
  combine non-overlapping worker commits and run one full clean acceptance gate before
  pushing; a clean rebuild per individual function is unnecessary.
- Update subsystem documentation once per packet. Record facts shared by the packet and
  retained unknowns, not a narrative for every leaf function.
- The coordinator keeps a durable list of exhausted candidates and includes it in later
  assignments. Do not retry a recorded two-shape failure unless new type, caller, data,
  compiler, or boundary evidence specifically addresses the recorded mismatch.
- Classification is cheap and mandatory; deep naming is evidence-driven and may remain
  incomplete. Sorting code into the correct subsystem must not become a demand to solve
  the entire subsystem before accepting exact C.

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
