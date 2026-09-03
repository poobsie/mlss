# Object runtime

## Variant cleanup transitions

The repeated wrappers from `0x0808ECDC` through `0x08094DE8` belong to object lifecycle handling, despite their former `script_dispatch_helpers.c` filename. Each wrapper reads a signed variant selector from offset `0xEC` of the object's linked state, invokes the setup routine for selector `-1` or `-2`, then installs `sub_8087540` in the object's cleanup slot at offset `0x68`.

`RuntimeObject` and `RuntimeObjectState` record only this proven prefix. The linked-state pointer is at object offset `0x28`; its broader ownership and the gameplay meaning of the two negative selectors are still unknown. The eleven wrappers remain address-named because each pair of setup routines belongs to a different behavior sequence and those sequences have not yet been identified.

The six adjacent variant dispatchers now use the same types and named sentinel. They select between two complete behavior sequences, using the first sequence for variant `-1` and the second for every other value. Their address names remain until those sequences can be identified from their setup, jump, landing, and completion callbacks.

## Jump and landing phases

The eleven randomized jump setups and nine landing transitions now share the recovered motion fields in `RuntimeObject`: `verticalPosition` at `0x18`, `verticalBase` at `0x40`, the active `update` callback at `0x4C`, `verticalAcceleration` at `0x94`, and `verticalVelocity` at `0xB2`. The linked state supplies `floorHeight` at `0xE0`, while the visual object referenced at `0x08` supplies its animation flags at `0x12`.

Each setup chooses an initial upward velocity, stores a constant downward acceleration, selects animation 5, and switches to its airborne update. Each landing transition integrates velocity from the same base height, clamps to the linked floor height, selects animation 8, and advances to its completion callback. The two source families differ in their animation parameter (`0x204D` or `0x2000`), so they remain separate pending identification of that parameter.

The ten fixed-jump transitions share the same visual flag and update fields. Unlike the randomized setups, they retain the existing velocity and only install a fixed acceleration of `-0x48` or `-0x58` before selecting animation 5. This confirms that the field at `0x94` is acceleration, rather than an initial velocity or generic timer.

The seventeen completion gates and actions now use `flags76`, the linked visual flags, and the active `update` callback directly. A completion signal is bit 3 of the visual flags. Some sequences additionally terminate when any of object flag bits 3 through 5 are set; the shared destination `sub_808DD2C` remains unnamed until its complete teardown path is recovered.

Five setup transitions now expose their animation selection, signed delay timer at `0xAC`, visual mode bits, and next update callback. Three delayed-cleanup transitions use the same timer, terminate early on object flag bits 3 through 5, and clear bit 2 in the linked state's signed `flags111` byte. Five cleanup gates call the common cleanup routine when visual completion bit 3 is set.

## Initialization and visual setup

Eight initialization and visual-setup callbacks now share the behavior descriptor at `0x6C`, object flag byte at `0x77`, linked-state snapshot at `0x114`, visual parameter byte at `0x20`, behavior state at `0x9C`, and next update callback. Descriptor values `0x084FE8A8` and `0x084FE9A4` distinguish the two setup families.

The snapshot is copied from offset `0x2A` of one of two records reached through the global pointer at `0x03000FF4`; one family uses the base record and the other uses the record at `+0x3C`. Neither the record type nor the snapshot's gameplay meaning is established, so `snapshot114` and the raw global address remain explicit.

## Action completion

The common exit at `0x0808DD2C` is now `runtime_object_finish_action`. It is not a destructor: when the object's mode bits indicate an active action, it clears the linked-state reservation flag, releases an auxiliary handle, resets visual control bits and parameter state, selects animation 0, and clears the active update callback. Its semantic name is shared by the recovered lifecycle files and the remaining callers in mixed source files.

Three later conditional mode transitions now use the same visual and update fields. Each tests an external readiness gate, selects animation kind 7 or 8 only when the gate is clear, sets visual mode 2, and installs its next update callback. Their gameplay owners remain unidentified, so the individual entry points retain address names.

## Next boundary

Trace the entry dispatcher around `0x0808CC08` and group complete setup-to-completion behavior sequences. Keep the two descriptor families separate until the global source records are understood.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports 1,301 linked C functions checked, 1,301 exact, and zero mismatches.
