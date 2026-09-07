# Focused matching-decompilation workflow

## Prepare types and run local comparisons

For compilable near-matches, the optional CPU mutation stage and unattended engine
comparison are documented in [local-mutation.md](local-mutation.md). Keep it bounded
and use it before further model-driven register or expression shaping. It does not
replace type recovery or acceptance.

Run the following commands under Unix or WSL from the repository root. Packet creation
now preprocesses relevant project headers before calling m2c. Automatic selection uses
bounded textual references to the target and its callees; it is not a complete call graph.
Choose the subsystem headers explicitly when automatic selection is incomplete or ambiguous:

```sh
.decomp-tools/venv/bin/python scripts/decomp_workflow.py packet sub_8000000 \
  --header include/global.h --header include/ui/object.h --output scratch/function.md
```

Replace the example symbol and headers with the assigned function and its actual interfaces.
Repeat `--header` for additional headers, or supply an already preprocessed `--context` file.
Context generation follows header includes with the Makefile's preprocessor flags. Stable
scratch paths preserve m2c's parsing cache, and changed headers refresh the context. A context
failure is reported rather than silently discarding type evidence.

Packets include bounded C reference locations and previous rejection evidence. Raw target
hex is omitted by default; `--include-bytes` restores it for inspection. The default target
is the frozen reference ROM, not a potentially nonmatching build. The address span may include
padding and is not a linked function-size measurement.

Use the local runner before spending model turns on mechanical control-flow variations:

```sh
.decomp-tools/venv/bin/python scripts/decomp_local.py nullsub_1 \
  --header include/global.h --seconds 60 --max-variants 3
.decomp-tools/venv/bin/python scripts/decomp_local.py sub_8000000 \
  scratch/first.c scratch/second.c --seconds 60 --max-variants 2
```

With no source arguments, the runner tries the default m2c draft, `--no-switches`, and
`--gotos-only`, skipping identical drafts. These are bounded translation alternatives,
not random C permutations. With source arguments it tests only those standalone C files.
Each must define the target as its first emitted function and include its required types.
The runner reads compiler flags from the Makefile, compiles in a unique scratch directory,
and resolves external symbols using the frozen reference ELF. It never installs the draft
in `src/` or changes assembly/linker ownership.

Results distinguish `types_required`, `decompiler_warning`, `error`, `mismatch`, and `span_match`. Unknown m2c
types stop automatic variants so the worker can supply evidence-backed signatures instead
of guessing. A wall-clock deadline bounds subprocesses; complete command logs, source,
target bytes, linked output, disassembly, and a JSON report remain under `scratch/matching/`.
The compact report gives byte lengths and the first mismatch offset. A span match requires
equal lengths and equal bytes, including the span's padding. It remains a diagnostic result:
review the source, integrate in the correct subsystem, verify linked function bytes, and
run `make decomp-acceptance`. Reference-address scratch linking does not validate the final
project layout. ARM-mode functions need a suitable separately configured compiler path;
this runner uses the repository's normal Thumb compilation flags.

Keep a worker on one family and provide its shared interfaces once. Ask a stronger model
only a specific unresolved type, ownership, or compiler question, with the best draft and
failed attempts attached. Do not restart broad workflow reviews between pilot packets.
Compare at least three comparable packets before claiming token savings. Account allowance
percentages, raw model tokens, and API charges are distinct measurements; record each only
when it is actually available, including rejected work and coordination.

The workflow keeps large assembly files out of the model context. It ranks small
functions and creates a compact evidence packet with the target's assembly callers,
callees, and neighbors. A packet is a scouting boundary, not permission to turn an
isolated m2c translation into permanent source.

Run the initial tool setup once:

```sh
scripts/setup-tools.sh
```

Build the current exact ROM and map, then list likely easy candidates:

```sh
make
.decomp-tools/venv/bin/python scripts/decomp_workflow.py scan --max-bytes 96 --limit 25
```

Create a packet in the ignored scratch directory:

```sh
.decomp-tools/venv/bin/python scripts/decomp_workflow.py packet nullsub_21 \
  --output .decomp-tools/packets/nullsub_21.md
```

Measure its context cost against loading the entire source assembly file:

```sh
.decomp-tools/venv/bin/python scripts/decomp_workflow.py benchmark nullsub_21
```

Check discovery, target-byte extraction, SWI filtering, and packet size against
the current exact build:

```sh
.decomp-tools/venv/bin/python scripts/test_decomp_workflow.py
```

## Coordinating multiple agents

Use an implementation-first pipeline. Assign compact packets directly to isolated
workers when the subsystem and address boundary are already defensible. A separate
evidence pass is reserved for genuinely ambiguous ownership, ABI, or data boundaries;
it is not the default precondition for writing C. A bounded slice normally contains 10
to 30 plausible related functions in one contiguous range.

The stages form a continuous pipeline, not separate backlogs. Once the evidence for a
slice is sufficient, the same worker should implement and exact-match it in an isolated
worktree. A scouting report is useful only when it changes the next implementation
decision. Do not accumulate reports faster than accepted slices can be integrated.

The coordinator owns shared headers, linker placement, symbols, queue state, and final
integration. Workers may edit concurrently only when they have isolated worktrees and
non-overlapping file ownership. If they share a checkout, keep workers read-only and use
one writing integrator. Concurrent edits to a common header or linker script create
ambiguity instead of removing it.

Every worker result uses the packet contract fields: functions, subsystem, evidence,
semantic names, retained unknowns, shared interfaces, exact match, byte count, changed
files, and follow-up. If sound typing or ownership requires code outside the assignment,
the worker proposes a larger slice instead of silently expanding scope.

For sustained parallel work:

1. Create one worktree per worker from the latest accepted commit.
2. Assign one bounded subsystem slice and explicit source ownership to each worker.
3. Have each worker implement, compare exact bytes, document uncertainty, and commit a
   useful packet. Two informed shaping attempts per function are enough for one batch;
   restore difficult outliers to assembly and keep moving. Do not stop after the first
   match when other compiler-friendly functions remain in the assigned range.
4. Integrate non-overlapping worker commits together when practical. Resolve shared
   header and linker order centrally, run one full clean `make decomp-acceptance` for
   the combined checkpoint, push it, then refill all workers from that checkpoint.

The normal packet target is 5 or more exact functions or 256 or more executable bytes,
preferably 8 to 20 functions or 512 to 2048 bytes. A smaller packet is justified only
by local exhaustion, an interface decision, or a 30-minute checkpoint. Do not require a
fixed survey count. Scouting ends when implementation can begin.

Subsystem classification and deep semantic naming have different costs. Classification
is required immediately. A checked typed layout may retain `field_XX`, numeric constants,
and address-based function names when that is the strongest honest statement available.
Refine those names when adjacent callers or data supply evidence; do not hold exact code
in assembly while guessing gameplay meaning.

Subsystem documents describe recovered behavior and retained uncertainty. Do not copy the
current project-wide function count into every subsystem page; use `make progress` for live
totals and record durable milestone numbers in `docs/detangling-audit.md`. Global counters
in worker-owned documentation create avoidable merge conflicts and become stale immediately.

Report accepted exact functions and bytes per round. Do not report candidate counts as
decompilation progress.

## Measuring throughput

The tracked telemetry ledger provides prospective evidence for workflow changes:

```sh
python3 scripts/decomp_telemetry.py snapshot --phase batched-v1 \
  --functions 2157 --matched-bytes 125442 --accepted 8 --accepted-bytes 632 \
  --attempted 12 \
  --rejected 4 --model gpt-5.6-luna --wall-minutes 30 \
  --gate-seconds 10 --coordination-minutes 3 --usage-used-percent 1
python3 scripts/decomp_telemetry.py report
```

Supply the live values printed by the acceptance and progress commands. When available,
also record the account usage reset timestamp so usage deltas are never compared across
weekly windows. Record exhausted candidates once:

Scanner sizes are address spans to the next mapped symbol. They are useful for assignment
boundaries, but can include unnamed or non-function bytes. Record accepted bytes from the
linked ELF `FUNC` sizes and require the packet total to match the integrated matched `.text`
delta.

```sh
python3 scripts/decomp_telemetry.py reject sub_8000000 \
  --mismatch-class "literal register allocation" \
  --required-evidence "a recovered type that changes literal lifetime"
```

The scanner omits exhausted entries until their stated evidence changes. A workflow has
not proved faster merely because its prompt is shorter or one packet succeeds. Compare
at least three packets over at least one hour, count rejected work and coordination, and
require exact acceptance throughout.

## Acceptance

A decompiled slice is accepted only when its code is in a defensible subsystem module,
shared declarations are canonical, names and types are supported by evidence, remaining
uncertainty is explicit, and the bytes match. Address names are acceptable when honest;
unclassified holding files are not a completion state.

Do not accept object size or instruction shape as proof. The acceptance command rebuilds
the exact ROM, audits every linked C symbol against the reference, and checks that the
detangling queue has no active, queued, or unclassified source:

```sh
make decomp-acceptance
```

Use `make progress` afterward when a coverage number is useful. Progress is reporting,
not acceptance.

`verify_exact_functions.py` fails if any linked C function differs. The progress
report classifies linked symbols by the C or assembly object that defines them,
so rejected drafts, disabled assembly blocks, padding objects, declarations,
and unlinked experiments cannot inflate the percentage. It does not guess from
source when build products are absent.

The benchmark reports two baselines: the complete assembly source and a more
conservative 200-line local window. It measures prompt material only. It does not
claim to measure hidden reasoning, generated output, or provider-side caching.

Token counts change as assembly is converted. Run the benchmark command when a
current measurement is useful instead of preserving historical milestone data
in this document.
