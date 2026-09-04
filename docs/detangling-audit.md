# Current detangling audit

The currently decompiled C is fully triaged by subsystem. The queue contains no active, queued, or unclassified source files.

| disposition | C lines | share |
| --- | ---: | ---: |
| Detangled | 17,758 | 99.71% |
| Deferred with a concrete evidence requirement | 51 | 0.29% |
| Active or unclassified | 0 | 0.00% |

The deferred slice is `src/memory/heap.c`. Its allocation and free operations are understood, but the ROM contains two identical allocation entry points and two identical free entry points. Their caller groups differ without proving a behavioral or ownership distinction. The slice should reopen when adjacent assembly or runtime tracing establishes why both entry points exist.

The uncertainty counts reported by `scripts/detangling_status.py` are triage signals, not unfinished-work percentages. Remaining address names are retained where they are ABI entry points, refer to assembly-only callbacks, or lack evidence for a narrower identity. Remaining offset-bearing names describe structurally proven but semantically unidentified fields. The subsystem documents record the specific evidence needed to refine them.

At the 25% proof-of-concept checkpoint, 1,755 of 7,017 functions are in C (25.0107%), and `make decomp-acceptance` reports an exact ROM match for all 1,750 linked C functions. The workflow tests also cover linked-symbol progress classification and exact reference-byte extraction.
