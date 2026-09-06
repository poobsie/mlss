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

`object_start_secondary_visual_and_continue` starts visual mode 2 with the established default command, selects visual flag state 2, and installs the continuation at `0x0809C660`. The surrounding behavior identity remains unknown, so the name describes only the proven transition.

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

Two continuation installers extend that middle-runtime chain. One waits for `value80`
and a signed timer, starts animation 9 and effect `0x138A`, clears the auxiliary
callback, and advances. The other waits for `value80`, installs three independent
follow-up callbacks, starts animation 7, and arms a 16-tick continuation. Those
callback slots are kept structural because their assembly-owned effects do not yet
support gameplay-specific names.

Four direct leaves extend the same callback graph. Two identical owner-release
callbacks poll the object, stop sound `0x2E`, clear the state reservation bit, and
either reactivate or stop the position owner according to its signed state value at
`0xF6`. Two visual continuations start animations 5 and 10 after their respective
completion and readiness gates. The signed state value remains offset-named because
its wider owner behavior is still in assembly.

One adjacent timer continuation now installs its three observed follow-up callbacks,
starts animation 5, plays sound `0x38`, restores visual mode 2, and advances. The
callbacks remain address-named because their assembly bodies do not yet establish
more specific roles.

Eight late-middle callbacks now cover three `value80` gates, paired visual-completion
transitions, and a timer-driven handoff. Four neighboring routines remain in assembly
after exact-sized but register-sensitive C failed the capped pass. The accepted names
describe their observed gates and continuations without assigning scene identities.

Nine later callbacks extend the linked-object sequence through periodic effect `0x212B`, paired animation-4 gates, shared-effect position synchronization, readiness sound switching, owner-variant selection, linked animation completion with effect `0x1FA6`, and effect `0x1E8A`. Owner selectors and numeric effect identities remain structural; no encounter-specific names are inferred from them.

Twelve callbacks from the following `0x080703B0` through `0x0807127C` sequence now cover value gates, visual countdowns, fixed-motion initialization, effect `0x201C`, command `0x40E7`, linked-owner cleanup, and final animation handoffs. The word at offset `0x88`, numeric animation and effect identifiers, and the gameplay identity of the position owner remain deliberately structural. Three address spans containing unnamed raw-code tails and two register-sensitive indexed or readiness routines were rejected instead of assigning false function boundaries.

Three middle-runtime leaves add one value-gated transition and two compact continuation updates. The aliases state only the proven gate or callback change, retaining the original symbols where the surrounding assembly does not establish a scene-specific role.

Twenty-one remaining scripted-action factories now use the established thirteen-argument construction interface. Each wrapper preserves its callback, event, visual, orientation, path, and point-table configuration in C. Callback addresses remain in the aliases because the corresponding action bodies are still assembly-only; assigning encounter-specific names before those bodies are recovered would add guesswork without information.

Seven compact callbacks in the `0x080742FC` through `0x080746A8` object chain now expose readiness resumption, two signed countdowns, animation and effect setup, a linked-child wait, and a `value80`-gated timer handoff. Effects `0x22E2` and `0x22C0`, sound `0xAD`, and the linked child's gameplay identity remain numeric or structural. Three neighboring owner-coordinate routines and one owner-variant selector stayed in assembly after exhausting their shaping budget.

Eight callbacks in the `0x08075BB8` through `0x08075F4C` chain now expose an owner-forwarded transition, a readiness cleanup, two visual-completion gates, paired periodic effect `0x23CC` loops, and terminal effects `0x23DE` and `0x2423`. The owner argument and numeric effect identities remain structural. Two adjacent routines stayed in assembly after their natural C forms produced compiler-specific four-byte differences, while the larger global-object and construction routines surveyed after them were deferred as a separate ownership slice.

Fifteen callbacks from the following `0x08077140` through `0x08077924` sequence now cover linked-chain cleanup, visual-completion handoffs, paired countdowns, random animation selection, and effects `0x24BA`, `0x24E0`, `0x24E9`, `0x24FB`, `0x2515`, `0x2563`, `0x25AB`, `0x25B9`, `0x25F5`, and `0x2983`. The owner forwarded through `sub_810DD7C`, the linked objects, and the numeric resource identities remain structural. Larger construction and global-state callbacks in the surveyed `0x08076034` through `0x08077924` range remain in assembly for a later typed slice.

Sixteen callbacks selected from the next forty-function survey now cover visual and `value80` gates, linked-object completion, fixed leftward motion, command `0x4029`, random animation selection, owner signaling, and effects `0x29D2`, `0x2A58`, `0x2A8B`, and `0x2AA6`. The global sequence counter at `0x03000ED0` and variant word at `0x03000F6C` are address-bound pending recovery of their owning process. Raw-tail boundaries and the larger constructors in the surveyed `0x08077ECC` through `0x08079C3C` range remain in assembly.

Ten small runtime transitions now use the shared object layout across several
existing callback chains. Three readiness gates select the established motion or
effect continuations, one attaches the caller-supplied owner before beginning a
horizontal-motion update, and one advances `valueA8` to its proven limit before
arming a 300-tick child wait. The remaining callbacks count down timers, restore a
saved follow-up, update X from a signed offset, wait for `linkedObject` to clear,
or begin a fixed vertical descent. The readiness predicates, owner identities,
timer units, and numeric effects remain structural until their assembly-only
producers and continuations establish stronger names.

`runtime_object_start_timed_motion` stores the caller's duration at object offset `0x92` before forwarding the object and motion value to the established initializer. The duration unit remains unspecified because the initializer and tick consumer are still assembly-only.

Twenty-three repeated vertical-motion callbacks now share the typed object and state
layouts. Seventeen integrate vertical velocity and position, then select animation 6
and either command `0x204D` or `0x2000` after the shared motion predicate clears. Six
related landing callbacks clamp the object to `state->floorHeight`, select animation
8 with command `0x204D`, update the proven flag bits, and install their continuations.
Lettered path suffixes distinguish otherwise identical callbacks whose assembly-only
continuations do not yet establish gameplay-specific identities.

Three later object callbacks now expose distinct state-machine actions. One raises
the object's Y coordinate, establishes fixed vertical position `0x2600`, selects
animation 1 with command `0x40C2`, sets visual mode 2, plays sound `0x15D`, and
installs its continuation. Another advances byte `0x75` by five, performs the
neighboring setup, resets the animation, and stops updating. The third decrements a
positive signed timer and otherwise installs callback `sub_809E0EC`. Byte `0x75`,
the command, and the continuation retain structural or address-based names because
their assembly-only producers do not yet prove gameplay identities. The adjacent
command-`0x4109` spawn callback remains in assembly after both bounded C shapes
changed register allocation.

The paired-object transition callbacks now expose the runtime-owned primary and
secondary action objects instead of repeating raw offsets `0x70` and `0x74`. The
recovered paths cover motion polling, countdowns, animation and command selection,
visual completion, counterpart synchronization, and linked-object handoffs across
two related variants. Numeric commands and the variants' gameplay identities remain
structural. Four register-sensitive members remain in assembly after the capped
shaping pass; their surrounding typed callbacks retain the raw continuation symbols
without inventing names for code that did not match exactly.

Two paired fixed-height motion callbacks now expose their fixed-point Y step,
vertical height, conditional motion-step initialization, and continuation. Their
neighboring owner-attachment callbacks name the proven owner readiness test before
starting animation 3 with command `0x40C2`. The related owner-effect and
screen-position variants remain in assembly after the capped shaping pass because
their natural typed forms changed instruction scheduling or omitted compiler
bookkeeping bytes. Numeric commands, effect `0x1202`, and the pair's gameplay
identity remain deliberately structural.

Five repeated action-object polling callbacks now select the runtime's primary or
secondary action object through the shared typed layout. Each waits for visual
readiness, recognizes the established flag modes 2 and 4, derives a fixed-point
motion value through the relocated scale routine, clears the pending control bit,
and installs its path-specific continuation. The distance parameters 4, 15, and 18
and the primary/secondary path distinction are proven; their gameplay identities
remain unknown. Neighboring descriptor handoffs and three register-sensitive
polling variants remain in assembly after the bounded shaping pass.

Seven later callbacks complete the same paired action paths. Three poll an action
visual, clear its animation and visual mode bits, and install a caller continuation.
Two play sound `0x2E` before selecting the proven primary animation 13 or secondary
animation 8 command. The final pair clears and stops the primary or secondary
action once its visual is ready. The numeric sound and command identities remain
structural, and the unlabeled constructor tail immediately following the terminal
pair remains in assembly.

Two neighboring lifecycle callbacks now use the shared runtime-object interface.
One waits for `value80` to clear before installing the existing state-motion
continuation. The other detaches an embedded object when applicable, releases its
visual state, clears all observed behavior and ownership slots, and performs the
established flag-gated resource release. The containing state's offset `0x78` and
the released resource value remain structural because their producers are still in
assembly.

An adjacent motion step now advances the signed halfword at offset `0x92`, derives
vertical position from the object's base coordinate, and clamps at `value98` while
clearing the step value. `value98` stays structural because other object variants
use its low bits as flags, so a single stronger field meaning is not yet supported.

The neighboring interval helper clamps or reflects an input position across two
bounds, converts its distances from each bound through the runtime transform at
`0x03001038`, and returns the resulting signed output pair. Reflected inputs negate
both outputs. The transform retains its address-based identity because the same
runtime callback is used for operations whose narrower mathematical role is not
yet established.

One nearby runtime owner now exposes a target pointer at offset `0x08` and a
pending word at offset `0x04`. Its completion callback waits for bit `0x02` of the
target byte at `0x111` to clear, finalizes the target subobject at offset `0x08`,
and clears the pending word. The owner, target, and flag keep structural names
because their assembly callers do not establish a narrower object class.

The motion continuation paired with this family now waits for the established
completion bit at object offset `0x79`. For active modes 2 and 4 it clears the
current animation, removes visual control bits `0x40`, `0x02`, and `0x04`, then
restores the callback saved in `followup`. The visual bits remain numeric because
their rendering effects are not independently established.

Two setup callbacks feed that continuation path. For active modes 2 and 4 they
select command `0x2000` for object variant `-1` and `0x204D` otherwise, start
animation 5 or 4, and normalize the visual mode to 2. The animation-5 path enters
the motion update directly; the animation-4 path first saves the current update in
`followup`. Command identities remain numeric because the associated visual asset
tables are still assembly-only.

The animation-4 branch now has both continuations in C. Its first callback waits
for visual completion, selects animation 6 with the same variant-dependent command,
normalizes the visual mode, and enters the shared motion update. Its second callback
advances that motion, clears animation and visual control bits at completion, then
restores and clears `followup`. The underlying motion calculation remains in
assembly because its fixed-point fields are not yet independently identified.

The shared animation-5 and animation-6 motion path now also has its outbound
continuation in C. It advances the same assembly motion calculation, waits for
the completion bit, selects animation 8 with the established variant-dependent
command, normalizes the visual mode, and installs the cleanup callback that
restores the saved update. The command values and completion bit remain numeric
until their producers and rendering effects provide stronger names.

The later object-control cluster now exposes two additional compact callbacks.
One stops sound `0x6C` before forwarding the object, owner, and setup command to
the shared initializer. The other consumes visual completion by clearing the
object's active behavior through the established runtime helper. The sound ID
and visual bit remain numeric because their asset and renderer meanings are not
independently established.

The same control cluster now exposes a variant selector and a delayed followup
setup. The selector reads the position owner's established runtime variant,
chooses animation 7 or 8 for variants `-1` and `-2`, and installs the common
continuation. The setup waits for `value80` to clear, stores a 24-frame timer,
forwards command 6 to the shared state helper, and records its followup callback.
The command and continuation retain conservative names while their larger state
machines remain in assembly.

Two paired value-clear gates now expose the three-callback sequence used by this
cluster. Each resets the object, installs callbacks at offsets `0x58`, `0x5C`,
and `0x60`, copies the current behavior state into the short timer, and prepares
shared command 3. They differ only in the followup selected for the subsequent
control branch. Offset `0x58` is now named `auxiliaryUpdate`; its repeated use
beside the established secondary and tertiary callback slots supports that type.

The horizontal exit callback used by the short timer transition is now in C. It
decreases the signed horizontal step, updates the fixed-point X coordinate,
converts the object position through the existing runtime transform, and finishes
the object once transformed X falls below `-16`. The transform keeps its neutral
name because its broader camera or projection role is not yet independently known.

Its preceding arc callback is now in C as well. It applies the stored horizontal
step, integrates and decreases the signed vertical velocity, runs the same
position transform, and finishes when transformed Y exceeds `0x110` or
transformed X falls below `-16`. These are named as transformed bounds, not screen
bounds, because the helper's exact coordinate space remains unresolved.

A later timer-control pair is now represented in C. One callback waits for a
zero timer, starts animation 5, arms the linked object's timer for 16 ticks, and
installs the established flag-clear continuation. The other conditionally
attaches to a ready position owner, counts down, clears the state subfield at
`0xB4` when its controlling word is zero, stops sound `0x5E`, and finishes the
object. The state subfield retains its offset-based name because its consumer is
not yet decompiled.

Two neighboring terminal gates are now in C. The first clears active behavior
when the signed timer reaches zero. The second waits for `value80` to clear,
plays sound `0xAD`, starts animation 1, applies the established object reset, and
installs the next flag-driven continuation. Numeric animation and sound values
remain unchanged because their asset identities are not established here.

The next two control callbacks are also in C. The first waits for `value80` to
clear, stops sound `0x5E`, clears the state halfword at `0xB4`, and installs the
raw continuation at `0x0808C601`. Inspection of that continuation shows a compact
per-axis integrator that adds signed fields `0xAE`, `0xB0`, and `0xB2` to the
three current positions; it remains raw to avoid adding a symbol to the stable
function denominator. The second stores a 24-tick timer, selects command 4 or 6
from the position owner's established variant, and installs its followup.

The traced velocity path now includes its compact setup and linked countdown
transition. The setup stores a three-tick timer, prepares command 2 with the same
duration, and records the established followup. The countdown conditionally
attaches to a ready position owner, then starts animation 7 on the controller and
animation 2 on its linked object, normalizes the linked visual mode to 2, and
continues into the existing completion path.

The same velocity-control family now includes three later transitions. One starts
animation 3, clears the visual mode bits, and begins a 45-tick countdown. A
`value80` gate stops sound `0x6C`, prepares command 3 with argument `0x20`, and
stores a 24-tick followup. That followup starts animation 4, clears the same
visual mode bits, and installs the established 30-tick countdown callback.

The later action family now exposes its shared finish routine and one jump setup.
Finishing is gated by the object's active visual mode; it clears the owner's
pending flag, removes a linked object, restores visual flags and parameter state,
stops the active animation command, and clears the update callback. The jump
setup plays sound `0x2B`, stores a fixed downward acceleration, starts animation
5 in visual mode 2, and enters the established vertical-motion continuation.

That jump path's mirrored motion and landing callbacks are now represented in C.
Both integrate the signed vertical velocity and acceleration, switch to animation
6 while descending when the shared transition helper does not take control, then
land at the state's established floor height with animation 8. The two paths keep
their observed command variants, `0x204D` and `0x2000`, through both transitions.

The adjacent action branch now includes another alternate-command vertical path
and its shared cleanup gate. The motion callback follows the same signed vertical
integration and animation-6 transition used by the established jump family, then
continues to its existing `0x2000` landing callback. The cleanup gate clears the
owner's pending flag and finishes on action flags or after its short timer expires.

Two later alternate-command jump branches now share the typed vertical-motion
implementation. Each integrates velocity and acceleration, switches to animation
6 during descent when the shared transition helper remains idle, and enters its
established landing continuation. One paired landing callback is also in C; it
clamps to the state's floor height and starts animation 8 with command `0x2000`.

The forward jump family now includes two more alternate-command descent paths
and a compact visual-completion stop. The descent callbacks preserve the same
typed velocity integration, animation-6 transition, and command `0x2000` landing
handoff. The stop callback waits for visual completion, stops command `0x2000`,
and clears the object's active update.

The later action branch now includes paired short cleanup gates and its alternate
floor landing. Both gates clear the owner's pending flag, then finish on action
flags or after their observed 24- and 20-tick limits. The landing callback clamps
vertical motion to the state's floor height, starts animation 8 with command
`0x2000`, restores visual mode 2, and enters the existing completion callback.

A neighboring variant branch now includes its paired 24- and 20-tick cleanup
gates. Both retain the established action-flag and owner-pending behavior before
invoking the shared action-finish routine.

Three more alternate-command landing callbacks now use the typed floor-clamp
implementation. Each integrates the signed vertical step, clamps to the state's
known floor height, clears the active motion flag, starts animation 8 with command
`0x2000`, restores visual mode 2, and installs its established completion callback.

The following object branch now has typed interfaces for its compact owner and
visual callbacks. Its auxiliary callback forwards the supplied owner and command,
then emits effect `0x1CF9` at the object's current fixed-point position. The visual
callback waits for completion, starts animation 9, clears the visual mode bits,
and installs the adjacent idle return callback.

The owner-position effect branch now exposes its setup and readiness-gated
completion callbacks. Setup reads the three fixed-point words at owner-state
offsets `0xD8`, `0xDC`, and `0xE0`, offsets the first coordinate by `0x22`,
then configures animation 5, the object's stored display value, and sound
`0x112`. Completion waits on the shared readiness query, starts animation
`0x0F`, restores visual mode 2, stops that sound, and enters the established
12-tick visual-completion delay. The first two owner-state words remain
offset-named until callers distinguish their axes from other positional views.

The connected paired-object path now exposes its motion-completion handoff. Once
motion polling clears, it selects the established primary or secondary animation
command, restores visual mode 2, copies the position owner's current coordinates,
starts the 24-tick countdown with sound `0xAE`, and continues into the existing
linked-object creation callback.

The same paired-object chain now exposes its auxiliary-object setup callbacks.
One starts the primary or secondary animation-1 command, creates command object
`0x208D`, marks that object's runtime flag `0x20`, and installs the existing pair
continuation. A later visual-completion callback creates command object `0x2089`
from the secondary action owner, clears its upper flag bits, attaches it as the
linked object, and selects the established motion-node update when its mode is
active.

The sibling owner-position setup and the paired path's terminal transition are
now represented in typed C. The sibling setup selects its coordinate offset and
height scale from the object's established behavior state, copies the owner's
display ordering, starts animation 5, and routes to the corresponding completion
callback. The paired terminal transition conditionally refreshes the owner
binding, emits the variant-selected effect at the linked object's fixed-point
position, destroys that linked object, and rebuilds the controller effect from
the three known owner-state coordinates before continuing. The intermediate
paired-object constructor remains raw because its register allocation did not
match within the bounded source-shape attempts.

The auxiliary owner-position branch now has its typed setup and effect-spawn
completion. Setup mirrors the established owner-coordinate selection, copies the
owner's display ordering, starts animation 5 and sound `0x112`, then enables the
auxiliary visual path and installs its tertiary callback. Its completion waits
for shared readiness, restores visual mode 2, stops the sound, emits effect
`0x215C` at the object's fixed-point position, and enters the existing delayed
visual callback. The nearby paired-effect stop remains raw after the bounded
source shapes selected the opposite callee-save ordering.

The remaining setup and completion siblings in this owner-position branch are
now typed. One setup rebuilds the standard owner-relative effect and hands off
to a visual reset that restores mode 2, delays for 40 ticks, and stops sound
`0x112`. The alternate setup uses fixed X `-0x20`, owner-derived Y and height,
animation `0x0C`, and an observed raw auxiliary callback boundary before its
next transition. Its paired completion restores mode 2 and emits effect
`0x215C` at the object's fixed-point position before entering the established
delayed-spawn callback.

The later exit branch now exposes its compact motion-completion and visual gates.
The motion gate waits for the shared motion poll to clear, halves the observed
signed step at offset `0xAE`, clears the following two motion fields, resets the
motion helper, and enters the established off-screen continuation. The visual
gate clears behavior when completion bit 3 is set. The continuation and adjacent
effect teardown remain raw after their bounded source-shape attempts failed to
preserve the original instruction scheduling.

The outward auxiliary path now includes its animation-2 handoff and far-offset
owner effect. The handoff starts animation 2, restores visual mode 2, and enters
the established owner-offset setup. That setup rebuilds the effect from the
known owner-state coordinates with an X offset of `0x44`, applies display value
`0x280`, starts animation 3 and sound `0x11B`, then installs its observed
continuation. The preceding readiness reset and auxiliary motion poll remain raw
after bounded attempts changed store order and callee-save allocation; the raw
callback at `0x0810FBBD` remains intentionally unnamed.

The following runtime slice now includes a motion-update notification and a
state-cleanup predicate. The motion callback preserves its position owner,
runs the established motion step, forwards the owner and object when runtime
flag `0x20` becomes set, and enters the existing continuation. The cleanup gate
calls the established cleanup pair on the object's state only after its linked
object is clear. A nearby visual-and-link stop transition remains raw after its bounded
source shapes changed the original register allocation.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports every linked C function exact, with zero mismatches.
