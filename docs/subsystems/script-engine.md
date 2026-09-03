# Script engine

## Animation script streams

The first recovered boundary is the animation-script state shared by the interpreters around `0x080DF2B0` through `0x080E1AF0`. `AnimationScriptState` captures its proven 24-byte prefix: an update callback, owner pointer, byte-stream cursor, signed wait timer, and three signed origin coordinates. The word at offset zero is still `unknown0`; no current C establishes its meaning.

Three transition helpers now live in `src/script/animation_transitions.c`, with their shared layout and interface in `include/script/animation_script.h`. Each reads the initial 16-bit wait value, advances the stream by two bytes, selects the corresponding interpreter, and immediately executes it.

The stream names are intentionally structural. The interpreter at `animation_script_update_10_byte_stream` consumes an identifier, three position values, and a wait value from each 10-byte record. `animation_script_update_4_byte_stream` consumes an identifier and wait value from each four-byte record while using the state's origin coordinates. `animation_script_update_command_stream` handles a variable-width opcode stream. Higher-level animation names require the tables or owning object types that select each format.

| Previous name | Recovered name | Evidence |
| --- | --- | --- |
| `sub_80E1908` | `animation_script_enter_10_byte_stream` | Reads the initial wait word and selects the interpreter that advances by ten bytes per record. |
| `sub_80E1924` | `animation_script_enter_4_byte_stream` | Reads the initial wait word and selects the interpreter that advances by four bytes per record. |
| `sub_80E1940` | `animation_script_enter_command_stream` | Reads the initial wait word and selects the variable-width opcode interpreter. |
| `sub_80DF5EC` | `animation_script_update_10_byte_stream` | Reads record fields at offsets 0, 2, 4, 6, and 8, then advances by ten bytes. |
| `sub_80E1AF0` | `animation_script_update_4_byte_stream` | Reads fields at offsets 0 and 2, then advances by four bytes. |
| `sub_80DF2B0` | `animation_script_update_command_stream` | Dispatches a variable-width stream through a 23-entry opcode table. |

## Field-object command handlers

`ScriptCommandContext` now captures the proven pointer at offset `0x14`, and `ScriptObjectRegistry` captures the object-pointer array beginning at registry offset `0x28`. The recovered handlers can consequently select `objectRegistry->objects[index]` instead of reconstructing that relationship with byte arithmetic.

Three commands use registry slot 183, the pointer at offset `0x304`. Its role is not established by current callers, so the constant deliberately retains the slot number. The operations applied to it at `0x080F0BC0`, `0x080F0BD8`, and `0x080F0BF0` also remain address-named pending recovery of the tables consumed by their callees.

| Previous name | Recovered name | Evidence |
| --- | --- | --- |
| `sub_80EA9A8` | `script_command_set_input_mask` | Passes the command's 16-bit argument to the routine that stores the mask used by the input test at `0x0801B084`. |
| `sub_80F1478` | `script_command_set_object_configuration` | Selects an object by command-supplied index and stores the 16-bit argument in its configuration field at offset `0x26C`. |
| `script_cmd_80F17C4` | `script_command_set_object_mode` | Selects an object by command-supplied index and applies the supplied three-bit mode through `sub_8047364`. |
| `sub_80F17DC` | `script_command_advance_object_mode` | Selects an object by command-supplied index and invokes the paired no-argument mode transition routine `sub_80473DC`. |

The former `script_dispatch_helpers.c` cluster was found to be object lifecycle code and moved to the object-runtime queue. The currently recovered script C now has subsystem placement and shared state types; further script work depends on converting adjacent assembly or recovering command data tables.

## Command execution state

`ScriptExecutionState` captures the command interpreter fields proven by the handlers around `0x080EA514` through `0x080EB248`. The interpreter has a current cursor, an end cursor, one saved return cursor, a 16-word value stack and depth, a wait timer, and two parallel value/flag/mode channels. The purpose and units of the two channels are not yet established, so their names remain structural instead of pretending they are coordinates or animation state.

The extracted command handlers now expose stack push/pop, stored-value assignment, call/end control flow, current-object configuration, a word-copy operation, a successful no-op, and a two-argument forwarding command. The stack access retains explicit byte-offset arithmetic because the original compiler otherwise emits two extra instructions; the shared structure documents the relationship while the source preserves the exact ROM bytes.

| Previous name | Recovered name | Evidence |
| --- | --- | --- |
| `sub_80EA514` | `script_state_set_secondary_channel` | Writes the second value pair, flag halfword, and mode byte. |
| `sub_80EA530` | `script_state_set_primary_channel` | Writes the first value pair, clears the return cursor, and writes the first flag/mode pair. |
| `sub_80EA904` | `script_command_pop_value` | Decrements the depth byte and clears the vacated 32-bit stack entry. |
| `sub_80EA91C` | `script_command_store_value` | Copies the command argument into the interpreter's standalone stored word. |
| `sub_80EA928` | `script_command_push_value` | Writes the argument at the current stack depth, then increments the depth. |
| `script_cmd_call` | `script_command_call` | Optionally saves the current cursor and jumps to the command-supplied cursor. |
| `script_cmd_end` | `script_command_end` | Marks the current cursor as the end cursor and clears the saved return cursor. |
| `sub_80F14C4` | `script_command_set_current_object_configuration` | Applies the supplied 16-bit configuration to the object passed as the active command target. |
| `sub_80F1AE4` | `script_command_copy_word` | Copies one command-supplied word to the destination selected by the dispatcher. |
| `sub_80F7E80` | `script_command_noop` | Returns the interpreter's successful-completion value without changing state. |
| `sub_80F80B4` | `script_command_forward_pair` | Forwards two consecutive command words to the same callee. The callee's semantics remain unknown. |

The execution state now exposes the saved cursor at offset `0x14`. Three wait handlers restore that cursor and yield when their respective condition becomes true: the primary actor height test, field flag `0x291` bit 0, or a context-owned asynchronous operation. `script_command_branch_if_condition` decodes its aligned condition, operand, and target-cursor record and updates the current cursor only when the shared condition evaluator succeeds.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports 1,368 linked C functions checked, 1,368 exact, and zero mismatches.
