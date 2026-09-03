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

## Next boundary

Audit the remaining address-named Mario Bros functions for defensible public names, then defer any identities that require assembly callers or initialization paths not yet decompiled.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports 1,301 linked C functions checked, 1,301 exact, and zero mismatches.
