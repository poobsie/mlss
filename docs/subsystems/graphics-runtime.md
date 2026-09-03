# Graphics runtime

`GraphicsTransfer` is a 2 KiB source block followed by a destination pointer at offset `0x810`. `graphics_transfer_copy_2048_bytes` configures DMA channel 3 for one 512-word transfer from the block to that destination and reads the control register back after starting it.

`GraphicsRuntime` contains two known transfer pointers at offsets `0x2C` and `0x30`. The pair helper loads both through the runtime pointer stored at `0x03001024` and uploads them in order.

The pair helper deliberately reloads the global runtime pointer for the second transfer. Caching it shortens the generated function by four bytes, so the repeated load is part of the matching source contract.

Three destructor entry points install vtable `0x08CDD090` in a `GraphicsResourceOwner` and optionally free it. Their class-specific identities are not available in current C, so the variants remain lettered.

`graphics_upload_fixed_tile_regions` follows two resource pointers from an owning object and copies their sources to `0x06010400` and `0x060108C0`, with lengths `0x4C0` and `0x500`. The common transfer routine's final mode parameters are not yet named.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports 1,301 linked C functions checked, 1,301 exact, and zero mismatches.
