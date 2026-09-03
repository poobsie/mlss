# Battle runtime

## Definition wrappers

The first recovered family consists of thin initializers for `BattleDefinitionObject`. Each stores one immutable definition pointer at offset `0x30`, then calls the common initializer with the object, caller argument, and same definition. The descriptor contents and gameplay identities remain outside the current C boundary.

## Next boundary

Convert the later definition wrappers to the shared type, then separate sprite ownership, effect state, runtime values, and destructor families.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports 1,301 linked C functions checked, 1,301 exact, and zero mismatches.
