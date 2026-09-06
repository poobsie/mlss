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

The later Mario Bros support code also contains a compact M4A recovery helper.
When the shared sound-info identity differs from the established M4A value, it
disables both direct-sound DMA channels, clears the PCM DMA counter, and advances
the temporary identity lock. The implementation uses the existing `SoundInfo`
layout and hardware register definitions.

`include/mario_bros/callback.h` names the recovered callback ABI. The assembly routines are register trampolines that jump through argument 0, 1, or 2; C now describes those operations as callback calls. Five global callback slots are named by signature and family. Their gameplay purpose is still unknown because the currently decompiled code only reads them.

`include/mario_bros/functions.h` provides semantic C names while retaining the original `sub_` symbols required by assembly callers. Confirmed names cover interrupt shutdown, platform-state reset, fixed-size buffer and tilemap clearing, object position integration, readiness-gated state advance, and the state-7-guarded fall initializer. The two position routines use `a` and `b` suffixes because their X-coordinate helpers differ but their gameplay classes are not yet identified.

Replicated helpers now follow the same rule. Their names state the observable contract, including selector-based callback dispatch, frame-table bit updates, state-controller reset, command 12 forwarding, and event emission followed by sequence advancement. Letter suffixes distinguish parallel implementations whose owning gameplay classes are still in assembly.

Additional selectors copy one of two local table values into `value18` according
to object flag bit 2. Animation clocks advance the frame byte and wrap or toggle
the variant at their proven limits. The later object family now exposes the same
three-frame, one-based variant cycle already established by its earlier sibling.
The `a` through `d` suffixes remain because the
parallel ROM and work-RAM tables do not yet identify the gameplay classes that own
them; the frame limits and zero-based or one-based wrap behavior are now explicit.

The later animation family also has a table-driven clock. While `value18` is
nonzero, it advances `animationFrame` to the state-selected threshold, wraps the
four-value variant, and refreshes `value06` plus the low flag bit from parallel
work-RAM tables. Those table roles are established by access width and consumers;
the owning gameplay class and the broader meaning of `value18` remain unknown.

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

The later mirrored runtime also exposes a linked-fall transition. Unless the object
is already in state 7, it runs the existing setup, installs the established downward
delta, and forwards the linked record's index to the paired position and activation
helpers. The record remains narrowly typed because no other field role is proven.

The pool layer now includes mirrored heap-block release operations that unlink a
block and update the free-list head, plus mirrored link-context dispatchers. Their
names state those allocator and dispatch mechanics; the gameplay owners of the
two runtime families remain unresolved. The primary runtime also exposes its
active-object release sweep: it checks each established activity halfword and
returns only the corresponding active object to the existing pool release path.
Its readiness-gated sibling releases one supplied object through that same path
and, while the associated runtime mode is active, decrements the nonzero byte at
`0x458E`. The byte remains offset-named because its broader role is not yet proven.

Three additional object helpers now share the established `MarioBrosObject`
layout. One decrements the halfword action countdown and invokes its follow-up
when the value reaches zero. Another initializes downward motion while setting
the two proven enable bits and clearing the auxiliary byte at `0x26`. The third
services an effect-state record, invoking its existing update when effect slot
`0x44` is active and then clearing the pending byte at `0x3F`.

The gameplay class owning these records remains unknown. The countdown's
follow-up and the effect identifier are therefore retained under their original
symbols; names describe only the observable state contract. Nearby tile-code and
direction-animation candidates remain in assembly because two natural typed C
forms changed register allocation.

A later compact display consumer now uses the 20-byte descriptor prepared by its
existing sibling helpers. When source byte `0x01` equals 20, it constructs that
descriptor, offsets the established X field by 24, and submits the related display
sequence. The source byte remains offset-named because its wider state meaning is
not yet established.

The same object layer now exposes a 64-tick lifetime helper. It increments the
low byte of `value24` and returns the object to the existing pool once the next
value exceeds 63. The record's gameplay class and the release routine's broader
ownership policy are not yet established, so the name describes only the proven
lifetime behavior. Nearby input, phase, direction, and mode helpers remain in
assembly after natural C forms changed stack or register allocation.

The embedded M4A lifecycle now includes its typed player-stop path. It validates
the standard player identity, marks the player paused, stops each configured
track through `TrackStop`, and restores the identity after the traversal. The
adjacent continue leaf remains in assembly because natural typed forms either
added a frame or replaced the observed return with alignment padding.

The same embedded driver now exposes its canonical player volume-control loop.
It applies the supplied track mask only to existing tracks, stores the M4A
quarter-scale volume adjustment, marks volume state dirty, and preserves the
driver's identity lock around the traversal. Neighboring pitch and pan controls
remain raw where their entry boundaries are anonymous.

Player initialization now uses the canonical `MPlayOpen` contract. It clamps
the supplied track count, clears each track's flags, links the player into the
sound driver's player and update lists, and restores both identity fields. The
relocated update entry remains the observed numeric address until its copied
code boundary is independently detangled.

The embedded driver also exposes its canonical direct-sound pitch conversion.
`MidiKeyToFreq` clamps the MIDI key and fine adjustment, interpolates between
the relocated M4A scale entries with high-word multiplication, then scales the
source wave frequency. The two RAM tables are named only for their proven
element types and access pattern.

The player-control boundary now includes `m4aMPlayAllStop`. It walks the
configured M4A player table and applies the existing typed stop operation to
each player, preserving the driver's per-player identity and track cleanup.
Nearby song-number wrappers remain in assembly because their natural typed
forms changed literal and working-register allocation.

## Next boundary

The currently decompiled slice is detangled. Further gameplay-specific names depend on assembly callers, callback initialization paths, and table contents that are outside the current C boundary. Resume this subsystem when those dependencies are decompiled rather than replacing explicit `a`/`b` variants with guesses.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports every linked C function exact, with zero mismatches.
