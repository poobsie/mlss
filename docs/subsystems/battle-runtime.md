# Battle runtime

## Recovered boundary

The current C boundary is organized under `src/battle/` by responsibility:

- `definition_initializers.c` stores one immutable definition at offset `0x30`, then calls the common initializer.
- `effect_state.c` hides an attached sprite and clears the effect state byte.
- `runtime_values.c` updates the independently observed fields at offsets `0x514`, `0x518`, and `0x52C`.
- `value_state.c` clears a separate object's halfword at offset `0x14`.
- `control_flags.c` groups the bit and value updates on the battle control layout, including the reset of its two late motion values and low two-bit mode.
- `resource_control.c` groups two operations guarded by the same inactive-state test on flags at `0xFC`: one prepares the resource at `0x304`, while the other activates it and sets control bits `0x780`.
- `buffer_sync.c` exposes the wrapper around the assembly routine that DMA-copies the active battle process buffers.
- `sprite_owner.c` provides sprite access, visibility, coordinate forwarding, and release operations.
- `sprite_motion.c` configures two structural motion modes on sprite-owning derived objects.
- `sprite_motion_variants.c` groups construction, state preparation, child cleanup, owned-resource cleanup, and attached-position synchronization for the shared sprite-motion layout.
- `single_sprite_destructors.c` groups cleanup for owners containing one sprite, a sprite in their second slot, or three sprite slots.
- `sprite_variant_container.c` owns a two-variant container that constructs exactly one sprite-backed child and dispatches to the matching destructor.
- `large_resource_cleanup.c` contains cleanup for the independently proven large-object resource slots at `0x524`, `0x804`, and `0x80C`.
- `destructors.c` installs the common terminal vtable and optionally frees the owner.

The destructor file also groups seven entry points that install vtable `0x08CDCA30`, including the base entry referenced by that vtable itself. Their shared `BattleVtableObject` layout proves a value pointer at offset `0` and vtable at offset `4`; subclass identities remain unknown.

`BattleDefinitionObject`, `BattleEffectObject`, `BattleRuntimeValues`, and `BattleSpriteOwner` represent separate observed layouts. They are not merged into a speculative inheritance tree.

`BattleSpriteMotionOwner` extends the proven sprite-owner prefix with values at `0x18`, `0x20`, `0x24`, and `0x38`. Its two recovered configuration methods select mode `4` with `0xC8` or mode `3` with `0x64`, negate the supplied value into `0x20`, clear `0x38`, and clear the attached sprite's halfword at `0x0C`. Those values remain structural until the assembly update routines establish their physical units.

`BattleSpriteMotion` is the broader sprite-backed position object initialized by `sub_815F8F4`. It records 24.8 X and Y positions, their previous values, signed per-frame velocities, a state byte, a descriptor, and overlapping subclass storage from `0x34` onward. The overlap is represented explicitly: the same slot can be a 16-bit constructor value or an owned child pointer depending on the installed descriptor.

The recovered sprite-motion variant family includes four initializers, two state preparations, four child-destructor variants, five owned-resource destructor variants, and two identical attached-position synchronization entry points. Semantic aliases state the proven lifecycle behavior, while variant suffixes remain until descriptor tables or construction callers identify their battle entities. The shared motion helper adds X velocity and Y velocity plus the caller's Y offset each tick.

The sprite variant container clears its state, installs descriptor `0x08CDC4D0`, and allocates one `0x34`-byte child. The signed low five bits of byte `0x03001010` select between the two child constructors at a threshold of five. This is enough to name the ownership and lifecycle, but not the gameplay meaning of either variant or the selector byte.

The five compact sprite-owner destructors share cleanup shape but not enough class evidence to merge their layouts. Three unconditional single-sprite variants use offset `0`; one nullable sprite uses offset `4`; one owns three nullable sprites at offsets `0`, `4`, and `8`. Their semantic names describe those proven layouts and preserve variant suffixes where separate ROM entry points remain unexplained.

The large cleanup helpers are deliberately kept separate from `BattleSpriteMotion`. Their observed fields occur at offsets `0x524`, `0x804`, and `0x80C`, and no evidence yet proves that the two large layouts are the same class.

`battle_tick_countdown_1f2a` decrements a signed counter in the large battle-scene runtime and clears the adjacent value at `0x1F28` once the counter becomes negative. Both fields retain offset-bearing names until the code that arms the counter is recovered.

`include/battle/functions.h` supplies semantic C names while retaining the original linker symbols for assembly callers. Definition initializers use numbered identities because their descriptor contents and gameplay roles have not been recovered. The runtime-value names retain offsets for the same reason. These names should become gameplay names only when callers or descriptor data prove them.

## Matching constraint

The byte update in `battle_effect_hide_sprite_and_reset` is intentionally expressed through a byte pointer. A direct nested structure-field expression makes this compiler save an additional register, growing the function by eight bytes. The receiver and stored sprite pointer remain typed; the local expression preserves the original instruction selection.

The bitwise assignments in `control_flags.c` likewise retain byte-pointer expressions. Direct structure-member compound assignments reverse temporary-register selection in this compiler. `BattleControlObject` still provides the canonical layout and readable field inventory.

The late fields at `0x2F8` and `0x2FC` are named as motion values because their shared reset also clears the low two-bit mode at `0xF9`. Their axis or timing roles remain unresolved.

## Remaining evidence

Gameplay-specific definition names require recovered descriptor contents or identifiable construction call sites. The identical destructor and synchronization entry points require class ownership evidence before their variant suffixes can be replaced honestly. The sprite-container selector needs a recovered owner for `0x03001010` before it can receive a stable domain name.

## Verification

Twelve mirrored sprite-motion callbacks now expose constructors, origin-position
synchronization, sprite-size setup, and horizontal wrap motion through the shared
`BattleSpriteMotion` layout. Descriptor addresses and numeric state and variant
values remain explicit because their owning effect tables are not yet recovered.
Semantic C aliases map to the original symbols without introducing duplicate
function entries.

Ten additional sprite-motion leaves cover activation, ground clamping,
position/resource synchronization, motion forwarding, and cleanup. Six neighboring
event-state routines remain in assembly because natural C produced different
instruction scheduling. The accepted aliases continue to preserve the original
symbol table, so coverage accounting remains at the canonical 7,017 functions.

The battle layer also gains two typed sprite-motion constructors, a signed effect
value accessor, and the absolute setter for the circular-mask value. The setter's
recovered 32-bit field width is shared through the graphics header; the battle
effect and descriptor identities remain structural where current callers do not
prove them.

Five more leaves expose a runtime flag setter, three large-owner cleanup paths,
and a compact effect-state update. Their structural layouts name only proven
ownership and value relationships; unresolved battle entity identities remain
attached to the original linker symbols.

The full ROM passes its SHA-1 comparison. The exact-function verifier reports 1,602 linked C functions checked, 1,602 exact, and zero mismatches.
