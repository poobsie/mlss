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

Five high-address helpers now have narrow runtime overlays. They capture the low byte of `VCOUNT`, select an indexed pointer from the table at `0x03001070`, set the pointer slot at `0x03001074`, and latch bytes `0x16` or `0x1A` while clearing their associated flag fields. These structural names deliberately stop short of assigning audio or graphics ownership without callers that prove it.

Five adjacent definition and adapter helpers now live in `runtime/high_definitions.c`. They expose a forced-mode wrapper, a definition target getter, a descriptor-installing destructor, a default-initializer adapter, and a four-word definition initializer. Their names record proven mechanics and definition addresses because the concrete classes are not visible in current C.

`definition_slot_destroy` now replaces the slot definition with `0x08CDD0B8` and conditionally frees the containing allocation. Two callers with the same intrusive-list-owner layout now have typed destructors; both install descriptor `0x08CDD108`, clear the owned list through the existing runtime routine, and honor the low-bit free flag. The two owner classes remain distinct because their surrounding construction paths have not established a shared semantic identity.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports 1,648 linked C functions checked, 1,648 exact, and zero mismatches.
`pointer_list_count_value` walks a singly linked list and returns the number of nodes whose payload pointer equals the requested value. The second word in each node remains unknown; traversal proves only the payload at `0x00` and next pointer at `0x08`.

`DefinitionState` is a six-word base overlay used by several differently sized late-runtime allocations. Two initializer families clear the same fields and install distinct definitions while setting value `0x10` to `0x7E00`; paired reset functions replace the definition and clear state. The initializer return types now match callers that retain `r0` as the initialized object pointer.

`word_triplet_copy` copies one exact three-word value from source to destination. The words are named by order because its current callers prove the value width and copy direction, but not the payload semantics.

`runtime_release_global_resource_callback` adapts the no-argument global resource-release operation to callback sites that supply an unused object pointer. The underlying resource owner is still identified only through globals, so the name does not claim a narrower subsystem.

`DefinitionSlot` is the one-word payload embedded in late-runtime list nodes. Its initializer installs definition `0x08CDD0B8`; the paired assembly destructor now has the semantic alias `definition_slot_destroy`.

`RuntimeCallbackPacket` records two signed arguments and a callback at offset `0x14`. Its recovered trampoline invokes that callback with the stored argument pair, replacing the former raw byte offsets and cast-through-`void` expression.

`runtime_dereference_pointer` is the narrow indirect-pointer adapter used by two assembly construction paths. Those callers do not expose a common owned type, so the helper states the exact pointer operation without inventing object semantics.

`runtime_release_global_state_ff4` releases and clears the shared pointer at `0x03000FF4`. Many object and screen paths consume that state, but its allocation and copying logic do not yet prove a narrower class name, so the global suffix remains explicit.

The same runtime module now owns the heap releases for global slots `0x03000FB4`, `0x03000FC4`, and `0x03000FC0`. The last operation clears its slot after release; the first two preserve the original value. Address suffixes remain because allocation sites have not established narrower resource identities.

The module now also releases and clears global slot `0x03000FBC`. Its grouped teardown first invokes the existing `0x03000FB4` release, then releases and clears `0x03000FB8` and `0x03000FBC`. The allocation code proves that these slots participate in one resource setup, but not enough payload structure is recovered to replace their address suffixes safely.

`RuntimeIntrusiveList` and `RuntimeIntrusiveNode` recover the generic head, tail, count, previous, and next fields used near `0x08163CD4`. `runtime_intrusive_list_append_unique` first rejects a node already present in the list, then appends it and increments the count. The node payload at offset `0` is intentionally unnamed because this routine never reads it.

Additional high-address leaves now copy and initialize the established three-word runtime value and bridge it into adjacent UI and graphics owners. Field names remain structural because no recovered consumer proves a narrower payload type.
