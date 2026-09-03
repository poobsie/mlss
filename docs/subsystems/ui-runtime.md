# UI runtime

The current C boundary contains a compact generic UI object API. `UiObject` exposes three caller-supplied values at offsets `0x18` through `0x20`, plus reset state at offsets `0x40` through `0x48`. One reset entry also forwards to the still-address-named update routine `sub_8161E38`.

`UiSpritePair` owns two optional sprite pointers at offsets `0x10` and `0x14`. Its paired callbacks hide or show every present sprite. These operations were previously mixed with an unrelated recursive object-tree traversal.

Names retain offsets where current C proves storage but not domain meaning. The update routine and callers must be recovered before those value names can be narrowed.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports 1,301 linked C functions checked, 1,301 exact, and zero mismatches.
