# Compact matching-decompilation workflow

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
call names, an m2c draft, and a strict result contract. Give each worker a disjoint
address range and request the five-field result described in the packet. Integrate
accepted functions in batches, then run one clean full-ROM build.

Do not accept object size or instruction shape as proof. The single milestone
command rebuilds the exact ROM, audits every linked C symbol against the
reference, then reads progress from the linked ELF:

```sh
make progress
```

`verify_exact_functions.py` fails if any linked C function differs. The progress
report uses linked symbols when a built ELF is present, so rejected drafts,
padding objects, declarations, and unlinked experiments cannot inflate the
percentage. It falls back to source counting only when no linked ELF is available.

The benchmark reports two baselines: the complete assembly source and a more
conservative 200-line local window. It measures prompt material only. It does not
claim to measure hidden reasoning, generated output, or provider-side caching.

## Validated trial

The first trial packet targeted `sub_8158E10`. It contained 246 `o200k_base`
tokens, produced clean C, and the cold rebuild retained the exact ROM SHA-1
`7C303CDDE5061EE329296948060B875CB50BA410`. The corresponding assembly source
contained 8,945,270 tokens, a 99.9972% reduction in supplied source context.

The 5% milestone used the same flow. A representative `sub_815FACC` packet was
357 tokens versus 2,666 tokens for a 200-line local window, an 86.61% reduction.
