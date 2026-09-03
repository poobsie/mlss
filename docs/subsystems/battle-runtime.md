# Battle runtime

## Recovered boundary

The current C boundary is organized under `src/battle/` by responsibility:

- `definition_initializers.c` stores one immutable definition at offset `0x30`, then calls the common initializer.
- `effect_state.c` hides an attached sprite and clears the effect state byte.
- `runtime_values.c` updates the independently observed fields at offsets `0x514`, `0x518`, and `0x52C`.
- `value_state.c` clears a separate object's halfword at offset `0x14`.
- `sprite_owner.c` provides sprite access, visibility, coordinate forwarding, and release operations.
- `destructors.c` installs the common terminal vtable and optionally frees the owner.

`BattleDefinitionObject`, `BattleEffectObject`, `BattleRuntimeValues`, and `BattleSpriteOwner` represent separate observed layouts. They are not merged into a speculative inheritance tree.

`include/battle/functions.h` supplies semantic C names while retaining the original linker symbols for assembly callers. Definition initializers use numbered identities because their descriptor contents and gameplay roles have not been recovered. The runtime-value names retain offsets for the same reason. These names should become gameplay names only when callers or descriptor data prove them.

## Matching constraint

The byte update in `battle_effect_hide_sprite_and_reset` is intentionally expressed through a byte pointer. A direct nested structure-field expression makes this compiler save an additional register, growing the function by eight bytes. The receiver and stored sprite pointer remain typed; the local expression preserves the original instruction selection.

## Remaining evidence

Gameplay-specific definition names require recovered descriptor contents or identifiable construction call sites. The five identical destructor entry points require class ownership evidence before their `a` through `e` suffixes can be replaced honestly.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports 1,301 linked C functions checked, 1,301 exact, and zero mismatches.
