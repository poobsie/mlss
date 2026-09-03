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
