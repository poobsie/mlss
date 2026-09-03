# Runtime bootstrap

The recovered bootstrap code now lives under `src/runtime` instead of the generic `runtime_helpers.c` and `runtime_tail.c` files.

`runtime_memory_state_init` resets three pieces of runtime state before the process system starts. The value copied from ROM offset `0xF4` is also used as the upper boundary of the IWRAM heap. The other two globals are still address-named because much of their behavior remains in assembly.

`runtime_relocated_code_init` allocates space for the ARM routine stored from `0x08000534` through `0x0800063B`, copies it into writable memory, and installs the resulting function pointer. Several screen loaders call that relocated routine with source data and a destination. Its exact data format is not yet proven, so the routine is described mechanically rather than named as a specific decompressor.

`decimal_digit_count` has one known caller and computes the number of decimal positions needed for a nonnegative limit. It remains in the same object as the bootstrap initializer because the original functions are contiguous; splitting them introduces executable-section padding and breaks the exact ROM match.

Three generic callback forwarders now live in `src/runtime/callback_forwarders.c`. `RuntimeCallbackTable` records the proven callback slot at offset `0x1A0`; each trampoline loads that callback and invokes it with the original argument, table, and address of the callback slot. The entry points remain address-named because their owning table types are not yet distinguishable.

`src/runtime/interrupts.c` owns interrupt callback installation. Null callbacks are replaced by a no-op callback, installation is protected by `REG_IME`, and selector 2 uses the callback slot embedded in `gGameState` while other selectors address the callback table beginning at `0x03000014`.

`src/runtime/game_state.c` contains the recovered play-time setter and its adjacent no-op. The setter writes `GameState.playTime` and marks bit 0 of the still-partially-understood byte at offset `0x889`. `src/runtime/state_clear.c` clears two 32-bit words at `0x03000D28`; the state owner remains unknown, so the address is retained in its name.

The explicit zero padding after the two no-op functions is required. Splitting the old mixed source objects otherwise causes the assembler to fill each alignment gap with a Thumb `nop`, changing two non-function halfwords even though every function still matches.

Eight additional side-effect-free callback entries live in `src/runtime/noop_callbacks.c`. They retain their `nullsub_` symbols because their owning callback tables are still in assembly; naming them for a guessed subsystem would provide false certainty.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports 1,301 linked C functions checked, 1,301 exact, and zero mismatches.
`pointer_list_count_value` walks a singly linked list and returns the number of nodes whose payload pointer equals the requested value. The second word in each node remains unknown; traversal proves only the payload at `0x00` and next pointer at `0x08`.

`DefinitionState` is a six-word base overlay used by several differently sized late-runtime allocations. Two initializer families clear the same fields and install distinct definitions while setting value `0x10` to `0x7E00`; paired reset functions replace the definition and clear state. The initializer return types now match callers that retain `r0` as the initialized object pointer.

`word_triplet_copy` copies one exact three-word value from source to destination. The words are named by order because its current callers prove the value width and copy direction, but not the payload semantics.

`runtime_release_global_resource_callback` adapts the no-argument global resource-release operation to callback sites that supply an unused object pointer. The underlying resource owner is still identified only through globals, so the name does not claim a narrower subsystem.

`DefinitionSlot` is the one-word payload embedded in late-runtime list nodes. Its initializer installs definition `0x08CDD0B8`; the paired assembly destructor now has the semantic alias `definition_slot_destroy`.
