# Mario Bros minigame

## Command readers

Two command-reader families near `0x08F6F26C` and `0x08F95DEC` use the same 68-byte `MarioBrosCommandContext`. Each recovered handler copies one byte from `cursor`, advances the cursor, and stores the byte at one of offsets `0x1E`, `0x1F`, `0x24`, `0x26`, `0x27`, or `0x2C` through `0x2F`.

The shared layout lives in `include/mario_bros/command_context.h`; the primary and secondary reader objects live under `src/mario_bros`. Field names remain offset-based because current C does not show how the command dispatcher or later consumers interpret those bytes. Both families also contain a no-op command handler.

## Object layout

The overlapping object views used by table selection, animation, movement, and state transitions now share `MarioBrosObject` from `include/mario_bros/object.h`. Repeated behavior supports names for the state byte, packed flag bytes, display and animation frames, animation variant, and X/Y position.

Offsets `0x18` and `0x1C` deliberately remain `value18` and `value1C`. Movement routines treat them as coordinate deltas, while table-selection routines store a selected value at `0x18`; this likely represents related object classes with a shared prefix. Naming them as universal velocity or handler fields would discard that distinction. Packed overlays document the independently accessed bits in flag bytes `0x08` and `0x0A`.

Unused stream, scale, tagged, list-node, and halfword layouts were removed from `mariobros_helpers.c`. They had no generated functions or consumers and therefore supplied no recoverable evidence. Keeping such speculative scaffolding would make later field inference less reliable, not more.

The surviving contents of that catch-all file are now grouped under `src/mario_bros`: object animation and table selection, state helpers, no-op callbacks, and a fixed-size buffer fill. The linker still selects the original per-function sections, so this organization does not imply false source-level ownership.

The byte at global runtime offset `0xC5A` is now `sequenceIndex`: two helpers advance it after emitting an event, and three wrappers use it to select a callback from parallel tables. The recovered `MarioBrosRuntime` also names the pointer chain used to obtain that event's argument. Unobserved ranges remain explicit padding.

All currently decompiled Mario Bros code now lives under `src/mario_bros`. Legacy no-op callbacks, object transitions and command wrappers, movement/platform helpers, and the small tilemap helper are named by their observed roles rather than by extraction order.

The former mixed platform file is split into hardware setup, object movement, global callback forwarding, and tilemap clearing. The movement helper at `0x08F63DB8` now uses the shared object layout: it tests `state` and writes `value1C`, whose more specific meaning remains class-dependent.

`include/mario_bros/callback.h` names the recovered callback ABI. The assembly routines are register trampolines that jump through argument 0, 1, or 2; C now describes those operations as callback calls. Five global callback slots are named by signature and family. Their gameplay purpose is still unknown because the currently decompiled code only reads them.

`include/mario_bros/functions.h` provides semantic C names while retaining the original `sub_` symbols required by assembly callers. Confirmed names cover interrupt shutdown, platform-state reset, fixed-size buffer and tilemap clearing, object position integration, readiness-gated state advance, and the state-7-guarded fall initializer. The two position routines use `a` and `b` suffixes because their X-coordinate helpers differ but their gameplay classes are not yet identified.

Replicated helpers now follow the same rule. Their names state the observable contract, including selector-based callback dispatch, frame-table bit updates, state-controller reset, command 12 forwarding, and event emission followed by sequence advancement. Letter suffixes distinguish parallel implementations whose owning gameplay classes are still in assembly.

Four additional selectors copy one of two local table values into `value18` according
to object flag bit 2. Four animation clocks advance the frame byte and wrap or toggle
the variant at their proven limits. The `a` through `d` suffixes remain because the
parallel ROM and work-RAM tables do not yet identify the gameplay classes that own
them; the frame limits and zero-based or one-based wrap behavior are now explicit.

Two mirrored geometry helpers add a flag-selected horizontal offset and clamp only
positive overflow. Two more return the remaining horizontal distance when both axes
fall inside the supplied limits; the vertical test uses absolute magnitude. Their
callers have not yet established a gameplay-specific coordinate space, so the names
state only the measured behavior.

The primary runtime at `0x03000F50` and its mirror at `0x03000F40` expose matching
object-pointer and activity arrays. Mirrored lifecycle helpers release an optional
allocation, clear the object's activity slot, and restore its 60-byte template.
Link helpers attach a selected pool object and set the two-bit link mode to 2. A
second pair copies source flag bit 7 into destination flag bit 0. Spawn helpers
allocate kind 5, initialize the selected object, set state 3, and establish the
back-pointer through the allocation at offset `0x38`. Array ownership, the meaning
of kind 5, and the remaining flag bits are deliberately retained as unknowns.

The pool record at offset `0x4504` has a second allocation at record offset `0x20`.
Its mirrored reset helpers release that allocation when present, then restore the
complete 36-byte record from the corresponding primary or secondary template. Two
lookup pairs now expose separate contracts: one scans the 28 runtime identifiers at
offset `0x4544`, while the spatial pair delegates coordinate selection and returns
the low byte of the selected object's `value24`. The meaning of that identifier is
not yet established.

The 16 records at runtime offset `0x4504` also carry a one-based dispatch selector
in their first halfword. Mirrored dispatch loops use that selector to call the
parallel primary and secondary callback tables. Callback purpose and record class
remain unknown. The nearby wrapped-coordinate pair remains in assembly because the
compiler consistently chose a different scratch register despite matching behavior;
forcing an invented ABI would weaken the recovered interface.

Runtime offset `0x4480` is a shared route target. Two mirrored guards call their
family-specific callback only when target byte `0x29` is clear. A second pair uses
the linked object's byte at allocation offset zero to choose whether `0xF0` is
written to target halfword `0x18` or `0x1C`. Those fields remain route-numbered
because their downstream interpretation is still in assembly.

Runtime byte `0xC5B` is now `directionOffset`. Two mirrored helpers add it to the
object's signed X tile coordinate, rotate the resulting byte right by two bits,
store it in `value24`, clear `animationVariant`, and enter state 5. The direction's
gameplay labels are not yet proven. The upper-edge geometry pair validates the upper
half of a bounded vertical range, checks the absolute horizontal magnitude, and
returns remaining vertical distance or `-1`.

The nearby relative-coordinate pair remains in assembly. Its behavior was recovered,
but two natural C shapes changed register allocation and literal reuse; preserving
the observed ABI and exact code is preferable to compiler-specific coercion.

Two mirrored falling-object updates now apply the established per-frame motion and
advance their objects when the terminal condition is reached. The adjacent prepare
pair initializes each family-specific linked object through the same narrow runtime
overlay. Family suffixes remain because the owning gameplay tables are still in
assembly.

## Next boundary

The currently decompiled slice is detangled. Further gameplay-specific names depend on assembly callers, callback initialization paths, and table contents that are outside the current C boundary. Resume this subsystem when those dependencies are decompiled rather than replacing explicit `a`/`b` variants with guesses.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports 1,482 linked C functions checked, 1,482 exact, and zero mismatches.
