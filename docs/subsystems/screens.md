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

## Company intro

The process previously abbreviated as `COMP` is the company intro shown before the title screen. `company_intro_create` loads the two background layers, creates Mario, Luigi, and AlphaDream logo sprites, and attaches a child render process. `company_intro_update` runs the complete sequence: the brothers fall, the impact shakes the background, the brothers settle and fade out, the AlphaDream logo fades in and holds, then the screen fades into the title process. A, B, or Start skips the logo hold.

The motion fields are signed 8.8 fixed-point values. `backgroundOffsetY`, `marioX`, `marioY`, `luigiX`, and `luigiY` are divided by 256 when written to hardware or sprite coordinates. `verticalVelocity` and `gravity` use the same scale.

The shared child process installed from the `OPDR` label is now exposed mechanically as `screen_render_process_create` and `screen_render_process_update`. Its update services the sprite system and submits the prepared render range. The original abbreviation is retained only as the allocation label because allocation labels are ROM data, not source-level API names.

| Previous name | Recovered name | Evidence |
| --- | --- | --- |
| `COMPProcess` | `CompanyIntro` | Owns the complete Mario, Luigi, and AlphaDream pre-title sequence. |
| `comp_init` | `company_intro_create` | Initializes that process, its resources, sprites, motion, and render child. |
| `comp_update` | `company_intro_update` | Its seven states advance the company intro and create the title screen on completion. |
| `sub_8057458` | `company_intro_destroy` | Restores the company-intro definition, removes its render child, and removes the intro process. |
| `brightness` | `phaseTimer` | Used as blend intensity during fades and as the hold and shake countdown. |
| `flags` | `brothersInMotion` | Gates the brothers' post-impact horizontal and vertical motion until they land. |
| `verticalOffset` | `backgroundOffsetY` | Written to `BG0VOFS` after conversion from 8.8 fixed point. |
| `acceleration` | `gravity` | Added to vertical velocity during both falling phases. |

## Remaining screen work

The title and option screens still combine process lifecycle, graphics-resource loading, widget state, and transitions in large root-level files. They remain active work and should be split in bounded slices rather than moved wholesale.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports 1,301 linked C functions checked, 1,301 exact, and zero mismatches.
