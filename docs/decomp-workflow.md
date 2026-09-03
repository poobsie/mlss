# Focused matching-decompilation workflow

The workflow keeps large assembly files out of the model context. It ranks small
functions, creates a self-contained packet for one function, and measures the
packet with the pinned `o200k_base` tokenizer.

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

Candidate packets contain only the function's assembly, target ROM bytes, direct
call names, an m2c draft, and a strict result contract. Give concurrent work disjoint
address ranges and request the five-field result described in the packet. Integrate
accepted functions, then run one clean full-ROM build.

Do not accept object size or instruction shape as proof. The single milestone
command rebuilds the exact ROM, audits every linked C symbol against the
reference, then reads progress from the linked ELF:

```sh
make progress
```

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
