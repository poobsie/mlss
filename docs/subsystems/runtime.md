# Runtime bootstrap

The recovered bootstrap code now lives under `src/runtime` instead of the generic `runtime_helpers.c` and `runtime_tail.c` files.

`runtime_memory_state_init` resets three pieces of runtime state before the process system starts. The value copied from ROM offset `0xF4` is also used as the upper boundary of the IWRAM heap. The other two globals are still address-named because much of their behavior remains in assembly.

`runtime_relocated_code_init` allocates space for the ARM routine stored from `0x08000534` through `0x0800063B`, copies it into writable memory, and installs the resulting function pointer. Several screen loaders call that relocated routine with source data and a destination. Its exact data format is not yet proven, so the routine is described mechanically rather than named as a specific decompressor.

`decimal_digit_count` has one known caller and computes the number of decimal positions needed for a nonnegative limit. It remains in the same object as the bootstrap initializer because the original functions are contiguous; splitting them introduces executable-section padding and breaks the exact ROM match.

Three generic callback forwarders now live in `src/runtime/callback_forwarders.c`. `RuntimeCallbackTable` records the proven callback slot at offset `0x1A0`; each trampoline loads that callback and invokes it with the original argument, table, and address of the callback slot. The entry points remain address-named because their owning table types are not yet distinguishable.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports 1,301 linked C functions checked, 1,301 exact, and zero mismatches.
