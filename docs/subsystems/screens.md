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

## Options screen

The main options process now lives in `src/screens/options.c`; its small dialog-layout helpers are in `src/screens/options_dialogs.c`. Its layout, states, setting bits, and public operations are in `include/screens/options.h`. It owns the three settings shown on the menu, the selection cursor, confirmation-dialog graphics, the animated window mask, and a child render process.

`pendingSettings` is assembled from the current Easy Sleep, rumble, and Auto Sleep values. Left and right input changes those bits locally. `options_screen_save_settings` copies them back to the runtime and persistent option fields, then invokes the save routine. A failed save builds and opens the error dialog before the process eventually returns to the title screen.

`WindowAnimation` describes a centered rectangular window and its opening or closing progress. `window_animation_prepare` writes the window tilemap and initializes that record. `window_animation_update` expands the hardware window from progress 1 through 8, or contracts it from 7 to 0 when `isClosing` is set.

| Previous name | Recovered name | Evidence |
| --- | --- | --- |
| `OPTNProcess` | `OptionsScreen` | Owns the complete options menu lifecycle and is allocated by the title-screen Options selection. |
| `optn_init` | `options_screen_create` | Adds the options process, loads its resources, initializes settings and dialog buffers, and creates its render child. |
| `optn_update` | `options_screen_update` | Implements the eight-state input, confirmation, save-error, and exit state machine. |
| `try_save_options` | `options_screen_save_settings` | Copies the pending setting bits to runtime and persistent storage, then calls the save operation and returns its result. |
| `sub_8052B54` | `options_screen_build_option_labels` | Renders the three option labels into the label tile buffer and optionally copies them to VRAM. |
| `sub_8052EFC` | `options_screen_build_save_error_dialog` | Clears the dialog buffers, renders the save-error message, and constructs its tilemap. |
| `sub_805420C` | `options_screen_prepare_save_error_dialog` | Reads the save-error dimensions and initializes the centered window animation. |
| `option_screen_set_ok_button` | `options_screen_prepare_confirmation_dialog` | Initializes a confirmation window and records the cursor position for its OK button. |
| `WindowAttr` | `WindowAnimation` | Its dimensions and center drive the hardware window bounds; its progress and closing flag drive the open/close sequence. |
| `stru_8CDC1F8` | `gOptionsScreenProcessDefinition` | Descriptor installed on the options process. |
| `stru_8CDC208` | `gOptionsScreenRenderProcessDefinition` | Descriptor installed on the options screen's render child. |

The one-bit `entryArgument` and three-bit `unknownFlags` fields retain deliberately narrow names. The only recovered caller passes zero, and the current C never reads either field, so a stronger semantic name would be fiction. The text context type also remains structurally incomplete even though its ownership by the options screen is established.

## Backup-clear screen

The startup `bclr` process is the backup-clear confirmation flow. The startup dispatcher selects it for saved-state marker `0x0307` instead of launching the company intro. It renders a two-position confirmation, invokes the backup-clear routine for the affirmative path, writes the result, handles a write error, closes its window, and then creates the company intro.

Its 76-byte layout is now `BackupClearScreen` in `include/screens/backup_clear.h`. The process shares `WindowAnimation` with the options screen but has its own message tiles, dialog tilemaps, text context, selection cursor, write progress, and render child. The six outer states are named in `BackupClearScreenState` from their observed transitions. The mixed recovered assembly is grouped under `asm/screens/options_and_backup.s` until its individual functions are converted to C.

| Previous name | Recovered name | Evidence |
| --- | --- | --- |
| `bclr_init` | `backup_clear_screen_create` | Creates the 76-byte startup process, its render child, two-choice cursor, text resources, and initial dialog. |
| `bclr_update_8053778` | `backup_clear_screen_update` | Its six states run confirmation, backup clearing and writing, error handling, and exit to the company intro. |
| `sub_80536E8` | `backup_clear_screen_destroy` | Removes the render child, frees every owned buffer and text context, restores display state, and removes the process. |
| `sub_8054164` | `backup_clear_render_process_update` | Services and submits the sprite render list; descriptor `0x08CDC1E8` invokes it. |
| `sub_80541B0` | `backup_clear_screen_prepare_dialog` | Centers a requested dialog size and initializes the process's shared window animation record. |
| `0x08CDC1D8` | `gBackupClearScreenProcessDefinition` | Its update pointer is `backup_clear_screen_update`. |
| `0x08CDC1E8` | `gBackupClearRenderProcessDefinition` | Its update pointer is `backup_clear_render_process_update`. |

Only bit zero of the byte after the process header is understood: it selects the affirmative or negative cursor position. The remaining bits stay `unknownFlags`. `writeProgress` is passed to and replaced by the backup-write operation, but the format of its intermediate values is not yet recovered.

## Mario Bros save-error screen

The former option-screen tail is a 64-byte error screen used only on the Mario Bros return path. Selecting Mario Bros from the title sets the shared handoff state to 1. When the embedded game returns with state 2, `mario_bros_sync_records` compares its records with the saved values and attempts to persist any improvements. A failed synchronization creates this error screen; a successful one returns directly to title-screen entry path 2.

`MarioBrosSaveErrorScreen` owns the rendered message, its tilemap and text context, and one `WindowAnimation`. `mario_bros_save_error_screen_update` waits for the centered message window to finish opening, holds it for up to 240 frames or until A, B, or Start is pressed, closes it, frees the owned buffers, and recreates the title screen. Its source is now `src/screens/mario_bros_save_error.c`. The backup-clear helpers that previously followed it are isolated in `src/screens/backup_clear_helpers.c`.

| Previous name | Recovered name | Evidence |
| --- | --- | --- |
| `sub_8053CB4` | `mario_bros_save_error_screen_create` | The Mario Bros return dispatcher creates it only when record synchronization reports failure; it builds one centered message screen. |
| `sub_8053FC4` | `mario_bros_save_error_screen_update` | Holds the message for 240 frames or input, animates it closed, destroys the process, and returns to the title screen. |
| `sub_805410C` | `mario_bros_save_error_screen_destroy` | Frees the exact five allocations owned by the 64-byte message process and removes it. |
| `sub_80540B0` | `mario_bros_save_error_screen_prepare_dialog` | Reads this message's dimensions and initializes its centered window animation. |
| `sub_8057568` | `mario_bros_sync_records` | Compares the returned Mario Bros record values with persistent values, updates improvements, and invokes the save operation. |
| `0x08CDC1C8` | `gMarioBrosSaveErrorScreenProcessDefinition` | Its update pointer is `mario_bros_save_error_screen_update`. |

The exact record semantics are not yet proven, so the synchronization function deliberately uses `records` rather than `scores`. Its field-level data model should be recovered with the surrounding Mario Bros subsystem.

## Remaining screen work

All currently decompiled screen C now has a subsystem path, canonical public header, typed process ownership, and evidence-backed lifecycle names. Some adjacent assembly remains in `asm/screens/options_and_backup.s`; it should be split further as those functions are converted to C.

Six late screen helpers now live in `src/screens/runtime_helpers.c`. Two launch the menu/save and shop processes; their ROM allocation labels are literally `MENU`, `SAVE`, and `SHOP`, and their distinct allocation sizes and constructors are preserved. Four configure a layer object through the shared hardware-backed layer routine, with three setting their owner's proven completion byte afterward. One of those also fades music over sixteen steps. The sparse owner layouts remain separate because matching field offsets alone does not prove a common screen class.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports every linked C function exact, with zero mismatches.
## Scrollable view process

`ScrollableViewProcess` owns a content area, a `240 x 160` viewport position, hardware scroll output, and four edge-arrow sprites. Its update routine writes the scroll registers and hides each arrow when movement in that direction has reached the corresponding content boundary. Its clamp routine constrains the viewport and forwards the position to the content object.

The recovered lifecycle methods initialize the base process and release the owned content, child process, and auxiliary object. A separate update passes game-state value `0x880` through two still-unidentified transforms, so its name deliberately stops at `scrollable_view_update_persistent_value`.

`ScrollableViewContent` now exposes its process base, six owned buffers, and cleanup-active byte at `0x584`. Destruction runs the optional content cleanup, resets the VRAM-backed workspace, frees every present buffer, and removes the process. Buffer roles retain offsets until their allocation and rendering consumers are recovered.
