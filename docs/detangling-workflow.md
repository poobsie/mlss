# Detangling workflow

Detangling is a continuous companion to matching decompilation. The unit of work is a bounded subsystem slice, not an arbitrary number of functions and not an entire unfinished subsystem.

The persistent queue is stored in `config/detangling.json`. Inspect it with:

```sh
make detangle-status
python3 scripts/detangling_status.py next
```

The queue state is authoritative; the scanner's uncertainty count is only a triage signal. A low count does not prove that names or types are correct.

## Continuous work loop

1. Start from an exact build with `make verify`.
2. Resume the subsystem marked `active`. If none is active, take the first `queued` subsystem.
3. Inspect callers, callees, shared globals, descriptors, tables, and adjacent assembly before editing names.
4. Define a slice small enough to verify and commit independently. A useful default is 5 to 25 functions or one shared structure plus its direct users.
5. Mark the subsystem `active` in the queue.
6. Recover the boundary and ownership first: source folder, public header, shared types, and linker placement.
7. Recover function signatures, field names, constants, and semantic names together. Keep address names where evidence is insufficient.
8. Update all known callers and remove superseded local declarations.
9. Record evidence, unresolved questions, and matching constraints in the subsystem document.
10. Run `make verify`. Do not accept a mismatching slice.
11. Commit the verified slice, update its queue state, then immediately select the next slice.

No user prompt is required between successful slices. Continue until all currently decompiled C has either been detangled or assigned a concrete deferred evidence requirement.

## Queue states

- `active`: currently being investigated or edited. There should be at most one.
- `queued`: enough evidence exists to attempt a bounded slice.
- `detangled`: the currently decompiled portion has stable boundaries and honest names. Future adjacent decompilation may reopen it.
- `deferred`: progress requires specific evidence that is not currently available. The `next_action` must state what evidence is missing.

Do not use `deferred` for code that is merely large, tedious, or difficult.

## Naming confidence

- Proven behavior may receive a semantic name without an address suffix.
- Strongly inferred behavior may receive a narrow mechanical name, with the inference recorded in the subsystem document.
- Unknown class identity, domain meaning, or field ownership keeps its address or offset name.

Renaming `sub_` to vague words such as `handle`, `manager`, `thing`, or `primary` is not progress.

## Slice acceptance checklist

A slice is complete when:

- its files live under a defensible subsystem boundary;
- shared declarations have one canonical header;
- known raw offsets are represented by checked structure layouts;
- function and field names are supported by callers, data, or runtime behavior;
- remaining uncertainty is listed explicitly;
- the linker preserves original order and padding;
- `make verify` reports an exact ROM and zero mismatched C functions;
- the queue and subsystem document describe the new state.

## Failure handling

If a semantic cleanup changes generated code, compare the affected bytes and preserve the constraint in source comments. If the evidence needed for a name is absent, leave the placeholder and continue with other proven parts of the slice. If the whole boundary is wrong, revert that slice rather than building more structure on it.
