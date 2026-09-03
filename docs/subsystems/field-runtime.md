# Field runtime

## Actor and action layout

The transition families share a `FieldActor` layout. Each actor embeds a `FieldAction` at offset `0x08`; the action holds a visual pointer at offset `0x08` and its next update callback at offset `0x4C`. This explains why other transition code tests actor offset `0x54` as an activity value: it is the embedded action's update slot.

The field runtime pointer at `0x03000FD8` exposes the two repeatedly selected actors at offsets `0x70` and `0x74`. The remaining observed actor fields include packed state bits at `0x7E`, flags at `0x81`, a sound result at `0x82`, and a cleared halfword at `0x86`. Names remain conservative until all transition families use the shared layout.

The paired-actor state transitions now show the full relationship: they wait until the other actor's embedded action has no update callback, optionally start sound 16 based on the active actor's state bits, clear flag `0x20`, and install the caller's next update.

The reversed family performs the same operation with actor B active and actor A as the wait condition. Its runtime actor-pointer reads remain volatile, matching the original routines' observable access contract.

Activation transitions now select `actorA` or `actorB` directly, activate the embedded action, inspect the actor's state and readiness flag, store the returned sound handle, and install the next action update. The sound kinds remain numeric because their table identities have not been recovered.

Command and interaction transitions now expose their readiness checks through `action.visual.flags`, issue the observed kind and command pair against the embedded action, normalize the visual mode bits, and install the next update. Interaction transitions additionally activate the action first and gate on actor flag `0x20`.

## Next boundary

Convert activation, command, interaction, and state transition families to the shared actor and runtime types, preserving volatile accesses where code generation requires them.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports 1,301 linked C functions checked, 1,301 exact, and zero mismatches.
