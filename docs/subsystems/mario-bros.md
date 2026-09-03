# Mario Bros minigame

## Command readers

Two command-reader families near `0x08F6F26C` and `0x08F95DEC` use the same 68-byte `MarioBrosCommandContext`. Each recovered handler copies one byte from `cursor`, advances the cursor, and stores the byte at one of offsets `0x1E`, `0x1F`, `0x24`, `0x26`, `0x27`, or `0x2C` through `0x2F`.

The shared layout lives in `include/mario_bros/command_context.h`; the primary and secondary reader objects live under `src/mario_bros`. Field names remain offset-based because current C does not show how the command dispatcher or later consumers interpret those bytes. Both families also contain a no-op command handler.

## Next boundary

Unify the overlapping `MbObject`, `MbBitObject`, `MbLateObject`, and `Mb604Object` layouts from their table-selection, animation-frame, and movement users. Preserve separate overlays where offsets have different proven roles.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports 1,301 linked C functions checked, 1,301 exact, and zero mismatches.
