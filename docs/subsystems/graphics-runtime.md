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

`SpriteVisibilityController` exposes owned sprites at offsets `0x08` and `0x0C`
and the comparison value at `0x34` used by the neighboring assembly visibility
update. Its initializer clears the proven state, installs the two resource
tables, and selects the initial sentinel values. The refresh callback forwards
to the established update sequence, while the paired cleanup helpers release
each sprite. The destructor restores the class descriptor, runs both cleanup
paths, and honors the standard low-bit heap release flag. A narrower gameplay
or screen identity is not visible in current callers.

The adjacent `GraphicsResourceList` exposes its doubly linked head and tail,
active-node count, and class descriptor. Its membership predicate walks forward
from the head through each node's next link. The destructor restores the class
descriptor, delegates list clearing to the established cleanup routine, and
honors the standard low-bit heap release flag.

`graphics_terminate_process_label_at_2` writes the terminator in the third byte of the base process label. Its placement beside the constructor and destructor using graphics descriptor `0x08CDC2C8` establishes ownership; the name records the exact base-field operation instead of guessing why that process uses a two-character label.

Three final bucket-02 wrappers now have graphics ownership. `graphics_apply_staging_source` copies the established six staging values and runs the four adjacent configuration passes on the same source. `graphics_deactivate_linked_visual` performs the shared visual cleanup before unlinking the visual from the active graphics list. `graphics_update_global_resource_fcc_layer_4_mask_16` invokes the two proven update operations on the graphics resource held at `0x03000FCC`; the address and numeric arguments remain explicit because the underlying resource layout is still assembly-only.

`field_transfer_graphics_resource` measures an indexed graphics resource, runs the installed relocated data callback, and returns the measured size. Callers can retain the callback output as a heap allocation or request a temporary allocation that is copied into their supplied destination and released. The callback's underlying data format remains unnamed.

`GraphicsCompactStagingSource` captures a second four-halfword staging layout at offsets `0x30` through `0x36`. Its copy helper masks the first pair to nine bits and the second pair to eight bits before writing the interleaved staging region at `0x02000010`. The values stay structurally named until the assembly routines that consume this compact format are recovered.

The high-address runtime group now includes compact resource cleanup and state helpers shared with UI code. Their typed owners expose only the fields touched by these leaves; resource and screen identities remain unresolved where callers are still assembly-only.

`GraphicsPositionState` now records the shared position words, output sprite pointer, selection flags, and height-source pointer used by the adjacent graphics helpers. The recovered reset clears the proven state fields, while the shared-output helper writes the current value pair to each selected slot at `0x02000010`. The individual flag meanings remain unknown.

Two position-state initializers now preserve the current value pair and install a new target. The timed form accepts its duration directly and selects state 1 or 2 from the caller's final argument. The distance form computes an 8.8-scaled delta, delegates the square-root operation through the existing runtime callback, clamps a negative result to one, and selects state 2. Their names describe the proven scheduling inputs without guessing the eventual visual effect.

`graphics_resource_owner_initialize` installs descriptor `0x08CDD060` and clears its transfer pointer. `graphics_fill_background_palettes` replicates one 16-bit value across both 512-byte background palette banks using the BIOS fill operation.

The tile-buffer owner now has an explicit ownership boundary. Its destructor
clears both external output halfwords, releases the two sprites and four owned
heap blocks, runs the shared graphics cleanup, and optionally frees the owner.
The battle-side refresh callback forwards the owner's tile-buffer object to the
established rebuild-and-upload routine and normalizes its result to a boolean.
Its interpolation setup clamps the requested target against the visible bounds
derived from the tile dimensions, resets the progress counter, and hides both
sprites. The paired completion predicate updates the two external offsets with
the negated interpolated coordinates until the configured duration has elapsed.

`graphics_destroy_linked_visual` now exposes the complete linked-visual teardown path. It detaches a non-null visual, clears flag bits `0x04` and `0x08` at offset `0x13`, runs the graphics cleanup, and releases the visual. The remaining flag bits stay unnamed until their writers and rendering effects are recovered.

`graphics_display_manager_get_layer_buffer` indexes the display manager's twenty-byte layer records beginning at offset `0x0C` and returns the selected buffer. Existing field-display callers establish the manager and layer ownership; the buffer's narrower rendering format remains unknown.

`graphics_free_owner_if_requested` is the common low-bit destructor leaf used by several graphics-owning objects. Bit zero requests release of the supplied owner through the established heap routine. The owning classes and higher flag bits remain unspecified because this function only proves the conditional ownership rule.

`graphics_frame_transfer_callback` is installed into runtime frame-callback slot
zero by both adjacent graphics resource initializers. It copies the first two
halfwords from the staging buffer at `0x03000E0C` to the display pair beginning
at `0x0400001C`, refreshes that staging buffer from the allocation at
`0x03000E08`, and arms DMA3 from the staging buffer's next halfword. The buffer
contents remain address-based because their rendering format is not yet proven.

`graphics_selected_register_transfer_callback` performs the same staging refresh
and DMA3 setup, but derives the destination register pair from the low five bits
of the runtime byte at offset `0x0B`. Each four-byte table record contributes a
two-bit register-pair selector. The other record bytes and the staging format
remain unnamed because this callback does not establish their contents.

`graphics_apply_indexed_resource_entry_value` follows the resource pointer at
offset `0x57C`, translates a caller-supplied slot through the byte array at
`0x580`, and forwards the resulting resource-entry index and value to the shared
resource operation. The entry's visual or gameplay identity remains unknown.

The paired indexed tile-resource transfer entry points read a relative source
offset from the table at `0x08940C9C`, convert the destination tile and tile
count to byte units, and copy the selected data to character VRAM beginning at
`0x06004000`. Their otherwise identical entry points remain separate because
their owning callback roles have not been recovered.

`graphics_rebuild_and_upload_vram_buffer` runs the three established rebuild
passes and uploads the owner's `0x3000`-byte buffer at offset `0x94` to VRAM.
`graphics_set_configuration_state_and_load` records state `-5` and the selected
configuration index before invoking the adjacent 24-byte runtime-record loader.
The configuration record's remaining fields stay unnamed.

`GraphicsIndexedResourceRecord` establishes the twenty-byte, sentinel-terminated
records selected through runtime byte `0x0A`. Two scanners extract the proven
bit ranges from the word at `0x10` or halfword at `0x12` and apply every matching
entry to the owner. The packed values remain offset-named because their concrete
resource meaning is not established by these consumers.

`graphics_initialize_resource_entry_index` follows the independently selected
four-byte definition list, requires flag `0x40`, combines its byte at `0x01`
with `0x5000`, and stores the created entry index in the owner's array at
`0x580`. That array is the same one consumed by the indexed resource-entry
forwarding helper.

`graphics_initialize_large_owner_resource_entries` applies the complementary
definition rule to the larger owner layout. It clears the four entry indices at
`0x76C`, selects a definition list through byte `0x05` of the owner's twelve-byte
configuration record, and creates entries lacking flag `0x40` until the `0x80`
sentinel. The created resource type remains unspecified.

`graphics_initialize_owner_resource_entries` applies that same bulk rule to the
smaller owner layout. It clears the four indices at `0x580`, selects the
definition list through runtime byte `0x08`, and creates entries lacking flag
`0x40` until the `0x80` sentinel. This complements the single-slot initializer,
which handles definitions carrying flag `0x40`.

`graphics_copy_indexed_tile_resource_to_base_vram` is the base-character-VRAM
counterpart to the two offset transfer entry points. It resolves the same
relative resource table and converts tile units to bytes before copying to the
destination beginning at `0x06000000`.

`GraphicsBlendTransition` now covers the compact lifecycle around the existing
default initializer. The explicit initializer bounds the hardware blend mode,
clears progress, and starts the update path immediately for a zero-duration
request. The completion predicate compares progress with the target, while the
destructor restores the class descriptor and honors the standard low-bit heap
release flag.

`graphics_destroy_allocated_buffer_owner` establishes a separate early graphics
ownership boundary. It installs terminal descriptor `0x08CDC278`, releases the
three optional allocations at offsets `0x78`, `0x70`, and `0x68`, then removes
the process. The intervening pointers remain offset-named because this teardown
does not establish their formats or ownership rules.

`graphics_build_owner_resources_with_scratch_buffers` establishes the temporary
lifetime of two more owner fields. It allocates and clears `0x3000` bytes at
offset `0x6C` and `0x2800` bytes at offset `0x74`, runs the three established
resource-building passes, then releases both scratch blocks. Their formats stay
offset-named because those passes remain coupled assembly routines.

The blend update path uses a typed linear interpolation helper. It normalizes a
nonpositive duration, clamps the requested step to the transition interval, and
uses the relocated signed-division routine to calculate the current blend
coefficient.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports every linked C function exact, with zero mismatches.
