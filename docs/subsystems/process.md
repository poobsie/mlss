# Process subsystem

The process scheduler now lives under `src/process`, with its public interface and types under `include/process`. It maintains a priority-ordered doubly linked list and runs each enabled process according to a signed four-bit execution rate.

Positive rates mean multiple updates may run in one frame. Negative rates mean one update runs after the corresponding number of frames. `yielded` records whether a process has completed its work for the current scheduler pass. The scheduler keeps a separate `nextProcessToExecute` pointer so the current process can remove itself safely.

The following structure names are supported directly by scheduler behavior:

| Previous field | Recovered field | Evidence |
| --- | --- | --- |
| `startProcessLink` | `processListHead` | List traversal and insertion always begin here. |
| `nextProcess` | `next` | Forms the forward half of the doubly linked process list. |
| `previousProcess` | `previous` | Forms the backward half of the list and is used during removal. |
| `flag` | `enabled` | Disabled processes are skipped; enable and disable operations assign this bit. |
| `wait` | `yielded` | Set after the process finishes its work for a pass and cleared for the next frame. |
| `executeMax` | `executionRate` | Controls updates per frame or frames per update according to its sign. |
| `executeCounter` | `executionCounter` | Counts executions or elapsed scheduler frames against the rate. |
| `processCount` | `initialListPosition` | Captures the insertion position. It is not maintained as the list later changes. |

The base process definition is exposed as `gBaseProcessDefinition`. Its internal unknown fields remain address-neutral placeholders because the current scheduler only proves the update callback and data offset.

Address-named subclass destructors are grouped in `src/process/destructors.c`, but are not renamed yet. Their class identities cannot be established from the destructor wrappers alone.

The early destructor that installs the definition at `0x08CDBD98` is now in the same file and uses the shared `Process` layout and `process_remove` declaration. Its mechanical name retains the definition suffix until the owning process class is identified.

`TimedProcess` extends the base process with a limit, current count, and step byte. Its update increments the count, reports progress through `sub_801B7B0`, then removes itself with definition `0x08CDBD98` when the limit is reached.

`OwnedBufferProcess` extends the base process with an optional owned buffer. Its destructor installs definition `0x08CDBDA8`, frees the buffer when present, and removes the process. A global-slot helper destroys the instance stored at `0x03000D44` and clears that slot.

`ProcessCallbackOwner` is a separate process overlay with a signed resource identifier at `0x1C`, an optional callback at `0x20`, and its callback value at `0x24`. Its destructor installs descriptor `0x08CDC2D8`, releases the resource when the identifier is valid, invokes the callback when present, and removes the process.

Two upper-region constructors now use the canonical `Process` prefix and the full three-argument `process_add` contract. `process_initialize_tld` is supported by the `TLD` label passed at its recovered call site and installs definition `0x08CDC3C8`. The second installs definition `0x08CDC4A0`; its class remains mechanically named until a caller or descriptor identifies it.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports every linked C function exact, with zero mismatches.
