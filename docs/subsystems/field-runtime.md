# Field runtime

## Actor and action layout

The transition families share a `FieldActor` layout. Each actor embeds a `FieldAction` at offset `0x08`; the action holds a visual pointer at offset `0x08` and its next update callback at offset `0x4C`. This explains why other transition code tests actor offset `0x54` as an activity value: it is the embedded action's update slot.

The field runtime pointer at `0x03000FD8` exposes the two repeatedly selected actors at offsets `0x70` and `0x74`. The remaining observed actor fields include packed state bits at `0x7E`, flags at `0x81`, a sound result at `0x82`, and a cleared halfword at `0x86`. Names remain conservative until all transition families use the shared layout.

## Next boundary

Convert activation, command, interaction, and state transition families to the shared actor and runtime types, preserving volatile accesses where code generation requires them.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports 1,301 linked C functions checked, 1,301 exact, and zero mismatches.
