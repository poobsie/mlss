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

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports 1,301 linked C functions checked, 1,301 exact, and zero mismatches.
