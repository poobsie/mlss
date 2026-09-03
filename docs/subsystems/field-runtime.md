# Field runtime

## Actor and action layout

The transition families share a `FieldActor` layout. Each actor embeds a `FieldAction` at offset `0x08`; the action holds a visual pointer at offset `0x08` and its next update callback at offset `0x4C`. This explains why other transition code tests actor offset `0x54` as an activity value: it is the embedded action's update slot.

The field runtime pointer at `0x03000FD8` exposes the two repeatedly selected actors at offsets `0x70` and `0x74`. The remaining observed actor fields include packed state bits at `0x7E`, flags at `0x81`, a sound result at `0x82`, and a cleared halfword at `0x86`. Names remain conservative until all transition families use the shared layout.

The paired-actor state transitions now show the full relationship: they wait until the other actor's embedded action has no update callback, optionally start sound 16 based on the active actor's state bits, clear flag `0x20`, and install the caller's next update.

The reversed family performs the same operation with actor B active and actor A as the wait condition. Its runtime actor-pointer reads remain volatile, matching the original routines' observable access contract.

Activation transitions now select `actorA` or `actorB` directly, activate the embedded action, inspect the actor's state and readiness flag, store the returned sound handle, and install the next action update. The sound kinds remain numeric because their table identities have not been recovered.

Command and interaction transitions now expose their readiness checks through `action.visual.flags`, issue the observed kind and command pair against the embedded action, normalize the visual mode bits, and install the next update. Interaction transitions additionally activate the action first and gate on actor flag `0x20`.

`FieldStateObject` consolidates the overlapping state-transition, state-preservation, and configuration views. The first converted transition now names its state, mode, packed flag bytes, and late status flags while keeping the command values `0x1001`, `0x1028`, and `0x1002` numeric until their command table is identified.

The preservation wrappers now snapshot and restore the low three bits of `flags024` and `flags214` around a state-dependent operation. Configuration helpers expose the signed configuration value, its dirty flag, selector, and source kind instead of offsets `0x26C`, `0x20E`, `0x26E`, `0x294`, and `0x21`.

`FieldObjectWrapper` now owns a typed sparse callback table. Every entry records a signed receiver adjustment and an unprototyped callback, and forwarding consistently invokes that callback on the adjusted child. Slot names remain offset-based because the base operations are still address-named; the layout no longer relies on byte-pointer arithmetic.

The wrapper entry points have semantic compatibility names in `include/field/functions.h`. They distinguish forwarding from result-returning queries and identify the callback slot used. Slot `0x20` also records its proven enable-bit gate. More specific operation names require the underlying `sub_804...` functions to be decompiled.

The same compatibility header names the configuration and field-state entry points: applying a configuration source, setting a configuration value, applying the mode-dependent transition, and the two flag-preserving finish variants. Original symbols remain available to assembly.

Actor transition entry points are also named by observable contract. The names record actor A or B, animation or command value, sound kind where applicable, and a suffix for otherwise indistinguishable continuations. They intentionally do not assign scene or character identities that are visible only in assembly callers.

## Next boundary

The currently decompiled field-runtime slice is detangled. Further names depend on base operations and scene-specific callers that remain in assembly. Resume when those dependencies can replace callback-slot and variant suffixes with evidence-backed identities.

`FieldSceneObject` covers the independently observed scene-object tail from offset `0x20F` through `0x340`. Its current helpers clear state under a value guard, mark an attached sprite while selecting state 7, and reset two sprite mode fields after common setup. The no-op entry points adjacent to the sprite reset remain address-named because their callback-table roles are not yet known.

The recovered layout now begins at offset `0x20C` and includes nine property operations: three flag setters or clears, two value setters, one flag query, two narrow two-bit clears, and a current-to-previous halfword update at offsets `0x266` and `0x268`. Offset-bearing names are retained where the gameplay meaning is not yet proven.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports 1,301 linked C functions checked, 1,301 exact, and zero mismatches.
