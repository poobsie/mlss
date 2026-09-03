# Audio subsystem

## Sound-effect control slice

The first recovered audio slice covers three entry points at `0x0801959C` through `0x080195F7`. These functions were previously stored in `runtime_helpers.c`, even though their call sites and command encoding identify them as sound-effect controls.

| Address | Previous name | Recovered name | Evidence |
| --- | --- | --- | --- |
| `0x0801959C` | `stop_all_sfx_801959C` | `sound_effects_stop_all` | It emits sound command `0x7000`, which has no sound identifier, and callers use it as a global stop. |
| `0x080195A8` | `stop_sfx_80195A8` | `sound_effect_stop` | Callers pass the same identifiers used to start sounds; the function emits command `0x6000 | soundId`. |
| `0x080195B4` | `play_sfx_80195B4` | `sound_effect_play` | Callers pass sound identifiers; the function emits command `0x5000 | soundId`, then optionally sets volume. |

The public interface is `include/audio/sound_effects.h`, and the implementation is `src/audio/sound_effects.c`. All C callers use that header. The former unprototyped stop function now explicitly accepts `soundId`; the old code only worked because the argument happened to remain in register `r0` across the wrapper call.

`SOUND_VOLUME_UNCHANGED` names the common `-1` argument. If no volume has been established yet, the play wrapper substitutes `SOUND_VOLUME_MAX`. The field at `gGameState + 0x890` is therefore named `volume` inside the narrow audio overlay. The ownership and final shape of the larger game-state structure remain unresolved.

## Verification

The rebuilt 112-byte range from `0x08019588` through `0x080195F7`, including the preceding helper and required alignment, matches the reference ROM byte for byte. Its SHA-1 is `aaa68c7b1729cdc6b6dbe1a8c23e237afcaf8d8d`.

The full ROM also passes its SHA-1 comparison. The exact-function verifier reports 1,301 linked C functions checked, 1,301 exact, and zero mismatches.
