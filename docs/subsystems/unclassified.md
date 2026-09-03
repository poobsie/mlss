# Unclassified C

This queue entry covers accepted C files that still sit at the root of `src/` or in address-based folders. It is a staging category, not a subsystem.

Take one caller-connected family at a time. Establish its actual ownership before moving it, then create or extend a subsystem document and remove those files from this category. Do not assign domain names from address proximity alone.

The former `text_upper_structural.c` bucket has been retired. Its event callback wiring belongs to field runtime, its sprite-backed lifecycle and motion variants belong to battle runtime, and its text cursor setter belongs to UI runtime. This split is based on callers and shared layouts, not the original address range.

The former `text_upper_helpers.c` bucket has also been retired. Its 170 entries are parameterized constructors for the same scripted object-action runtime, so they now live in `src/object/action_factories.c` with a typed shared construction contract.

Fourteen former `text_upper_functions/` entries have been assigned to battle runtime. Their evidence is structural and caller-connected: five release one or more owned sprites, five operate on the already recovered `BattleSpriteMotion` layout, two clean up large late-offset resources, and two form the construction/destruction pair for a two-variant sprite container. Gameplay identities remain explicitly unresolved where the available descriptors and assembly callers do not prove them.

Six more former upper-function entries now extend object runtime's late command transitions. They use the established `RuntimeObject` visual, linked-object, vertical-motion, timer, and update fields, and their adjacent assembly callbacks form the same state-machine chains. Their semantic names describe observable gates and effects; they do not invent identities for the owning gameplay sequences.

Fifteen former upper-function entries now form `src/field/callback_chains.c`. They share the callback slots and late flags of `FieldSceneObject`, use the field definition/profile preparation routines, and install callback sequences consumed by the same field dispatchers. This removes the raw offset casts while preserving variant names where the scene owners remain in assembly.

The `src/text_upper_functions/` staging directory is now retired. Its final fifteen files were assigned from concrete evidence: ROM labels and layer setup place six under screens, process definitions place two under process runtime, sprite visibility places two under graphics, shared field layouts place two under field runtime, one uses the established runtime-object transition layout, one releases shared global state, and one is a generic intrusive-list insertion. The remaining unclassified queue consists only of the three large legacy `text_misc_helpers_*.c` buckets.

The first extraction from `text_misc_helpers_01.c` moved twenty-nine visual-completion callbacks into object runtime. Their identical gates, shared `RuntimeObject` layout, and three explicit command-value families make the boundary mechanical rather than address-based.

The next extraction moved eleven terminal gates into object runtime. Five wait for visual completion before either stopping or returning to the common idle callback. Six wait for `value80` to clear before invoking one of two established transition routines. These remain distinct ABI entry points, but their repeated control flow is now expressed as typed families instead of raw offset casts.

Nine owner-driven setup callbacks have also moved into object runtime. Six pass the object's existing `positionOwner` to the shared setup routine, while three accept an owner from their caller. Their only proven differences are the continuation callback and one `behaviorState` initialization, so their semantic names preserve that evidence without guessing at the owning encounter.

Six adjacent timed follow-up setups now live in object runtime. Each stores its duration, configures a numbered follow-up kind with that same duration, and installs the corresponding callback in the typed `followup` slot.

Eighteen more object callbacks have left the staging bucket. Four install a continuation, with three returning the callback protocol's true result. The remaining fourteen expose countdowns, `value80` gates, visual-completion gates, timer setup, reset transitions, and two identical vertical-position updates. The word at object offset `0x84` is now a typed `value84`; its meaning remains explicitly unresolved.

Six non-object helpers have been assigned from their shared global owners. Three operate on the field runtime's active value-transfer state or primary actor object. Three release heap pointers in the general runtime global block, with the `0x03000FC0` variant also clearing its slot.

The remaining fourteen object callbacks from `text_misc_helpers_01.c` now use the shared setup and state-helper modules. They expose linked position synchronization, update preservation, state-byte gates, visual gates, and terminal callbacks. The final five mixed helpers belong to field view/process/display code and graphics process state. With those assignments, `text_misc_helpers_01.c` is retired; only buckets 02 and 03 remain unclassified.

The first extraction from `text_misc_helpers_02.c` moves twenty-eight object callbacks into two explicit families. Fourteen stop a known sound and forward their arguments into one of three shared setup routines. Fourteen wait for the field readiness gate, start animation 2 or 3, and install a sequence-specific continuation.

Sixteen more bucket-02 callbacks now extend typed object transition modules. Seven wait for `value80` to clear before selecting a proven animation and continuation. Four disable the visual and stop after visual completion. Five select animation 0 or 6 and invoke the common cleanup transition after completion.

Nineteen additional callbacks now form linked-object and cleanup families. Nine react to linked-object presence, completion, or a nested owner's active entry. Ten invoke cleanup callbacks, terminate on readiness or flag `0x20`, or release after `value80` or visual completion gates. Object byte `0x74` and visual byte `0x11` are now explicit structural fields.

Seventeen further object callbacks now have typed homes. Three perform owner-based setup, five start direct animation/sound transitions, and nine cover position motion, `value80` gates, field-readiness gates, and a state-owned subobject update. Their names state the proven mechanics and preserve numeric animation and sound identifiers.

Four saved-update and callback-dispatch transitions have also left miscellaneous bucket 02. They preserve and restore the primary object update around a shared setup operation, release an object when its state-owned visual clears byte `0x21`, or invoke the callback at offset 4 of the object's descriptor after the field readiness gate clears. The extraction leaves seventeen callable routines in bucket 02.

Miscellaneous bucket 02 is now retired. Its final routines resolved into field process and resource ownership, script branching and wait handlers, shared runtime-global teardown, and graphics staging or linked-visual operations. The only active unclassified C is now `text_misc_helpers_03.c`.

The first bucket-03 extraction moves forty-two object callbacks into four typed families. Nineteen wait for visual completion before selecting an animation and continuation, including one terminal command-`0x204D` variant. Seven interpret the pre-decrement timer as signed when deciding whether to advance. Seven combine visual completion with a fixed animation and delay. Nine cover direct setup, readiness, and `value80`-gated animation, timer, and sound transitions. Thirty-eight callable routines remain in the staging file.

Five non-object callbacks have now left bucket 03. Four operate on the field display runtime's object and process slots from `0x278` through `0x280`, including the two display-register synchronization callbacks. One copies a compact four-value graphics staging record into the established interleaved staging halfwords. Thirty-three callable routines remain unclassified.

Eight more object transitions now use the shared runtime layout. They cover two fixed command selections, timer increment and relative-animation setup after visual completion, signed state countdown, fixed X motion, a combined flags-or-visual finish gate, and a visual/link terminal gate. Twenty-five callable routines remain in the staging file.
