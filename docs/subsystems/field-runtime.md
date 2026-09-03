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

## Next boundary

Name callback-forwarding entry points from their base operations, then audit and organize the remaining field-runtime source files.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports 1,301 linked C functions checked, 1,301 exact, and zero mismatches.
