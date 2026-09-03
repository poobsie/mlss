#ifndef GUARD_SCREENS_MARIO_BROS_SAVE_ERROR_H
#define GUARD_SCREENS_MARIO_BROS_SAVE_ERROR_H

#include "process/types.h"
#include "screens/options.h"

struct struc_15;

enum MarioBrosSaveErrorScreenState {
    MARIO_BROS_SAVE_ERROR_STATE_WAIT,
    MARIO_BROS_SAVE_ERROR_STATE_CLOSE,
};

struct MarioBrosSaveErrorScreen {
    struct Process process;
    u8 phaseTimer;
    u8 padding1[3];
    u8* graphicsWorkAllocation;
    u8* messageTiles;
    u16* dialogTilemap;
    int* textEngineCode;
    struct struc_15* textContext;
    int* windowAnimationTilemap;
    struct WindowAnimation dialogWindow;
    u8 padding2[2];
};

extern struct ProcessDefinition gMarioBrosSaveErrorScreenProcessDefinition
    __asm__("stru_8CDC1C8");

struct MarioBrosSaveErrorScreen* mario_bros_save_error_screen_create(
    struct MarioBrosSaveErrorScreen* errorScreen,
    u8 priority,
    char* label);
void mario_bros_save_error_screen_update(struct MarioBrosSaveErrorScreen* errorScreen);
void mario_bros_save_error_screen_destroy(
    struct MarioBrosSaveErrorScreen* errorScreen,
    u32 flags);
void mario_bros_save_error_screen_prepare_dialog(
    struct MarioBrosSaveErrorScreen* errorScreen);

#endif
