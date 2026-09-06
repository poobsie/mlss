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

The recovered layout now begins at offset `0x20C` and includes property operations for flags, values, and a current-to-previous halfword update at offsets `0x266` and `0x268`. The additional predicate exposes bit `0x01` at offset `0x291`. Offset-bearing names are retained where the gameplay meaning is not yet proven.

The object also selects one 28-byte entry through an index at `0x26E` and a table pointer at `0x334`. Two wrappers perform guarded low-bit state changes on that entry, `2` to `1` and `1` to `2`. Their names state those proven transitions directly; the table's gameplay identity remains unresolved.

Four dispatch wrappers share another proven precondition: set bit `0x10` in `flags33E` and bit `0x40` in `flags2B6`, then call a variant-specific handler. The wrapper variants remain lettered because current C does not identify their scene owners.

`field_apply_position_delta` adds the object's signed deltas at `0x242` and `0x244` to its 24.8 position words at `0x0C` and `0x10`. The caller supplies an unused context argument, which remains in the public signature because this function is installed through a two-argument callback interface.

`FieldCollisionRecord` is the `0x4C`-byte record allocated in an eight-element set. Its initializer stores the record index in the low three flag bits and returns the record pointer used by the caller. The recovered maintenance helpers preserve four current bounds into their previous-value slots and release the resource at `0x44` while clearing the active flag. The geometric axis meanings are inferred from their grouped use and retain rectangle-oriented names pending full collision update recovery.

`FieldViewState` now owns the adjacent view-origin and pan fields at offsets `0x774` through `0x77A`. Callers use the first pair to convert world positions into screen positions, while the second pair is incremented or replaced to request view movement. The broader object remains opaque until its assembly-only update routines are recovered.

The base field-scene destructor and three variant destructors all restore descriptor `0x08CDBDE8` at offset `0x338`, then release the object when requested. Keeping the variants separate preserves their callback-table identities while sharing the proven object layout.

The guarded movement entry point now records `positionX` and `positionY` as the movement-start coordinates before invoking the collision-aware movement routine. Its two observed gates remain named by offset: packed flags `0x0801` at `0x20C` and inhibit bit `0x02` at `0x35A`.

`FieldLinkedObjectOwner` exposes the primary and secondary object pointers at `0x200` and `0x204`. The recovered helpers set both linked states to `0xB2`, test the primary marker against `0x15` and `0x1C`, recognize two proven state ranges, and dispatch states `5` through `12` between two assembly-only handlers.

Two adjacent wrappers call their respective field-object operations with enabled mode `1`. They remain variant `a` and `b` until the assembly-only operations at `0x802FAE4` and `0x8029A0C` are recovered.

`FieldDefinitionCallbacks` replaces the final root-level early helper family. Its initializer parses the object's definition, installs an update trampoline at `0x198`, and installs the definition callback at `0x1A0`; the trampoline passes the callback slot itself so the target may replace the next callback.

`FieldValueTransfer` exposes one half of a reversible state transfer: the recovered routine moves the halfword at `0x34` to `0x44` and clears the source. The adjacent assembly routine performs the inverse move, with additional mode bookkeeping that is not yet decompiled.

The same state now exposes its four-way readiness result. A pending destination value
at `0x44` has priority, followed by an empty source at `0x34`; otherwise flag `0x04`
at `0x32` selects between the two ready states. The numeric results remain unchanged
because their consumers do not yet establish stable semantic labels.

The display-transfer process keeps a one-bit phase at process offset `0x1C`.
Its callback toggles that phase directly; the surrounding display callbacks remain
in assembly until their indirect-call contracts are established.

The field graphics-block loader selects a resource using the runtime byte at `0x8C0`
plus the table bias `7`, then decodes it into the workspace buffer at `0x840` without
requesting a temporary heap buffer. The concrete resource and workspace payload types
remain opaque.

Indexed field sprites are stored in 64-byte entries reached through the pointer at
owner offset `0x158`. The positioning helper selects the entry by byte index and
forwards its sprite and coordinates while clearing both optional update arguments.
The adjacent update helper creates a missing sprite or updates the existing one using
the same entry stride and packed-position input.

The adjacent layer-reset helper invalidates runtime word `0x884`, resets the layer at
owner offset `0x20`, copies the owner halfword at `0x17E` to `0x02000000`, and marks
byte `0x156` initialized. The destination halfword remains generically named.

The intervening byte-coded callbacks actually begin at `0x08121970` and `0x0812198C`.
The first reports whether runtime byte `0x03000C80` is clear; the second creates a
sprite and stores it in the indexed 64-byte entry. They remain byte-coded because no
stable symbols currently establish those boundaries.

The selected-entry sequence is now one three-stage unit instead of three numbered catch-all files. Its stages wait for the shared blocker at `0x310`, prepare the selected entry at `0x349`, commit it through the active object at `0x7C`, clear the selection to `0xFF`, and install the next process callback at each boundary. Scene-specific names require the resource tables used by the assembly helpers.

The position-forwarding node passes its context pointer, signed coordinates at `0x12`
and `0x14`, and flag bit `12` to the shared field helper. Other flag bits and the
context payload remain unnamed because this wrapper does not interpret them.

The linked-value callback copies byte `0x0A` from the object referenced at owner
offset `0x6C` into runtime byte `0x2F9`, then invokes the shared refresh helper. The
value remains generically named because neither side establishes its domain.

A fourth selection-setup stage waits on an external readiness poll and flag `0x04` at `0x2BF`. Mode `2` resets both indexed display selections through the same assembly helper before the process advances.

The paired-object slide sequence moves the objects at runtime offsets `0x37C` and `0x278` left by one 24.8 fixed-point pixel per tick. Once view conversion places them at screen X 208, it snaps both positions to that boundary, starts animation 4 on the second object, clears the flag at `0x342`, and installs the next process callback.

The later completion callback for that sequence now shares the same typed runtime. It waits for visual completion on the second object, starts animation 5, sets its visual parameter to `0x10`, and advances the field process.

A separate field-effect process now exposes its gate at runtime offset `0x248`, entry identifier at process offset `0x0C`, and 12-tick delay at `0x10`. Once the gate clears, it resets the surrounding dispatch state, resolves the entry, forwards the entry metadata's 16-bit dispatch value when present, and advances. The metadata value remains structural because the receiving assembly routine has not established whether it identifies text, graphics, or another effect resource.

The primary actor-pair flag helper now uses `FieldRuntime` and `FieldActor` directly. For each of actors A and B, state bits `1..2` equal to `2` cause flag `0x04` to be set at actor offset `0x81`, after which the field process advances.

The recovered actor-pair completion helper updates actor B's action, waits for its `0x20` flag, resumes actor A only for state bits `2` or `4`, and clears actor B's action update. It shares the same `FieldRuntime`, `FieldActor`, and embedded `FieldAction` layout as the other actor transitions.

Two later field-process callbacks now expose their actor selection and transition
contracts. One prepares actor B with animation 15 and command `0x2062` when its
state bits select an active mode, then advances the calling process. The other polls
actor A, waits for actor flag `0x20`, plays sound `0xAF`, conditionally applies
command `0x2024`, restores visual mode 2, and advances. The numeric commands and
continuations remain address-based because their assembly-only consumers do not yet
establish scene-specific identities. An adjacent actor-A visual-disable callback
remains in assembly after both bounded C forms changed the compiler's flag-clear
instruction selection.

A later actor-A process callback now exposes its linked-object and animation
handoff. It plays sound `0x85`, conditionally assigns the linked object's update
from its state bits, applies animation 9 and command `0x2036` when the actor action
is active, clears its visual mode bits, and advances the calling process. The
linked-object continuation and numeric command remain address-based pending their
assembly recovery. A neighboring actor-B link synchronizer remains in assembly
after both bounded forms expanded its flag updates beyond the original code size.

The field runtime also exposes actors C and D at offsets `0x80` and `0x84`. A recovered dispatcher installs the supplied action update on each actor whose state bits equal `2`; actor D is optional, while current callers guarantee actor C is present.

`FieldDisplayRuntime` consolidates the display manager at `0x250` and four owned display-process slots from `0x284` through `0x290`. The recovered lifecycle helpers release or finish those processes while disabling the associated layer pairs 0/1, 2/3, and 4/5; a separate entry configures layer 0 with the caller's value.

`FieldObjectSetDirectory` describes the eight-byte directory embedded in each field-object definition blob. Its packed bytes expose the object count and resource count, while backward offsets locate the blob's variable-length lists. `field_get_object_resource_list` now returns the resource-ID list used by the early field-object loader instead of presenting the calculation as an unrelated numbered helper. Two parallel indexed pointer tables remain `table_a` and `table_b`: their contents are proven to be metadata streams, but no decompiled caller distinguishes their roles yet.

The scene-state accessor at `0x080FAEEC` is now `field_get_scene_state_value_9a1`. The field ownership chain is established, but the byte's behavior is not; retaining `9a1` is more accurate than manufacturing a flag name from one conditional caller.

`field_clear_flags_11e_high_nibble` preserves the low twelve bits of a field object's halfword at `0x11E`. Its callers prove the mask but do not yet identify the four cleared flags individually, so the member remains offset-named.

`FieldResourceLoaderProcess` owns two independently released resources and one heap workspace. Its shutdown path clears the runtime-active flag; destruction restores five default resource pointers before removing the process. The five resource roles remain offset-named because only their tables and lifecycle are recovered.

`field_start_alternate_actor_action` chooses the object at runtime offset `0x80` or `0x84` from flag `0x04` at `0x2C0`, starts the corresponding command and visual placement, installs the next selection callback, and plays sound `0x2B`. The two objects are deliberately not given character names without evidence from their construction paths.

The small field-runtime utilities now have typed homes: a visual-completion branch process, a fixed five-command setup, nested flag clearing, conditional flag toggling, a three-tier random result for identifier `0x200`, selection readiness, and construction of two linked display nodes. Constants remain in the public names when current C proves their use but not their design meaning.

`field_set_mode_3a5_and_mark_pending` writes the requested mode and marks runtime flag `0x40`. Its byte update intentionally retains a raw offset expression because the exact compiler otherwise reverses the temporary registers and breaks the ROM match.

Ten event callback helpers now share `FieldEventContext`. Three read a byte from the context's selection table using its current index and a variant-specific displacement, store it as the selected value, and install the same callback-chain endpoints. Five enable event processing and install continuations, with three also clearing the proven reset halfword at `0x1D4`. Two replace a caller-owned callback after one of the two asynchronous gates clears. The variant suffixes remain because their owning event scripts are still assembly-only.

Fifteen upper-region callbacks now expose the callback-chain portion of `FieldSceneObject`. The dispatcher sits at `0x198`, the active and linked chain callbacks at `0x1A0` and `0x1A4`, and an optional auxiliary callback at `0x1AC`. Initializers select a preparation profile, install a dispatcher and starting callback, then invoke the dispatcher immediately. One chain callback conditionally runs the existing field cleanup operation when flag `0x40` at `0x214` is set before forwarding through the next slot. Two variants also prepare the linked scene object at `0x344`. Variant letters remain because the installed assembly callbacks expose mechanics but not stable scene identities.

The final two upper field helpers now share those types. `field_clear_scene_object_modes` clears the proven low mode bit at `0x20C` and invokes the adjacent still-unidentified mode setter with zero. `field_prepare_callback_slot_3_and_dispatch` resets its scene object, installs the known callback in slot three of a four-entry callback packet, and invokes it immediately.

Three former miscellaneous helpers now use established field-runtime ownership. Two commit or prepare the `FieldValueTransfer` at runtime offset `0x248`; the third triggers the active object attached to the primary actor. `FieldAction::activeObject` is now typed at its proven offset `0x30` within the action.

The final field helpers from bucket 01 now set the view's pan deltas, wait for an object's state flag to clear, wait for a nested visual to complete, and create display node kind `0x86` with its value at `0x14` cleared. The pan deltas are computed by the adjacent assembly routine from changes in the view's origin and pan coordinates.

Bucket 02 adds three typed field-process transitions: one finishes an action when its branch query clears, one runs two global setup operations after field readiness, and one drives a selected runtime object until its update becomes null before returning to the field scan callback. Two companion transitions start animation `0x2F` on the first object owner at runtime offset `0x58`, then install their distinct continuations. The display-node module also exposes the paired index 0 and 1 initializer.

The resource-loader boundary now includes two owned allocations. `FieldOwnedResource` releases its allocation at offset zero, while `FieldResourceBlockList` releases its block array at offset `0x0C`; both conditionally release their owner when destructor flag 1 is present. The latter is constructed and destroyed by the adjacent field resource system, which supports the subsystem assignment without guessing the payload format.

The collision-map boundary now exposes its definition table at offset `0xA0`.
`field_collision_map_get_definition` returns one four-byte definition selected by
an eight-bit index. The entry payload remains opaque until its coordinate lookup
caller and definition consumers are recovered.

`field_collision_map_get_definition_at` validates signed X/Z indices against the
map limits, resolves the cell through the byte-sized definition-index grid, and
returns the shared fallback definition for out-of-range coordinates. The axis
labels are inherited from the original established symbol; their world units are
not yet known.

`field_collision_map_copy_indexed_values_36_3c` exposes the paired halfword
arrays used beside the collision grid. Their offsets and indexed-copy behavior
are proven; their gameplay meaning remains unknown, so the member and function
names retain the offsets instead of guessing.

`field_collision_map_reset_vram_workspace` resets the VRAM base, releases the
map workspace at offset `0xA4` when present, and fills the first `0x8000` VRAM
bytes with zero. Both observed callers run it immediately before disabling the
owning field process.

The adjacent `FieldMapGraphicsProcess` is a separate `yMap`-labeled process.
Its recovered destructor resets VRAM, releases the four proven buffers in
ownership order, and removes the process. The asset record fields used by its
remaining assembly loader are not named ahead of their consumers.

The display runtime now exposes its object and process slots at `0x278`, `0x27C`, and `0x280`. One helper releases and clears the object slot; another sends both process slots to the established display-finishing callback. Two process callbacks copy the staging halfwords at `0x0200001A` and `0x0200001E` into their matching display registers, either stopping before the copy or immediately after it when the owner becomes inactive.

Two view wrappers now obtain the active `FieldViewState` from the established field runtime and forward complete coordinate or record arguments to the underlying view transforms. The lower-level transforms remain address-named because their arithmetic is still assembly-only; the wrappers no longer disguise field-view ownership behind raw global-pointer casts.

The final five field-runtime helpers expose the nested flag container at runtime offset `0x244`, its paired flag words at `0x1788` and `0x1798`, the pending flag at `0x2BF`, and the active-object owner at `0x7C`. Three set, filter, or submit nested flag requests. Two select the active-object preparation path from runtime flag `0x80` or restore a saved process callback after active-object flag `0x20` clears. The flag numbers remain in the names because current assembly proves their mechanics but not their game-facing meanings.

The runtime node boundary now exposes the free list at offset `0x3C`, five active list heads from `0x40` through `0x50`, and the separate recycling pool at `0x240`. Six insertion helpers pop one node, initialize its owner or callback and counter, then push it onto an internal or caller-owned list. The adjacent object wrapper marks flag `0x10` at object offset `0x79` and schedules the known callback on list `0x4C`. List names retain their offsets because the remaining callback consumers have not yet established distinct behavioral roles.

The neighboring link-node pool uses runtime offsets `0x238` and `0x23C` as its free and active heads. Its allocator clears the low five flag bits before returning a node, while the owner-attaching form also links the owner's values and inline payload. Two payload-node allocators pop from the separate `0x240` pool, clear all `0x1C` bytes through the runtime memory routine, and optionally install three caller values. Those value roles remain offset-named pending recovery of their consumers.

The action-motion boundary now includes the shared vertical-arc step and two timer
transitions. The arc step subtracts the fixed acceleration `0x5E`, updates the
object's vertical position relative to `positionZBase`, and clamps both position
and velocity at landing. One timer transition resets animation command zero,
clears visual mode bits `1` and `2`, and continues through the shared action
callback; the other only waits before selecting that callback. The callback itself
remains address-named because its wider action-state role is still in assembly.

Three direct helpers now sit with their typed field owners. The runtime flag query
tests the proven `0x10` bit, the view initializer installs its default definition
before forwarding to the established setup routine, and the display-node helper
draws an offset box from the node's three signed coordinate values. The adjacent
configured-box, countdown, display-register, and entry-state routines remain in
assembly: their behavior is understood, but the available C shapes did not match
the original instructions exactly. Their wider flag and staging roles therefore
remain intentionally unnamed until a matching consumer boundary provides better
evidence.

Two larger field-process state machines now use the shared actor and object layouts.
The first waits for actor B's visual completion, conditionally applies animation 10
and command `0x2063`, initializes its sound handle for 20 ticks, clears the related
runtime flags, masks the secondary timer, and advances. The second waits for actor
A's visual completion, disables that action when active, then initializes actor B's
sound handle for 10 ticks before advancing. The indirect sound allocator remains
expressed through its established runtime entry point; its resource identity and
the numeric command remain unresolved.

Two effect-producing actor transitions now share those same layouts. One waits for
actor B's completion flag, emits effect `0x2FE6` at actor A's fixed-point position,
plays sound `0x7C`, and, for the active actor states, arms actor A's sound handle for
24 ticks before advancing. The other waits on actor A, emits effect `0x1E`, plays
sound `0x65`, selects animation 8 with command `0x2000` for variant `-1` or `0x204D`
otherwise, sets visual mode 2, and advances. The effect IDs, command IDs, and
continuation callbacks remain numeric or address-named because their broader roles
are not yet established by callers.

The paired-actor sequence also exposes two coordinated animation transitions and
its actor-idle handoff. The animation transition assigns animation 7 and distinct
commands to both actors, then arms actor B's sound handle for eight ticks. The
completion-gated variant assigns animation 6, clears both visual modes, arms the
same handle for ten ticks, masks actor B's secondary timer, and advances. The
handoff waits for actor A's callback to clear, plays sound `0x2E`, arms actor B's
sound handle for 32 ticks, restores actor A's command `0x2024`, masks actor B's
secondary timer, and advances. Numeric sounds and commands retain their identifiers
until resource tables or named consumers establish their gameplay roles.

Three larger placement transitions establish signed display offsets at `0xC3`,
`0xC4`, and `0xC5` on both runtime objects and their attached state records. One
positions actor A from a process-owned state record, applies scale `0x600`, and
starts animation 4. Another reacts to actor B's completion, stops actor A's linked
object, repositions it from actor A's coordinates and display offsets, and applies
command `0x66`. The third prepares actor B and its linked object, computes a launch
position from actor B's coordinates and display offsets, starts motion `0x400`, and
arms the following transition. The coordinate relationship is proven; the numeric
animation, command, scale, and motion values retain their identifiers. The adjacent
view-relative effect transition remains in assembly because its natural typed forms
do not reproduce the original register allocation.

The late collision-query boundary now exposes two leaf checks around the shared
query record. `field_collision_query_owner_enabled` follows the query's owner
pointer and tests bit 0 at owner offset `0x1D6`. The paired unbounded query passes
the record's four signed bounds and owner directly to the established geometric
test, using `0x7FFF` and zero for its two open extents.

| Previous name | Recovered name | Evidence |
| --- | --- | --- |
| `sub_80FBE5C` | `field_collision_query_owner_enabled` | Returns whether bit 0 is set in the query owner's collision-state byte at offset `0x1D6`. |
| `sub_80FC148` | `field_collision_test_owner_unbounded` | Tests the query's bounds against its owner through the shared geometry helper with the established open-extent constants. |

The bounds layout and pointer ownership are proven by adjacent query wrappers.
The axis represented by each bound, the meaning of owner flag bit 0, and the
gameplay reason for the open-extent constants remain unknown.

## Verification

The nested field-flag owner now exposes the direct setter paired with its existing
clear helper. `field_set_nested_flags_1788` follows the runtime's container and
target pointers, then ORs the requested mask into `flags1788`. Its caller uses mask
`0x08` while committing a selected field entry. The individual bit meaning remains
unresolved, so the name records the proven ownership and operation without assigning
a speculative gameplay label.

Two field-script waits now share the established interpreter resume-cursor layout.
`field_wait_for_nested_state_179d_clear` yields while the low seven bits of the
nested flag target's byte at `0x179D` remain nonzero.
`field_wait_for_runtime_flag_10_clear` performs the same resume-and-yield behavior
through the existing `field_runtime_test_flag_10` query. The state byte's gameplay
meaning remains unresolved and therefore retains its structural offset.

Three adjacent object-status callbacks now consume flag bits `0x80`, `0x20`, and
`0x08` from the shared halfword at offset `0x11E`. Each acknowledged bit is
cleared and arms the corresponding halfword at offset `0x11C`, `0x10C`, or
`0x10A` with `0x100`. The bit meanings and the units of those armed values remain
unknown; the shared layout and one-shot relationship are proven by the repeated
instruction family.

The neighboring high-nibble clear remains part of the same typed status API.
More complex consumers are still in assembly until their callback owner explains
whether these are animation, movement, or interaction timers.

The full ROM passes its SHA-1 comparison. The exact-function verifier reports every linked C function exact, with zero mismatches.
