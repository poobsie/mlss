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

## Title screen

The title screen now lives beside the other screen processes in `src/screens/title_screen.c`, with its shared interface and layouts in `include/screens/title_screen.h`. The process owns the opening suitcase sequence, title and subtitle animation, press-start prompt, game selection, fade-out transition, scanline background effect, and its Mario Bros score display child.

The seven `TitleScreenStates` values describe the outer lifecycle. `TitleScreenItems` and `TitleScreenItemSuitcaseStates` describe the independently animated pieces within the opening sequence. Sprite array accesses use `TitleScreenSprites`, so an index now identifies the visual it controls instead of forcing readers to reconstruct the resource order.

`title_screen_prepare_press_start` establishes the stable title layout used after skipping the suitcase animation. `title_screen_prepare_game_select` lays out the three choices, selection pointer, suitcase, and suitcase contents, then enables the multiplayer serial interface. `title_screen_scanline_effect_update` prepares the per-line BG2 vertical offsets and starts the HBlank DMA transfer.

The former `OPDR` process is `TitleScreenScoreDisplay`. It converts the stored top score and player score into digit arrays during creation, then submits those digits while the Mario Bros suitcase visual is visible. `OPDR` remains only as a ROM allocation label.

| Previous name | Recovered name | Evidence |
| --- | --- | --- |
| `open_init_8055A00` | `title_screen_create` | Adds and initializes the title process, loads all title resources, creates its score display child, and selects its entry path. |
| `open_update` | `title_screen_update` | The title process definition invokes it once per scheduler update; it owns all seven outer states. |
| `sub_805737C` | `title_screen_destroy` | Removes the score display child, releases title resources, restores display state, and removes the title process. |
| `open_8055E2C` | `title_screen_prepare_press_start` | Reconstructs the visible logo and suitcase arrangement used by the press-start states. |
| `open_8055F74` | `title_screen_prepare_game_select` | Creates the three-choice layout and enables multiplayer serial handling. |
| `sub_8056224` | `title_screen_scanline_effect_update` | Builds a scanline offset table and programs DMA0 to update `BG2VOFS` during HBlank. |
| `MarioBrosScoreVisual` | `TitleScreenScoreDisplay` | Stores six top-score digits and two player-score digits as a child of the title process. |
| `mbsv_init` | `title_screen_score_display_create` | Initializes those digit arrays and installs the score-display process definition. |
| `opdr_update2` | `title_screen_score_display_update` | Emits the score digits into the sprite render list when the selected suitcase visual permits it. |
| `stru_8CDC238` | `gTitleScreenProcessDefinition` | Process descriptor whose update target is the title state machine. |
| `stru_8CDC248` | `gTitleScreenScoreDisplayProcessDefinition` | Process descriptor whose update target renders the score display. |

The three functions still compiled from assembly now use semantic entry-point and file names. Their guarded C reconstructions remain available for continued matching work without exposing address-based names to callers.

## Remaining screen work

The option screens still combine several process lifecycles, graphics-resource loading, widget state, and transitions in large root-level files. The next slice should recover their shared window and menu types before assigning names to individual handlers.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports 1,301 linked C functions checked, 1,301 exact, and zero mismatches.
