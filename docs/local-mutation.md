# Local CPU mutation search

Use this stage for compilable, nearly matching C with a known interface. It runs no
model and makes no inference API calls. m2c/type recovery still precedes it; source
review, subsystem integration, and full ROM acceptance still follow it.

## Setup

Run under Linux x86_64 or WSL with the normal project compiler and exact reference
ROM/ELF installed:

```sh
bash scripts/setup-mutation-tools.sh
```

The setup pins Transmuter, decomp-permuter, Bun, and pnpm. Dependencies live in
`$HOME/.cache/mlss-mutation` by default; `MLSS_MUTATION_TOOLS` overrides that path.
It does not install a global runtime or require API credentials. Logs are in that
tool directory. Keep dependency trees and search work on a native Linux filesystem
under WSL, because mutation searches create many short-lived files and processes.
The Bun download is Linux x86_64 specific; other platforms need their own setup.

## One candidate

```sh
python3 scripts/decomp_mutate.py sub_806018C scratch/candidate.c \
  --engine permuter --seconds 60 --jobs 8 --work-root /tmp/mlss-mutations
python3 scripts/decomp_mutate.py sub_806018C scratch/candidate.c \
  --engine transmuter --seconds 60 --jobs 8 --work-root /tmp/mlss-mutations
```

Replace the symbol and source with the assignment. The source must contain one
target function plus its headers/declarations. Historical `SEC(name)` section
macros are removed during preprocessing; other attributes and types are preserved.
No automatic typing repairs are made. Use `--prepare-only` to check compilation and
target extraction without starting a search. Already matching inputs are reported
separately and do not count as search successes.

Each run uses an independent directory and retains the original preprocessed C,
target assembly/object, compile wrapper, logs, best source, and `result.json`.
`--tools` selects another installation. Transmuter additionally accepts a compile
budget through `--max-compiles` and a seed through `--seed`. decomp-permuter's hidden
seed switch is a failure-reproduction control, not a comparable seeded search mode,
so the adapter deliberately does not set it. Parallel time-limited runs are not
bit-for-bit reproducible; save their inputs and outputs.

Both tools use the Makefile's pinned agbcc and assembler flags. Candidates are
preprocessed once, then compiled locally for each mutation. Full logs stay on disk;
the adapter prints one JSON result. The process-group deadline kills remaining
search workers and compiler descendants, including after a failed parent exits.
Transmuter gets up to five seconds of outer shutdown allowance beyond its internal
search timeout. Preparation and independent verification have separate bounds.

## Acceptance and limitations

Before searching, the adapter assembles and links the target at its ROM address and
requires its whole span to match the frozen ROM. It imports the reference ELF's
symbol types with `--just-symbols`; replacing Thumb functions with numeric `PROVIDE`
symbols can introduce interworking veneers and invalidate the comparison.

The best candidate is independently recompiled and linked against the frozen ROM.
Only identical lengths and bytes produce `span_match`. A tool's score of zero alone
is insufficient. Span sizes can include literal pools or padding and must not be
reported as linked C function bytes. The adapter currently supports Thumb targets;
unresolved renamed symbols, malformed drafts, or non-extractable target spans are
reported as errors rather than guessed around.

Mutation operators are search heuristics, not proofs of C semantics or good types.
Some historical drafts use provisional `M2C_UNK` declarations. Never integrate those
unchanged merely because the compiled bytes match. Review the resulting ordinary C,
recover evidence-backed interfaces, integrate into the owning subsystem, and run
`make decomp-acceptance`. Behavioral inline assembly is not accepted C progress.

## Compare engines without model polling

Create an ignored JSON manifest:

```json
{"cases": [{"function": "sub_806018C", "source": "scratch/candidate.c"}]}
```

Then run:

```sh
python3 scripts/decomp_mutation_trial.py scratch/trial.json \
  --seconds 30 --jobs 8 --work-root /tmp/mlss-mutation-trial \
  --output scratch/trial-results.json
```

Each pair runs concurrently with four compiler workers per engine, then the script
advances to the next function. It verifies that both engines received identical
raw and preprocessed input hashes, saves results after each pair, and prints one
summary line. Compare verified matches and elapsed time, not numeric scores between
engines: the scoring scales differ. Compiler attempts include unsuccessful compiles;
permuter internal failures are reported separately. Do not treat them as useful work.

Allow the batch to finish under the shell, rather than spending model turns polling
individual mutations. An expensive model should receive only an unresolved interface
question or the best candidate and a concrete remaining mismatch.

Tool sources: [Transmuter](https://github.com/macabeus/transmuter),
[decomp-permuter](https://github.com/simonlindholm/decomp-permuter).
