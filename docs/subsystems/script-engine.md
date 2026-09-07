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

Two adjacent object commands now expose the callback/configuration protocol shared by
indexed and active-object dispatch. Each command selects one of two callback entries at
offsets `0x90` and `0x98` in the object's callback table. An entry supplies both the
callback and a signed adjustment from the object base to the callback's component.
After dispatch, both commands apply an animation value and start the same interaction
path with the object's visual resource.

| Previous name | Recovered name | Evidence |
| --- | --- | --- |
| `sub_80F1738` | `script_command_configure_indexed_object_callback` | Selects an object from the context registry, chooses the primary or secondary callback from the command selector, then configures its animation and interaction. |
| `sub_80F1998` | `script_command_configure_object_callback` | Applies the same callback/configuration sequence to the active object and target supplied by the dispatcher. |

The callback entry layout and command-field roles are established by the mirrored
handlers. The gameplay identity of the callbacks, the visual resource at object offset
`0x294`, and the interaction helper at `sub_80EA60C` remain unresolved, so those names
stay structural.

## Command execution state

`ScriptExecutionState` captures the command interpreter fields proven by the handlers around `0x080EA514` through `0x080EB248`. The interpreter has a current cursor, an end cursor, one saved return cursor, a 16-word value stack and depth, a wait timer, and two parallel value/flag/mode channels. The purpose and units of the two channels are not yet established, so their names remain structural instead of pretending they are coordinates or animation state.

The extracted command handlers now expose stack push/pop, stored-value assignment,
call/end control flow, wait-timer control, channel replacement, current-object
configuration, a word-copy operation, a successful no-op, and a two-argument
forwarding command. The stack access retains explicit byte-offset arithmetic because
the original compiler otherwise emits two extra instructions; the shared structure
documents the relationship while the source preserves the exact ROM bytes.

| Previous name | Recovered name | Evidence |
| --- | --- | --- |
| `sub_80EA514` | `script_state_set_secondary_channel` | Writes the second value pair, flag halfword, and mode byte. |
| `sub_80EA530` | `script_state_set_primary_channel` | Writes the first value pair, clears the return cursor, and writes the first flag/mode pair. |
| `sub_80EA550` | `script_state_clear_secondary_channel` | Clears the second value channel and, when primary flag `0x0008` is set, clears flag `0x0004` in the linked execution state. |
| `sub_80EA584` | `script_state_replace_secondary_channel` | Clears the prior secondary-channel relationship before installing its replacement. |
| `sub_80EA5C8` | `script_state_replace_primary_channel` | Clears the prior secondary-channel relationship before installing a primary-channel replacement. |
| `sub_80EA778` | `script_state_tick_wait_timer` | Decrements the wait timer and clears primary flag `0x0010` when it reaches zero. |
| `sub_80EA904` | `script_command_pop_value` | Decrements the depth byte and clears the vacated 32-bit stack entry. |
| `sub_80EA91C` | `script_command_store_value` | Copies the command argument into the interpreter's standalone stored word. |
| `sub_80EA928` | `script_command_push_value` | Writes the argument at the current stack depth, then increments the depth. |
| `script_cmd_call` | `script_command_call` | Optionally saves the current cursor and jumps to the command-supplied cursor. |
| `script_cmd_wait_frames` | `script_command_wait_frames` | Loads the wait timer and marks primary flag `0x0010` while a nonzero delay is pending. |
| `script_cmd_end` | `script_command_end` | Marks the current cursor as the end cursor and clears the saved return cursor. |
| `sub_80F14C4` | `script_command_set_current_object_configuration` | Applies the supplied 16-bit configuration to the object passed as the active command target. |
| `sub_80F1AE4` | `script_command_copy_word` | Copies one command-supplied word to the destination selected by the dispatcher. |
| `sub_80F7E80` | `script_command_noop` | Returns the interpreter's successful-completion value without changing state. |
| `sub_80F80B4` | `script_command_forward_pair` | Forwards two consecutive command words to the same callee. The callee's semantics remain unknown. |
| `sub_80F087C` | `script_wait_for_battle_flag_208_10` | Yields and restores the saved cursor until battle-control flag `0x10` at offset `0x208` is set. |
| `sub_80F0914` | `script_command_set_battle_flag_12d` | Selects battle-control flag `0x10` or `0x20` at offset `0x12D`. |
| `sub_80F0938` | `script_command_set_battle_flags_12c` | Applies the established flags-mode operation, with `-32` selecting the dedicated flag `0x01` path. |
| `sub_80F0984` | `script_wait_for_battle_control_ready` | Restores the saved cursor and yields when the battle-control readiness predicate returns one. |
| `sub_80F0BA4` | `script_command_configure_object_slot_183` | Forwards two command bytes to the object in the already established registry slot 183. |
| `sub_80EAA5C` | `script_command_forward_input_mask` | Forwards the signed command value and the input runtime's halfword at offset `0x2E` through the shared six-argument command bridge. The mask's individual bit meanings remain unknown. |
| `sub_80EAA84` | `script_command_forward_selected_input_mask` | Selects the input runtime halfword at offset `0x2A` or `0x28`, then forwards it with the signed command value through the shared command bridge. The selector identities and mask bits remain unknown. |
| `sub_80EAB98` | `script_command_apply_arithmetic_and_forward` | Applies one of twelve arithmetic, shift, bitwise, or boolean operations to the command's mutable result word, then forwards that result and the signed command value through the shared bridge. Opcode zero leaves the result unchanged. |
| `sub_80EACDC` | `script_command_forward_selected_runtime_byte` | Selects one of four signed bytes at offsets `0x22` through `0x25` in the runtime referenced by `0x03000D44`, then forwards it through the shared command bridge. The selector identities remain unknown. |
| `sub_80EAD98` | `script_command_set_runtime_direction_sign` | Stores `1` or `0xFF` in runtime byte `0x29` according to whether the command argument is zero. The owner of the runtime record remains unresolved. |
| `sub_80EADC4` | `script_command_apply_runtime_signed_triplet` | Reads three signed command bytes at four-byte intervals and applies them to the runtime selected through `0x03000D44`. The callee's gameplay operation remains unresolved. |
| `sub_80EADEC` | `script_command_wait_for_runtime_slot` | Scans four 16-byte runtime slots and yields after restoring the saved cursor when an active slot has the requested identifier. Identifier `0x3F` accepts any active slot. |
| `sub_80EAE30` | `script_command_dispatch_runtime_slot` | Finds the active runtime slot with the requested identifier and dispatches its zero-based slot index through the established owner helper. The slots' gameplay identity remains unknown. |
| `sub_80E8EE0` | `script_runtime_slot_hide` | Hides the sprite owned by one indexed runtime slot and clears the slot's active byte. |
| `sub_80EAE70` | `script_command_forward_runtime_byte_30` | Forwards the signed command value and byte `0x30` of the runtime selected through `0x03000FB8` through the same command bridge. The byte's gameplay identity remains unknown. |
| `sub_80EAE9C` | `script_command_branch_if_runtime_byte_30_equals` | Branches when runtime byte `0x30` equals the command's full-width expected value. |
| `sub_80EAEBC` | `script_command_branch_on_resource_flag` | Tests the command-selected bit in resource byte `0x1B2` and replaces the execution cursor with the supplied target when that bit is set. The individual bit meanings remain unknown. |
| `sub_80EB048` | `script_command_set_runtime_byte_32` | Stores the low byte of the command argument in runtime byte `0x32`. |
| `sub_80EAEF8` | `script_command_control_sound_effect` | Starts, stops, or waits for a sound effect according to the command operation. A zero sound identifier on the stop path stops all sound effects. |
| `sub_80EAF4C` | `script_command_control_music` | Starts or resumes music, or changes its volume or tempo. The command's player, value, and fade fields retain structural names until the bytecode format is recovered. |
| `sub_80EB05C` | `script_command_control_resource_wait` | Starts an owner-scoped resource operation or yields until bit `0x04` in the selected 76-byte resource record clears. The record's owner and flag meaning remain unresolved. |
| `sub_80EB09C` | `script_command_configure_graphics_resource` | Applies one of five graphics-resource modes, or restores the resource's saved mode for larger values, then clears runtime byte `0x31`. |
| `sub_80F0540` | `script_command_clear_field_runtime_flag` | Clears a command-selected bit in the field runtime's 16-bit flag bank at offset `0x54A`. The individual flag meanings remain unknown. |
| `sub_80F0794` | `script_command_dispatch_field_object_operation` | Dispatches operation values 5 through 11 to established object-registry helpers and forwards other values through the registry's generic operation path. |
| `sub_80F0814` | `script_command_dispatch_field_object_control` | Decodes a packed group and action bit, invoking one of two object-registry control pairs and yielding while either paired query remains active. |
| `sub_80F08C0` | `script_command_branch_on_field_queries` | Runs the established field query sequence and branches according to whether all three queries report inactive. |
| `sub_80EA88C` | `script_command_call_system_service` | Operation zero forwards three command words to the established system service. Its service-specific meaning remains unresolved. |
| `sub_80EA8A4` | `script_command_control_system` | Dispatches four system-control operations, including the established game reset path and three still-address-named controls. |
| `sub_80EAB20` | `script_command_update_key_masks` | Sets bits in either script input mask or clears bits in the second mask according to the command operation. |
| `script_cmd_conditional_jump` | `script_command_conditional_jump` | Evaluates the command's typed condition record and replaces the cursor when the result matches the expected byte. |
| `sub_80EAEE0` | `script_command_set_sound_effect_volume` | Applies the command's volume byte to the selected sound effect. |
| `script_cmd_wait_for_user_input` | `script_command_wait_for_user_input` | Yields until the current key state intersects the script input masks, then records which configured input fired. |
| `sub_80F06EC` | `script_command_initialize_field_registry` | Initializes the field object registry through the established setup path. |
| `sub_80F0744` | `script_command_control_field_registry` | Dispatches a small command family over the field object registry. |
| `sub_80F095C` | `script_command_control_battle_registry` | Dispatches the parallel command family over the battle object registry. |
| `sub_80F1088` | `script_command_apply_flagged_effects` | Applies command-selected effects to the objects admitted by the command's flag mask. |
| `sub_80F10E0` | `script_command_branch_on_indexed_object_state` | Selects an object by index and branches when its state matches the command value. |
| `sub_80F110C` | `script_command_branch_on_object_state` | Performs the same state branch against the active object supplied by the dispatcher. |
| `sub_80F143C` | `script_command_control_indexed_object_runtime` | Selects an object by index and applies the requested runtime control operation. |
| `sub_80F1490` | `script_command_control_object_runtime` | Applies the parallel runtime control operation to the active object. |
| `sub_80F1A1C` | `script_command_control_object_pair` | Applies the selected control operation to the command's paired objects. |
| `sub_80F1AEC` | `script_command_branch_on_field_value_54c` | Branches according to the command's comparison against the structural field runtime value at offset `0x54C`. |
| `sub_80F1B14` | `script_command_dispatch_selected_runtime` | Selects a runtime record and dispatches the command operation through its established control path. |
| `sub_80F1BA4` | `script_command_branch_on_selected_runtime_flag` | Branches according to the selected runtime record's tested flag. |
| `sub_80F112C` | `script_command_control_object_motion` | Forwards the selected object, operation, and payload to the established three-argument motion-control routine. Individual operation meanings remain unknown. |
| `sub_80F7BB4` | `script_command_wait_for_matching_visual` | Yields while any of four visual-resource records is active with the requested identifier. Identifier `0x3F` is the established wildcard on this wait path. |
| `sub_80F7C3C` | `script_command_control_value_transfer` | Prepares the field value-transfer service in mode 0 or 1, or commits the pending transfer, according to the command operation. Other operation values are no-ops. |
| `sub_80F7C78` | `script_command_wait_for_value_transfer` | Yields until the value-transfer status and its companion readiness predicate clear, field flag `0x20` at offset `0x2BF` is clear, and the offset-`0x2F0` resource pointer is null. The latter roles remain structurally named. |
| `sub_80F7CD0` | `script_command_start_value_transfer` | Starts a value-transfer operation with the command's duration, flags, and dispatch value. The signed selector chooses kind 0 or 4 and whether the service value is zero or `0x7FFF`. |
| `sub_80F7D0C` | `script_command_start_display_value_transfer` | Starts the display-derived value-transfer variant with the command's dispatch value and the same signed-selector mapping. |
| `sub_80F8438` | `script_command_forward_selected_object_index` | Selects one of the six indexed field objects by the requested threshold/span mode, then forwards that object's index through the shared script result bridge. |
| `sub_80F84AC` | `script_command_forward_object_property` | Queries the command-selected property of an indexed field object, then forwards the result through the same bridge. The property selector meanings remain unresolved. |

The execution state now exposes the saved cursor at offset `0x14`. Three wait handlers restore that cursor and yield when their respective condition becomes true: the primary actor height test, field flag `0x291` bit 0, or a context-owned asynchronous operation. `script_command_branch_if_condition` decodes its aligned condition, operand, and target-cursor record and updates the current cursor only when the shared condition evaluator succeeds.

`script_state_enable_primary_flag_2` is shared by six setup-oriented command handlers. Each caller passes the command execution state as its third argument, and the helper sets bit `0x0002` in `primaryFlags`. The gameplay meaning of that bit remains unknown, so the numeric identity is retained instead of assigning a speculative state name. The other three callback arguments are unused by this helper and remain structurally typed.

`script_command_return_from_battle` now exposes the final miscellaneous script handler. A nonzero command argument marks field-runtime return flag `0x02`, then the handler delegates to the ordinary script return operation using the context embedded at offset `0x1C`. The original `script_cmd_btl_return` symbol remains available to assembly through the semantic alias.

The runtime-slot dispatcher now shares a typed 16-byte slot layout with its hide operation. The layout establishes the owned sprite pointer, identifier, delayed-hide timer, and active byte. Coordinate and timer maintenance remain in assembly because the current compiler shapes do not reproduce them exactly; the slots' gameplay identity is still unresolved.

The animation runtime now exposes the ordinary state maintenance around the
stream interpreters. `animation_attachment_flush_pending` consumes the pending
command and argument from an attachment owner, clears both slots, and dispatches
the command only while the observed attachment flag group is active.
`animation_script_tick_terminal_wait` counts down the terminal wait and clears
the update callback after committing the shared runtime value.
`animation_offset_update` advances two fixed-point display offsets and publishes
their integer components. `animation_script_apply_origin` either applies the
script origin to its action or clears the update callback once that action is
finished. The attachment flag bits and the two published display destinations
remain structurally named because their higher-level consumers are not yet in C.

The adjacent scene runtime now exposes its process teardown, layer query and
configuration, VRAM clearing, and readiness polling as ordinary C. The layer
record is represented by a narrow overlay containing only the two observed
pointers. The optional record contributes its halfword at offset `0x0A` to the
layer configuration call. The meanings of that halfword and the global word
cleared by the configuration and readiness paths remain unresolved, so those
fields retain offset-based names.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports every linked C function exact, with zero mismatches.
