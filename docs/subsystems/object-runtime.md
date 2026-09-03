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

## Countdown callbacks

Fourteen countdown callbacks from four former top-level files now share the signed `timer`, linked `state`, visual completion flag, and active `update` callback. The variants either release linked-state resources, stop sound `0xD2` and select animation 6, invoke a release callback, install another update, or wait for visual completion before selecting the next animation.

Several routines intentionally load the signed timer as `u16`, subtract one, store it back, then test the shifted signed result. That arithmetic is preserved rather than normalized because it controls zero crossing and wraparound exactly.

## Command and effect transitions

Seven command-related callbacks now use the shared visual, timer, linked-object, coordinate, and update fields. Two start fixed commands and set visual mode 2. Three wait for visual completion, start another command, spawn an effect at the object's `positionX`, `positionY`, and `positionZBase`, play sound `0x10C`, then advance their update. Two timed callbacks issue paired commands to the object and its `linkedObject` after the timer expires.

The former `verticalBase` field is now `positionZBase`: effect spawning reads it alongside the proven X and Y coordinates, while airborne updates add vertical velocity to the same Z base.

## State and signal transitions

Four state and signal transitions now expose `secondaryTimer` at `0xAE`, `stateValueB0` at `0xB0`, the shared `verticalVelocity` storage at `0xB2`, visual completion, and the next update callback. Two reset transient state after a polling routine returns zero. Two use the secondary timer to repeat sound `0x54`, then advance through command 13 and command 0 when visual completion arrives.

The name `stateValueB0` remains structural. Current C only proves that it is cleared during state reset; assigning a gameplay meaning would outrun the evidence.

## Conditional command transitions

Seven conditional setup and activation callbacks now use the runtime-object visual, update, and `flags79` fields. Three wait for visual completion before selecting animation kinds 8, 5, or 0. Two issue command `0x40BE` or `0x40C2` after completion and force visual mode 2. Two call an activation poll, require bit `0x20` in `flags79`, issue command `0x40C2`, play sound `0x15D`, and install their next update.

The similarly named actor-command wrappers were deliberately left outside this subsystem. They select actors through a global field context and belong to field runtime, even though their final animation calls look similar.

## Separate object layouts

The two callback-result helpers use `RuntimeObject` because they only replace its update callback and return success. The seven render-object initializers and fifteen descriptor-restoring destructors do not use that layout. They now use the separate `RenderObject` and `DescriptorObject` types in `include/object/render_object.h`.

`RenderObject` has an active byte at `0x24`, descriptor at `0x30`, and 16-bit value at `0x34`. `DescriptorObject` has its descriptor at `0x0C` and delegates teardown to `sub_8163B60`. Their class-specific entry points remain address-named because current C proves layout and lifecycle mechanics, but not the identity of each descriptor.

## Next boundary

Move the generic callback-table forwarders out of the object queue, then mark the current object-runtime C detangled. Future semantic sequence names depend on the entry dispatcher and neighboring assembly.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports 1,301 linked C functions checked, 1,301 exact, and zero mismatches.
