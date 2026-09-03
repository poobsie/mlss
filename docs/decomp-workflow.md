# Focused matching-decompilation workflow

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

Use a two-stage flow. First, assign compact packets to evidence workers. They identify
the likely subsystem, caller-connected family, shared state, signature, naming evidence,
and facts that remain unknown. The coordinator then chooses a bounded slice, normally 5
to 25 related functions, and assigns disjoint address ranges for implementation.

The coordinator owns shared headers, linker placement, symbols, queue state, and final
integration. Workers may edit concurrently only when they have isolated worktrees and
non-overlapping file ownership. If they share a checkout, keep workers read-only and use
one writing integrator. Concurrent edits to a common header or linker script create
ambiguity instead of removing it.

Every worker result uses the packet contract fields: functions, subsystem, evidence,
semantic names, retained unknowns, shared interfaces, exact match, byte count, changed
files, and follow-up. If sound typing or ownership requires code outside the assignment,
the worker proposes a larger slice instead of silently expanding scope.

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
