# Graphics runtime

`GraphicsTransfer` is a 2 KiB source block followed by a destination pointer at offset `0x810`. `graphics_transfer_copy_2048_bytes` configures DMA channel 3 for one 512-word transfer from the block to that destination and reads the control register back after starting it.

`GraphicsRuntime` contains two known transfer pointers at offsets `0x2C` and `0x30`. The pair helper loads both through the runtime pointer stored at `0x03001024` and uploads them in order.

The pair helper deliberately reloads the global runtime pointer for the second transfer. Caching it shortens the generated function by four bytes, so the repeated load is part of the matching source contract.

Three destructor entry points install vtable `0x08CDD090` in a `GraphicsResourceOwner` and optionally free it. Their class-specific identities are not available in current C, so the variants remain lettered.

`graphics_upload_fixed_tile_regions` follows two resource pointers from an owning object and copies their sources to `0x06010400` and `0x060108C0`, with lengths `0x4C0` and `0x500`. The common transfer routine's final mode parameters are not yet named.

`sprite_heap_initialize_allocation_header` initializes the four-word header returned by `sprite_heap_alloc`: reference count 1, a copied owner value, the allocation's data pointer, and a cleared final word. The two copied values retain offset-bearing names until the sprite-heap allocator and consumers are recovered.

`CircularMask` owns a 240-line scanline-boundary buffer plus fixed-point screen and center offsets. `circular_mask_enable` and `circular_mask_disable` control the proven flag that selects between generating circular scanline bounds and clearing the buffer. Other flag bits and intermediate fields remain unnamed until their setters and update paths are decompiled.

The mask now also exposes its pixel radius at `0x30` and animated 8.8-scale value at `0x34`. The scale is used by nearby distance tests and transition interpolation; the setters for its target and step remain in assembly.

Two additional mask accessors clear the word at `0x20` and return the signed halfword at `0x1C`. Those members remain offset-named because their initialization and consumers do not yet establish whether they are coordinates, limits, or transition state.

`PositionBinding` connects 24.8 fixed-point world coordinates to an optional signed screen-coordinate pair. `position_binding_update_relative` subtracts a fixed-point origin and writes the integer X/Y results. Four identical callback entry points share that operation; their suffixes remain until the owning callback tables are recovered.

The early graphics staging path now has explicit source and destination layouts. It copies three 9-bit-masked values and three byte-sized components into the six interleaved halfwords at `0x02000014`. Two related process destructors install their terminal descriptors, stop DMA or clear VRAM as appropriate, release only the buffers that are present, and remove the process. Buffer names remain offset-based because their allocation sites are still assembly-only.

Thirteen high-address graphics helpers now have mechanical names for their proven operations: initializing and querying a replicated X/Y position state, resetting and ticking a two-halfword counter, initializing a binding record, packing RGB555 values, clearing an owned 8192-byte buffer, releasing an owned resource, clearing a value pair, and conditionally freeing the associated owners. Class identities remain unspecified where only destruction mechanics are visible.

`graphics_advance_by_nibble_width` advances a base value by four units for each significant hexadecimal digit, with zero occupying one digit. Adjacent numeric-glyph formatting loops use the result as their next layout position.

`GraphicsBlendTransition` exposes the mode, current value, and target used by the neighboring blend-register update routines. Its default initializer selects mode zero, clears the current value, and sets a sixteen-step target.

`graphics_extract_mode_relative_index` subtracts a base selected by bits 2 and 3 of the halfword at `0x02000008`, then extracts the normalized packed index. The global's owner and the index's concrete resource type remain unknown, so the name records only the proven transformation.

A second packed-value decoder obtains its mode halfword through an owner and source pointer before performing the related normalization. `GraphicsWorkspaceOwner` also exposes the allocation at offset `0x288`; its destructor copies the current global result to `0x02000000`, frees that workspace, and conditionally frees the owner. Neither layout is assigned a narrower rendering role without recovered construction code.

`SpriteVisibilityController` exposes its owned sprite at offset `0x0C` and the comparison value at `0x34` used by the neighboring assembly visibility update. The recovered refresh wrapper runs the shared setup, visibility update, and finalization sequence; the cleanup helper releases and clears that sprite. A narrower gameplay or screen identity is not visible in current callers.

`graphics_terminate_process_label_at_2` writes the terminator in the third byte of the base process label. Its placement beside the constructor and destructor using graphics descriptor `0x08CDC2C8` establishes ownership; the name records the exact base-field operation instead of guessing why that process uses a two-character label.

Three final bucket-02 wrappers now have graphics ownership. `graphics_apply_staging_source` copies the established six staging values and runs the four adjacent configuration passes on the same source. `graphics_deactivate_linked_visual` performs the shared visual cleanup before unlinking the visual from the active graphics list. `graphics_update_global_resource_fcc_layer_4_mask_16` invokes the two proven update operations on the graphics resource held at `0x03000FCC`; the address and numeric arguments remain explicit because the underlying resource layout is still assembly-only.

`GraphicsCompactStagingSource` captures a second four-halfword staging layout at offsets `0x30` through `0x36`. Its copy helper masks the first pair to nine bits and the second pair to eight bits before writing the interleaved staging region at `0x02000010`. The values stay structurally named until the assembly routines that consume this compact format are recovered.

The high-address runtime group now includes compact resource cleanup and state helpers shared with UI code. Their typed owners expose only the fields touched by these leaves; resource and screen identities remain unresolved where callers are still assembly-only.

`GraphicsPositionState` now records the shared position words, output sprite pointer, selection flags, and height-source pointer used by the adjacent graphics helpers. The recovered reset clears the proven state fields, while the shared-output helper writes the current value pair to each selected slot at `0x02000010`. The individual flag meanings remain unknown.

`graphics_resource_owner_initialize` installs descriptor `0x08CDD060` and clears its transfer pointer. `graphics_fill_background_palettes` replicates one 16-bit value across both 512-byte background palette banks using the BIOS fill operation.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports 1,630 linked C functions checked, 1,630 exact, and zero mismatches.
