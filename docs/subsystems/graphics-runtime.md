# Graphics runtime

`GraphicsTransfer` is a 2 KiB source block followed by a destination pointer at offset `0x810`. `graphics_transfer_copy_2048_bytes` configures DMA channel 3 for one 512-word transfer from the block to that destination and reads the control register back after starting it.

`GraphicsRuntime` contains two known transfer pointers at offsets `0x2C` and `0x30`. The pair helper loads both through the runtime pointer stored at `0x03001024` and uploads them in order.

The pair helper deliberately reloads the global runtime pointer for the second transfer. Caching it shortens the generated function by four bytes, so the repeated load is part of the matching source contract.

Three destructor entry points install vtable `0x08CDD090` in a `GraphicsResourceOwner` and optionally free it. Their class-specific identities are not available in current C, so the variants remain lettered.

`graphics_upload_fixed_tile_regions` follows two resource pointers from an owning object and copies their sources to `0x06010400` and `0x060108C0`, with lengths `0x4C0` and `0x500`. The common transfer routine's final mode parameters are not yet named.

`sprite_heap_initialize_allocation_header` initializes the four-word header returned by `sprite_heap_alloc`: reference count 1, a copied owner value, the allocation's data pointer, and a cleared final word. The two copied values retain offset-bearing names until the sprite-heap allocator and consumers are recovered.

`CircularMask` owns a 240-line scanline-boundary buffer plus fixed-point screen and center offsets. `circular_mask_enable` and `circular_mask_disable` control the proven flag that selects between generating circular scanline bounds and clearing the buffer. Other flag bits and intermediate fields remain unnamed until their setters and update paths are decompiled.

The mask now also exposes its pixel radius at `0x30` and animated 8.8-scale value at `0x34`. The scale is used by nearby distance tests and transition interpolation; the setters for its target and step remain in assembly.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports 1,301 linked C functions checked, 1,301 exact, and zero mismatches.
