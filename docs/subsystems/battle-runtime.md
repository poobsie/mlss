# Battle runtime

## Definition wrappers

The first recovered family consists of thin initializers for `BattleDefinitionObject`. Each stores one immutable definition pointer at offset `0x30`, then calls the common initializer with the object, caller argument, and same definition. The descriptor contents and gameplay identities remain outside the current C boundary.

The later file now uses the same definition type and separates three other observed layouts: an effect object with a sprite and state byte, a large runtime-value object, and a sprite owner with a vtable. Sprite access, visibility, cleanup, runtime values, and destructor vtable replacement no longer use raw byte offsets.

## Next boundary

Split definition initialization, sprite ownership, effect state, runtime values, and destructor families into focused source files.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports 1,301 linked C functions checked, 1,301 exact, and zero mismatches.
