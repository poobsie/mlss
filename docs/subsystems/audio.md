# Audio subsystem

## Sound-effect control slice

The first recovered audio slice covers three entry points at `0x0801959C` through `0x080195F7`. These functions were previously stored in `runtime_helpers.c`, even though their call sites and command encoding identify them as sound-effect controls.

| Address | Previous name | Recovered name | Evidence |
| --- | --- | --- | --- |
| `0x08019588` | `sub_8019588` | `sound_effect_is_playing` | Callers pass a sound identifier and stop that same sound only when this function returns true. The driver result is normalized to a boolean. |
| `0x0801959C` | `stop_all_sfx_801959C` | `sound_effects_stop_all` | It emits sound command `0x7000`, which has no sound identifier, and callers use it as a global stop. |
| `0x080195A8` | `stop_sfx_80195A8` | `sound_effect_stop` | Callers pass the same identifiers used to start sounds; the function emits command `0x6000 | soundId`. |
| `0x080195B4` | `play_sfx_80195B4` | `sound_effect_play` | Callers pass sound identifiers; the function emits command `0x5000 | soundId`, then optionally sets volume. |

The public interface is `include/audio/sound_effects.h`, and the implementation is `src/audio/sound_effects.c`. All C callers use that header. The former unprototyped stop function now explicitly accepts `soundId`; the old code only worked because the argument happened to remain in register `r0` across the wrapper call.

`SOUND_VOLUME_UNCHANGED` names the common `-1` argument. If no volume has been established yet, the play wrapper substitutes `SOUND_VOLUME_MAX`. The field at `gGameState + 0x890` is therefore named `volume` inside the narrow audio overlay. The ownership and final shape of the larger game-state structure remain unresolved.

## Music players

The game maintains two indexed music players. Their public controls are declared in `include/audio/music.h`; the recovered state-query and lifecycle wrappers are implemented in `src/audio/music.c`.

| Address | Previous name | Recovered name | Evidence |
| --- | --- | --- | --- |
| `0x08019308` | `sub_8019308` | `music_play` | Stores the supplied song identifier for the selected player and emits the driver play command. A zero identifier stops the player. |
| `0x080193B4` | `sub_80193B4` | `music_set_volume` | Maintains current and target 8.8 fixed-point volume values, optionally interpolating over the supplied duration. Driver command `0x9` carries the resulting value. |
| `0x08019460` | `sub_8019460` | `music_set_tempo` | Maintains a separate interpolated parameter initialized to 75 and sends it through driver command `0x8`, the music tempo control. |
| `0x080195F8` | `sub_80195F8` | `music_is_playing` | Extracts the selected player's active bit from the driver status mask. |
| `0x08019610` | `sub_8019610` | `music_get_song_id` | Returns the song identifier stored by `music_play`. |
| `0x08019628` | `sub_8019628` | `music_stop` | Emits driver command `0x1` for the selected player and clears its current volume. |
| `0x08019650` | `sub_8019650` | `music_resume` | Emits driver command `0x2`, restores the saved volume when requested, and optionally fades to the selected volume. |

The three controls still implemented in assembly now have stable public names because their arguments, state updates, driver commands, and callers agree. Their lower-level command encoder remains address-named pending reconstruction of the driver protocol.

## Driver servicing

The two recovered driver callbacks now live in `src/audio/driver.c`. `audio_update` services the enabled driver from the main loop. `audio_timer0_interrupt` is installed in interrupt slot 3, the GBA Timer 0 interrupt, and services the stream mixer only while audio is enabled.

`AudioDriverState` exposes the per-player flags at `0x494` and tempo words at `0x4A4`. The recovered setter is called with `0x4B` while a player is initialized, matching the music layer's default tempo of 75; the paired flag helper marks a selected player active with bit `0x01`.

Two scene-facing wrappers have also been separated from early address buckets. `audio_play_sound_50` starts sound ID `0x50` at the existing volume. `audio_stop_scene_sound_set` issues the original fixed stop sequence for IDs `0x157`, `0x87`, `0xDB`, and `0xDA`; the duplicate stop for `0xDA` is retained because exact reconstruction does not justify deleting it. The sound IDs remain numeric until call-site or asset-table evidence establishes their actual cues.

The six low-level command encoders behind these APIs now live in `src/audio/commands.c`. Their high nybbles are proven by the named callers: `0x1000` stops a music player, `0x2000` resumes it, `0x5000` plays a sound, `0x6000` stops a sound, and `0x7000` stops all sounds. Player identifiers occupy the next byte; sound identifiers occupy the low 12 bits.

## Verification

The rebuilt 112-byte range from `0x08019588` through `0x080195F7`, including the preceding helper and required alignment, matches the reference ROM byte for byte. Its SHA-1 is `aaa68c7b1729cdc6b6dbe1a8c23e237afcaf8d8d`.

The full ROM passes its SHA-1 comparison. The exact-function verifier reports 1,301 linked C functions checked, 1,301 exact, and zero mismatches.
