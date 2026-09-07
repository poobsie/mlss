# CPU mutation pilot

Baseline: `83ecc30`, with an exact ROM and 2,186 checked linked C functions matching.
No game source was changed by the searches. The input pool was older retained probe
drafts, filtered for active assembly targets, a compilable standalone draft, and an
independently exact extracted target. Ten eligible drafts were selected; nine were
recorded rejections and `sub_81DCF6C` was an additional retained draft. This is a
selected pilot, not an unbiased sample of the remaining game.

Both engines received identical raw and preprocessed source hashes. Each received a
30-second search budget and four compiler workers, running concurrently for a total
of eight workers. Preparation and independent verification were outside that budget.
The search artifacts contain inputs, complete logs, best sources, and byte checks.

| Engine | Compiler invocations during search | Improved tool score | Independently matching spans |
| --- | ---: | ---: | ---: |
| Transmuter | 40,377 | 4 / 10 | 1 / 10 |
| decomp-permuter | 19,750 | 7 / 10 | 0 / 10 |

Compiler invocations include failed compiles and engine scoring/output work. They
are not unique useful mutations. Scores are tool-specific and must not be compared
numerically between engines. decomp-permuter reported no internal failures in the
main trial. Transmuter performed only its initial compile on three cases, despite
spending the time budget; those cases need investigation before broad deployment.

| Function | Target span | Transmuter score, before → after | Permuter score, before → after | Exact span |
| --- | ---: | ---: | ---: | --- |
| sub_819BA10 | 28 | 6 → 6 | 515 → 10 | No |
| sub_8161954 | 32 | 16 → 16 | 680 → 320 | No |
| sub_80EA940 | 40 | 3 → 3 | 15 → 15 | No |
| sub_80F7ED0 | 40 | 12 → 4 | 465 → 275 | No |
| sub_816393C | 60 | 24 → 15 | 2245 → 1085 | No |
| sub_819B2E0 | 60 | 1 → 0 | 5 → 5 | Transmuter |
| sub_806018C | 72 | 14 → 4 | 745 → 320 | No |
| sub_8161C28 | 116 | 41 → 41 | 1040 → 705 | No |
| sub_80E3034 | 124 | 38 → 38 | 1640 → 640 | No |
| sub_81DCF6C | 20 | 3 → 3 | 210 → 210 | No |

## Match review

Transmuter found the matching `sub_819B2E0` draft after 106 compiler invocations in
about two seconds. Its mutation changed the increment of a `u16 *` using a GNU cast
lvalue. That expression is unsuitable as portable C. A separate review replaced it
with `var_r4 += 0x10;`, advancing by the same 32 bytes. Recompiling that ordinary
pointer expression preserved all 60 reference bytes. The old draft advanced by 64
bytes, so the older ledger's literal-pool-padding diagnosis was incomplete.

The portable draft still needs the owning subsystem's declaration/type review and
normal integration gate. This report counts one verified scratch match, not one
accepted decompiled function. Provisional external declarations in historical m2c
drafts are not approved merely by byte equality.

## Workflow corrections found during setup

- The scanner's bare-register trampoline filter also matched normal Thumb returns
  using `pop {r1}; bx r1`. The filter now excludes only a bare indirect branch.
- Numeric linker `PROVIDE` symbols lost Thumb function metadata and caused unwanted
  interworking veneers. Scratch linking now imports the frozen ELF's typed symbols.
- Some extracted assembly blocks end by selecting the next module's section. The
  target wrapper returns to `.text` before setting the function size.
- decomp-permuter's hidden seed flag forces its failure-reproduction behavior, so it
  is not used as a general seeded benchmark mode.

The main trial followed these corrections. Setup smoke runs and excluded inputs are
not included in the table. A final cleanup makes generated compile wrappers remove
their temporary assembly files; this does not change compiler flags or candidates.

## Decision

Keep both engines available as a bounded optional stage. The CPU performed over
60,000 compiler invocations without inference API calls, but nine of ten drafts
still did not match within the budget. This establishes useful local search capacity,
not end-to-end automation or measured subscription savings. Setup and supervision
used model work; those costs are separate from the token-free search process.

Preserve the best failed drafts for specific later questions. Do not immediately
rerun every failure with a larger budget. Broader promotion requires the project's
normal comparable-packet measurement window and accepted C throughput, including
review/integration cost. No GPU model was installed for this CPU-engine pilot.
