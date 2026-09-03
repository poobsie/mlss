# Current detangling audit

The currently decompiled C is fully triaged by subsystem. The queue contains no active, queued, or unclassified source files.

| disposition | C lines | share |
| --- | ---: | ---: |
| Detangled | 12,439 | 99.59% |
| Deferred with a concrete evidence requirement | 51 | 0.41% |
| Active or unclassified | 0 | 0.00% |

The deferred slice is `src/memory/heap.c`. Its allocation and free operations are understood, but the ROM contains two identical allocation entry points and two identical free entry points. Their caller groups differ without proving a behavioral or ownership distinction. The slice should reopen when adjacent assembly or runtime tracing establishes why both entry points exist.

The uncertainty counts reported by `scripts/detangling_status.py` are triage signals, not unfinished-work percentages. Remaining address names are retained where they are ABI entry points, refer to assembly-only callbacks, or lack evidence for a narrower identity. Remaining offset-bearing names describe structurally proven but semantically unidentified fields. The subsystem documents record the specific evidence needed to refine them.

The final audit requires `make verify` to report an exact ROM match for all 1,368 linked C functions. The workflow tests also cover linked-symbol progress classification and exact reference-byte extraction.
