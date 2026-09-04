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

Future semantic sequence names depend on the entry dispatcher and neighboring assembly. Newly decompiled helpers should join this subsystem only when they use the established object layouts or call graph.

Seven additional leaf callbacks now use `RuntimeObject` directly. Three move an
object left, or left and down, until it crosses the established screen boundary.
One starts animation 6 when `value80` clears, one repeats an animation according
to `behaviorState`, and one finishes a visual before stopping its update. The
remaining callback releases the `RuntimeObject`-shaped owner stored in
`positionOwner` and installs the next update. `value80`, `behaviorState`, and
the broader meaning of `positionOwner` remain structural because these paths do
not identify their gameplay owner.

Two mirrored animation-entry callbacks start animation 2, clear the timer, save
the object's current X and Y positions, and install different continuations. The
saved X field is still `value84`, and the adjacent saved-Y storage remains
structural, because other callback families use those offsets differently.

Ten early runtime callbacks now expose their actual transition contracts. They
cover paired effect emission and cleanup, readiness-gated animation setup,
restoring a saved position, two fixed-point offscreen exits, a visual-completion
counter, an accelerating arc, and two state-gated animation/effect transitions.
Names retain numeric animation and effect identifiers because their resource
tables still live in assembly. `behaviorState` is velocity-shaped in the arc
callback, but remains structural globally because other callbacks use it as a
counter or selector.

The adjacent early sequence contributes ten more typed leaves: readiness and
`value80` gates, visual-completion handoffs, countdown transitions, effect cleanup,
and linked-object clearing. Numeric effect identifiers and assembly-only
continuations remain explicit; the recovered names describe only the observed
gate and state change.

Ten callbacks from the following early range now cover saved-position restore,
visual and `value80` gates, linked-object release, effect setup, and fixed-point
motion transitions. The shared `RuntimeObject` layout now exposes the halfwords
at `0x7A` and `0x7C` structurally; their gameplay meaning is still unproven, so
they remain offset-bearing fields instead of receiving decorative names.

Nine more caller-connected callbacks extend the same visual and owner-motion
sequences. They cover owner-relative position setup, visual completion, readiness
gates, effect cleanup, and continuation installation. Six more arithmetic-heavy
neighbors remain in assembly after exact-sized C still differed in register
allocation; their recovered behavior is insufficient reason to weaken the shared
types.

Eleven callbacks from the next object-motion chain now expose paired setup,
visual-completion, countdown, and offscreen transition behavior. Four arithmetic
outliers remain in assembly after the capped matching pass. Their interfaces are
recorded for later caller-driven recovery, without forcing unstable compiler
shapes into the accepted source.

Three boundary callbacks now share `RuntimeObject` and `RuntimeObjectVisual`. Each performs the same base update, adds the visual's coordinate at offset `0` to the object's signed adjustment at offset `0x45`, and invokes the still-unidentified operation at `sub_807C298` when the result is nonpositive. Their variant suffixes remain until the callback-table owners are identified.

`BehaviorObject` is a narrower alternate overlay used by 49 callbacks that previously occupied `text_low_helpers.c`. It exposes a visual pointer, active update callback, and signed countdown at `0x9C`. The callbacks form three repeated families: starting an action before installing another update, conditionally forwarding when visual flag `0x08` is set, and counting down before setting visual state `0x10`. The entry points retain address names because their owning dispatch tables are still assembly; the shared control flow and object fields no longer do.

Four late command transitions now use the same `RuntimeObject` visual and update fields. Three wait for visual completion before issuing command `0` or `13`; the fourth tests the still-structural word at `0x80` before issuing command `10`. Their names expose those exact gates and effects without claiming a gameplay owner.

Six neighboring upper-region callbacks now extend that command-transition family. Three wait for the common readiness poll before selecting animations `8`, `4`, or `2`; one waits for visual completion before selecting animation `9` and setting a 60-tick delay; one waits for `linkedObject` to clear before selecting animation `13` and returning to the shared idle callback. The sixth integrates `value8C` into vertical position, subtracts the established vertical acceleration, then adjusts the position and selects animation `12` with sound `0xD5` when the step becomes nonpositive. Its name keeps `value8C` structural because other sequences use that slot differently.

The last isolated upper object callback now joins the late visual transitions. It waits for the same global gate used by neighboring sequences, starts the established timed visual operation with duration ten, and installs its next update. The gate remains generic because its implementation and gameplay owner are still assembly-only.

Twenty-nine callbacks extracted from the first large miscellaneous bucket now complete the visual-command family. Sixteen wait for visual completion, issue command `0` with no secondary value, and stop their update. Thirteen perform the same terminal transition with secondary command value `0x2000`; they directly pair with the thirteen previously recovered `0x204D` variants. One parameterized typed implementation now expresses all three families. Variant suffixes preserve distinct callback-table entry points whose sequence owners remain in assembly.

Eleven neighboring terminal gates now form two more typed families. Five wait for visual completion and either stop the active update or return to the shared idle callback. Six wait for `value80` to clear and then invoke an established trigger or cleanup transition. Lettered variants preserve callback-table identity where the owning sequences remain in assembly.

Nine setup callbacks now use `RuntimeObject` directly. Six forward the stored `positionOwner` into the shared setup routine and optionally install a continuation. Three take the owner as an explicit argument; one also initializes `behaviorState` to 1. Variant names remain structural because the assembly callers do not yet identify the gameplay sequences.

Six timed follow-up setups now expose the shared `timer` and `followup` fields. They configure kinds 2, 6, or 7 for durations of 3, 5, or 12 ticks, then install distinct assembly continuations. The numeric kind remains explicit until the underlying setup routine and its resource table are recovered.

Four continuation installers now extend the callback-result family. Three install the next `update` and return 1; one installs its update without a result. Their distinct entry points remain lettered because the callbacks' owners are still assembly-only.

Fourteen small value transitions now use the shared object and visual layouts. They cover `valueA0` and `value84` countdowns, four delayed `value80` gates, a direct `value80` continuation, three visual-completion continuations, two state resets, and two identical vertical-position updates. Offset `0x84` is proven to be a signed countdown word but keeps the structural name `value84` until its producer identifies the unit.

The final fourteen object callbacks from miscellaneous bucket 01 now use `RuntimeObject` and `RuntimeObjectState` throughout. They synchronize a linked object's position, preserve and replace update callbacks, expose state values at `0xA4` and `0x113`, read a signed byte from the state-owned source at `0xE4`, and express several terminal gates. The callback literal `0x0808A201` remains address-named because no symbol or recovered entry point currently identifies it.

Fourteen setup forwarders from miscellaneous bucket 02 now form a parameterized family. They stop sound `0x6C`, `0x81`, `0x11A`, or `0x11C`, then preserve all arguments and return the result from one of three established object setup routines. A separate zero-argument variant preserves the opposite call order used by its original sequence.

Fourteen readiness-gated animation transitions now share one typed implementation. Each waits for the field readiness query to clear, starts animation 2 or 3 with zero command arguments, and installs its own continuation. Variant suffixes preserve callback-table entry points whose gameplay owners remain in assembly.

Seven `value80`-gated callbacks now select animations 0, 4, 7, 9, `0x16`, or `0x18` and install their established continuations. Nine visual-completion callbacks form two terminal families: four disable the visual with `-1` parameters and stop, while five select animation 0 or 6 and invoke the shared cleanup transition.

Nine linked-object transitions now use `linkedObject` directly. They release or wait for a linked object, select follow-up animations, preserve terminal callbacks, and handle two nested-owner entry gates through a narrowly scoped structural overlay. No gameplay entity identity is assigned to that nested overlay.

Ten cleanup and readiness gates now expose the object's `cleanup`, `descriptor`, `flags79`, and structural byte `value74`, plus visual flag byte `flags11`. They stop or release the object after proven gates and preserve explicit sound identifiers. The `flags11` update uses an explicit local to retain the original compiler's register allocation.

Three more owner-based setups now stop sound `0x81` or `0x11C`, forward either the stored or supplied owner, and install the proven continuation. Five direct animation transitions select animations 2, 5, 9, or 10, set their sound or visual parameter where present, and advance immediately.

Nine remaining small transitions now expose signed X motion, comparison against `value84`, setup-result gates, `value80` waits, field readiness, and the state-owned subobject at offset 8. Two motion helpers retain explicit arithmetic temporaries because their signed rounding and exact register allocation are observable parts of the matching build.

Three additional visual-completion variants now use the shared object layout. They select animations from state at `0x9C` or flags at `0x98`; one also starts effect `0x151D`, installs a secondary update at `0x5C`, and advances the primary update at `0x4C`.

Four late visual transitions now expose linked-object completion, linked-chain flag propagation at `0xA8`, animation and sound setup, and terminal cleanup. Their semantic aliases describe the proven gate and effect; unresolved sound and animation values remain numeric.

Two neighboring callbacks now complete this late-transition group. One waits for visual completion, snaps both live and base coordinates to a position supplied by its owner, clears the visual, stops sound `0x119`, and advances. The other starts animation 4 on a nested linked object, installs a 32-tick timer and follow-up callback, then plays sound `0x120`. The owner and source layouts are named only as far as their observed position relationship proves.

Three identical delayed-motion callbacks now form one explicit family. They abort through the common action exit when object flags `0x38` are set, count down `behaviorState`, write `0xB400` and `-0x1CC` to the linked object's words at `0xA0` and `0xA4`, start animation 2, set visual flag `0x10`, and branch to family-specific continuations. The two linked words remain structural until the downstream motion code proves their units.

Three parallel callbacks use the same delayed-motion template with linked value `0xA00` instead of `-0x1CC`. Keeping both parameter sets in one generated family makes the behavioral difference explicit without duplicating the control flow.

Two more late callbacks now expose `value80` and `auxiliaryState` instead of raw offsets. One waits for visual completion and selects animation `0x0A` or `0x0B` from `valueA8`, with the zero branch installing a secondary effect update. The other waits for `value80` to clear, starts animation 5, arms a 32-tick timer, and plays sound `0x84`.

The widely reused state-action entry gate now has a typed home. It rejects incompatible object mode bits, requires an attached state whose reservation bit is clear, installs the action callback, clears `value80`, registers a state callback, marks the state reserved, and activates it. The gameplay action itself remains unnamed because both installed callbacks are still assembly-only.

Five early state transitions now use the same object layout. Each waits for `value80` to clear before selecting its next animation and callback; variants also stop a sound, arm a short timer, or track whether an owner condition became positive during the first `0x4000` ticks. Offset `0x60` is now exposed as a third callback slot because one transition installs an independent update there before advancing the primary callback.

Two adjacent callbacks complete this early group. One polls a shared asynchronous handle, copies its output into the object's current X and Y positions on every tick, and releases the handle when polling completes. The other waits for the common readiness check and selects animation 2 or 6 from the low bit of `behaviorState` before advancing.

Seven early visual transitions now share a second explicit family. They wait on visual completion or linked-chain exhaustion, choose animations from `valueA0`, `valueA4`, `valueA8`, or `behaviorState`, install primary and secondary callbacks, and start effects `0x1485` or `0x1509` where required. Numeric animation and effect identifiers remain explicit pending recovery of their resource tables.

Three remaining early callbacks now expose their actual control flow. One updates an owner until a signed timer expires, then clears a state halfword when its controlling word is zero. One moves left by `0x133` fixed-point units per tick while lowering toward height `0x800`, finishing after crossing screen X `-32`. The third waits for `value80` to clear and chooses `valueA8` uniformly from the half-open range defined by `valueA0` and `valueA4`.

Ten neighboring callbacks extend the same early object sequences with paired animations, effect setup, a four-way continuation selected by `valueA8`, vertical integration through `value8C`, linked-chain teardown, and visual offset decay. The visual halfwords at `0x04`, `0x06`, and `0x0C` and state members at `0x38` and `0xB4` remain structural; their update relationships are proven, but their rendering units are not.

Twenty-seven middle-address callbacks now form five explicit object-transition families: terminal action wrappers, visual-completion finishers, readiness-poll continuations, visual-flag continuations, and two follow-up initializers. Their C-facing names describe those families, with letter suffixes where the assembly-only owning behavior tables do not yet support gameplay-specific identities. The repeated control flow is represented once per family instead of as unrelated address-named functions.

Fifteen caller-connected callbacks from one middle scene chain now cover variant-selected
animation setup, visual-completion advancement, signed timer gates, and `value80` gates.
The two variant paths read a signed selector through the object's position owner and
choose animations 2 through 8, while later stages arm explicit delays and sounds before
installing their continuations. The owner member at offset `0x28` and its selector at
`0xEC` remain structural because their gameplay identity is still confined to assembly.

The next object sequence recovers an owner-supplied starting X position, command `0x4029` setup, and a linked position-history list. Each motion tick shifts the object left by `0x280` fixed-point units and propagates the previous X position through the list until the object crosses screen X `-40`.

`object_traverse_child_tree_noop` recursively visits both child links of an independently observed tree-node layout. It performs no action at each node. The explicit `noop` suffix is intentional: assigning cleanup or rendering semantics to a side-effect-free traversal would be fiction.

The recovered repeating-command sequence starts command `0x4029`, retriggers its action and sound every six ticks, and exits after six cycles once the visual completion flag is present. The alternative finishing animation still depends on the unresolved word at `0x03000F6C`, so that choice remains structural.

Two shared-motion callbacks now expose their 24.8 fixed-point coordinate flow. Both poll the handle at `0x03000E18`; one updates X/Y and removes the object when complete, while the other updates X/Z, advances the visual angle, and installs its continuation. Their output globals remain address-bound because the producer is still assembly-only.

`object_begin_effect_centered_between_field_actors` positions an effect from its owner's X coordinate and the active field actors' Y coordinates. It uses the lone active actor's Y or their average when both are active, then starts the proven animation, scale, sound, and continuation. The effect's gameplay identity is not visible in current C.

Nineteen small object callbacks from the former root bucket now form explicit visual-completion, readiness-setup, `value80`-gated, and state-helper families. Their names expose animation choices, sounds, timers, callback installation, linked-object behavior, and the one ballistic motion update. Variant suffixes and offset-bearing value names remain where neighboring assembly does not establish a gameplay identity.

The 170 scripted-action factory wrappers formerly collected in `text_upper_helpers.c` now live together as one object-runtime construction layer. Every wrapper forwards three coordinates, an event identifier, an update callback, visual identifiers, path-generation settings, orientation flags, and a point-data stream to `object_create_scripted_action`. The two factory macros distinguish entries that mirror the caller's orientation into both object and visual flags from entries that set those flags independently.

The individual factory symbols remain address-named ABI entry points because their owners are ROM callback tables and their callbacks are still assembly-only. Their declarations now expose the complete construction recipe, which is the strongest current evidence; assigning attack or entity names from numeric visual IDs alone would be unreliable.

Four miscellaneous-bucket callbacks now form the saved-update transition group. One stores the active update in `auxiliaryState`, runs the established setup routine, and installs a polling continuation when setup remains pending. That continuation starts animation 2 and restores the saved update after visual byte `0x21` clears. A related callback observes the visual pointer at state offset `0x10` before releasing the object, while the fourth invokes the callback at descriptor offset 4 after the shared field-readiness gate clears. `auxiliaryState` and the descriptor remain structural outside these proven uses.

The first forty-two callbacks recovered from miscellaneous bucket 03 are now grouped by their actual transition contracts. The visual-completion family selects fixed animations and continuations, with `idle` used only for the established common idle callback. A second family decrements the 16-bit timer first but tests the signed pre-decrement value, preserving the original edge behavior. Timed visual transitions set explicit delays from 1 through 60 ticks. The setup group exposes direct `value84` and `value8C` initialization, `value80` gates, readiness, and sound-stop ordering. Lettered variants remain where the assembly-only sequence owners do not justify gameplay names.

The same bucket's remaining straightforward visual transitions now expose commands `0x4071` and `0x4029`, relative animation selection from `valueA8`, a signed `behaviorState` countdown, fixed leftward motion, and terminal gates combining object flags, visual completion, `value21`, and linked-object presence. These names describe the observed state-machine decisions; they do not assign encounter identities that the current assembly does not prove.

Eight further bucket-03 callbacks now expose linked-object motion, owner suspension, flag-`0x20` cleanup, and vertical integration. Five coordinate an object's animation and update with its linked object or position owner, two poll the shared object status operation before stopping, resuming, or deactivating a visual, and one integrates `verticalPosition` through `value8C` until reaching fixed-point height `0x2800`. The owner and linked-object relationships are proven by their shared layouts; their gameplay identities remain unresolved.

The final eight object callbacks from the staging file now use `RuntimeObject`, `RuntimeObjectState`, `FieldActor`, and the established field-object owner layout. They cover a nested visual repeat counter, follow-up kind 3 setup, nested-chain completion, visual value `0x0C` accumulation, an animation-1 transition, paired field-object reset, second-actor position synchronization, and attachment to the first field object. The literal callback `0x081141F5` remains explicit because it enters the middle of an assembly routine and has no independent symbol.

Fourteen early-object callbacks now expose a connected timer, readiness, auxiliary-motion, and periodic-effect sequence. They preserve effect identifiers `0x1810`, `0xDB2`, and `0xDBB`, sound identifiers `0x6C`, `0x81`, `0xAF`, and `0x111`, plus the shared effect-object slot at `0x03000E3C`. The nested owner selector at offset `0xEC`, the auxiliary-motion arguments, and the gameplay identity of these numeric effects remain unknown. Their aliases therefore describe only the observed transitions.

Fourteen following callbacks continue the same runtime chain through readiness cleanup, saved-position restoration, fixed-point movement, visual gates, and periodic effects. The saved signed halfwords at offsets `0xAE`, `0xB0`, and `0xB2` remain structural because several sequences overlap them with wider state fields. Effect identifiers `0xD82`, `0xDB2`, `0x1BFE`, `0x1C52`, `0x1C5B`, and `0x1DF8` stay numeric pending recovery of their resource owners.

Three middle-runtime callbacks now expose their proven value gates and continuation changes. Their names describe the observed test and state transition while leaving the assembly-owned scene identity unresolved.

Eight late-middle callbacks now cover three `value80` gates, paired visual-completion
transitions, and a timer-driven handoff. Four neighboring routines remain in assembly
after exact-sized but register-sensitive C failed the capped pass. The accepted names
describe their observed gates and continuations without assigning scene identities.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports 1,602 linked C functions checked, 1,602 exact, and zero mismatches.
