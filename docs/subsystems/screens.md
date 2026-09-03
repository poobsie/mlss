# Screen processes

## Game Boy Player logo

The startup logo is a self-contained process in `src/screens/game_boy_player_logo.c`, with its state and interface in `include/screens/game_boy_player_logo.h`.

`game_boy_player_logo_create` installs the process definition, loads its palette, tiles, and tilemap, configures a lightening blend, and initializes a three-phase sequence. `game_boy_player_logo_update` fades the logo in over 16 frames, holds it for 50 frames, and fades it out over 16 frames before removing the process and invoking its completion callback.

The process also records simultaneous new presses of all four D-pad directions. If that chord occurs twice less than four process frames apart, it sets `gameBoyPlayerDetected`. The option screen uses that flag to expose its rumble setting and to select the corresponding graphics. The title screen also selects a different resource set from the same flag.

| Previous name | Recovered name | Evidence |
| --- | --- | --- |
| `gbpl_init` | `game_boy_player_logo_create` | Allocates all logo process state, installs its definition, and returns the initialized process. |
| `gbpl_update` | `game_boy_player_logo_update` | The process definition points here; it advances the fade and hold states once per scheduler update. |
| `brightness` | `phaseTimer` | It is a blend level during fades and a 50-frame countdown during the hold state. |
| `frames` | `lastChordFrame` | Updated only when the all-directions chord is observed and compared with the prior observation. |
| `field_888_1` | `gameBoyPlayerDetected` | Set by the logo's detection sequence and gates the rumble option and alternate screen resources. |
| `field_88A_3` | `gameBoyPlayerLogoFinished` | Cleared when the logo process is created and set immediately before it is removed. |

The field cleared in `stru_3000D18` after successful detection remains unnamed. Its broader owner and effect are not established by this process.

## Remaining screen work

The title and option screens still combine process lifecycle, graphics-resource loading, widget state, and transitions in large root-level files. They remain active work and should be split in bounded slices rather than moved wholesale.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports 1,301 linked C functions checked, 1,301 exact, and zero mismatches.
