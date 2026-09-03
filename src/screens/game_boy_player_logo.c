#include "global.h"
#include "common.h"
#include "process/process.h"
#include "screens/game_boy_player_logo.h"

struct GameBoyPlayerLogo* game_boy_player_logo_create(
    struct GameBoyPlayerLogo* logo,
    u8 priority,
    char* label,
    void (*finishCallback)(void)) {
    process_add(&logo->process, priority, label);
    logo->process.definition = &gGameBoyPlayerLogoProcessDefinition;
    gGameState.gameBoyPlayerLogoFinished = FALSE;
    logo->phaseTimer = 16;
    logo->finishCallback = finishCallback;
    logo->currentDpad = 0;
    logo->previousDpad = 0;
    logo->lastChordFrame = 0;
    logo->previousChordFrame = 0;
    CpuFastSet(dword_81DD7F4, (void*)0x2000080, 128);
    sub_8018218(dword_81DD9F4, (void*)BG_CHAR_ADDR(2), sizeof(dword_81DD9F4), 32, 0);
    sub_8018218(dword_81E19F4, (void*)BG_SCREEN_ADDR(0), sizeof(dword_81E19F4), 32, 0);
    gGameState.field_884 |= 0xFFFF;
    gGameState.field_2 = -1;
    sub_8017E34();
    BUFFER_REG_BLDCNT = BLDCNT_TGT1_ALL | BLDCNT_EFFECT_LIGHTEN;
    BUFFER_REG_BLDY = 16;
    BUFFER_REG_BG0CNT = BGCNT_CHARBASE(2) | BGCNT_256COLOR;
    BUFFER_REG_DISPCNT = DISPCNT_OBJ_1D_MAP | DISPCNT_BG0_ON;
    return logo;
}

void game_boy_player_logo_update(struct GameBoyPlayerLogo* logo) {
    u16 newDpadPresses;

    switch (logo->process.state) {
        case GAME_BOY_PLAYER_LOGO_FADE_IN:
            logo->phaseTimer--;
            BUFFER_REG_BLDY = logo->phaseTimer;
            if (logo->phaseTimer == 0) {
                logo->phaseTimer = 50;
                logo->process.state++;
            }
            break;

        case GAME_BOY_PLAYER_LOGO_HOLD:
            logo->phaseTimer--;
            if (logo->phaseTimer == 0) {
                logo->phaseTimer = 16;
                logo->process.state++;
            }
            break;

        case GAME_BOY_PLAYER_LOGO_FADE_OUT:
            logo->phaseTimer--;
            BUFFER_REG_BLDY = 16 - logo->phaseTimer;
            if (logo->phaseTimer == 0) {
                if (logo != NULL) {
                    logo->process.definition = &gGameBoyPlayerLogoProcessDefinition;
                    gGameState.gameBoyPlayerLogoFinished = TRUE;
                    BUFFER_REG_DISPCNT = 0;
                    BUFFER_REG_BLDCNT = 0;
                    process_remove(&logo->process,
                                   PROCESS_REMOVE_FLAGS_FREE | PROCESS_REMOVE_FLAGS_UNKNOWN);
                }

                if (logo->finishCallback != NULL) {
                    logo->finishCallback();
                }

                return;
            }
    }

    logo->previousDpad = logo->currentDpad;
    logo->currentDpad = DPAD_ANY & ~REG_KEYINPUT;
    newDpadPresses = logo->currentDpad & ~logo->previousDpad & DPAD_ANY;

    if (newDpadPresses == DPAD_ANY) {
        logo->previousChordFrame = logo->lastChordFrame;
        logo->lastChordFrame = logo->process.frames;
        if (logo->previousChordFrame != 0
            && logo->lastChordFrame - logo->previousChordFrame < 4) {
            gGameState.gameBoyPlayerDetected = TRUE;
            stru_3000D18.field_0_1 = 0;
        }
    }
}
