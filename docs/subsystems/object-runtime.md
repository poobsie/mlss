# Object runtime

## Variant cleanup transitions

The repeated wrappers from `0x0808ECDC` through `0x08094DE8` belong to object lifecycle handling, despite their former `script_dispatch_helpers.c` filename. Each wrapper reads a signed variant selector from offset `0xEC` of the object's linked state, invokes the setup routine for selector `-1` or `-2`, then installs `sub_8087540` in the object's cleanup slot at offset `0x68`.

`RuntimeObject` and `RuntimeObjectState` record only this proven prefix. The linked-state pointer is at object offset `0x28`; its broader ownership and the gameplay meaning of the two negative selectors are still unknown. The eleven wrappers remain address-named because each pair of setup routines belongs to a different behavior sequence and those sequences have not yet been identified.

The six adjacent variant dispatchers now use the same types and named sentinel. They select between two complete behavior sequences, using the first sequence for variant `-1` and the second for every other value. Their address names remain until those sequences can be identified from their setup, jump, landing, and completion callbacks.

## Jump and landing phases

The eleven randomized jump setups and nine landing transitions now share the recovered motion fields in `RuntimeObject`: `verticalPosition` at `0x18`, `verticalBase` at `0x40`, the active `update` callback at `0x4C`, `verticalAcceleration` at `0x94`, and `verticalVelocity` at `0xB2`. The linked state supplies `floorHeight` at `0xE0`, while the visual object referenced at `0x08` supplies its animation flags at `0x12`.

Each setup chooses an initial upward velocity, stores a constant downward acceleration, selects animation 5, and switches to its airborne update. Each landing transition integrates velocity from the same base height, clamps to the linked floor height, selects animation 8, and advances to its completion callback. The two source families differ in their animation parameter (`0x204D` or `0x2000`), so they remain separate pending identification of that parameter.

## Next boundary

Apply the shared object prefix to the fixed-jump, initialization, completion, and cleanup files. Recover stable names at the level of complete behavior sequences, rather than assigning names independently to dozens of nearly identical state callbacks.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports 1,301 linked C functions checked, 1,301 exact, and zero mismatches.
