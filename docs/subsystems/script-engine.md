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

## Remaining script work

The dispatch wrappers around `0x0808ECDC` still expose an object field at offset `0x28`, a signed status at nested offset `0xEC`, and a continuation callback at offset `0x68`. Those relationships need a shared type before the wrappers can be named safely.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports 1,301 linked C functions checked, 1,301 exact, and zero mismatches.
