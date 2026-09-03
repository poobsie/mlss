# Battle runtime

## Recovered boundary

The current C boundary is organized under `src/battle/` by responsibility:

- `definition_initializers.c` stores one immutable definition at offset `0x30`, then calls the common initializer.
- `effect_state.c` hides an attached sprite and clears the effect state byte.
- `runtime_values.c` updates the independently observed fields at offsets `0x514`, `0x518`, and `0x52C`.
- `value_state.c` clears a separate object's halfword at offset `0x14`.
- `control_flags.c` groups seven bit and value updates on the battle control layout from offsets `0xF8` through `0x12D`.
- `resource_control.c` conditionally forwards the resource at offset `0x304`, then sets control bits `0x780` in the word at offset `0xFC`.
- `sprite_owner.c` provides sprite access, visibility, coordinate forwarding, and release operations.
- `sprite_motion.c` configures two structural motion modes on sprite-owning derived objects.
- `destructors.c` installs the common terminal vtable and optionally frees the owner.

The destructor file also groups seven entry points that install vtable `0x08CDCA30`, including the base entry referenced by that vtable itself. Their shared `BattleVtableObject` layout proves a value pointer at offset `0` and vtable at offset `4`; subclass identities remain unknown.

`BattleDefinitionObject`, `BattleEffectObject`, `BattleRuntimeValues`, and `BattleSpriteOwner` represent separate observed layouts. They are not merged into a speculative inheritance tree.

`BattleSpriteMotionOwner` extends the proven sprite-owner prefix with values at `0x18`, `0x20`, `0x24`, and `0x38`. Its two recovered configuration methods select mode `4` with `0xC8` or mode `3` with `0x64`, negate the supplied value into `0x20`, clear `0x38`, and clear the attached sprite's halfword at `0x0C`. Those values remain structural until the assembly update routines establish their physical units.

`battle_tick_countdown_1f2a` decrements a signed counter in the large battle-scene runtime and clears the adjacent value at `0x1F28` once the counter becomes negative. Both fields retain offset-bearing names until the code that arms the counter is recovered.

`include/battle/functions.h` supplies semantic C names while retaining the original linker symbols for assembly callers. Definition initializers use numbered identities because their descriptor contents and gameplay roles have not been recovered. The runtime-value names retain offsets for the same reason. These names should become gameplay names only when callers or descriptor data prove them.

## Matching constraint

The byte update in `battle_effect_hide_sprite_and_reset` is intentionally expressed through a byte pointer. A direct nested structure-field expression makes this compiler save an additional register, growing the function by eight bytes. The receiver and stored sprite pointer remain typed; the local expression preserves the original instruction selection.

The bitwise assignments in `control_flags.c` likewise retain byte-pointer expressions. Direct structure-member compound assignments reverse temporary-register selection in this compiler. `BattleControlObject` still provides the canonical layout and readable field inventory.

## Remaining evidence

Gameplay-specific definition names require recovered descriptor contents or identifiable construction call sites. The five identical destructor entry points require class ownership evidence before their `a` through `e` suffixes can be replaced honestly.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports 1,301 linked C functions checked, 1,301 exact, and zero mismatches.
