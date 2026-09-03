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

## Remaining script work

The recovered command helpers and dispatch wrappers still use raw pointer arithmetic. The next slice should identify the command-handler context at offset `0x14` and the indexed object collection it owns before naming individual operations.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports 1,301 linked C functions checked, 1,301 exact, and zero mismatches.
