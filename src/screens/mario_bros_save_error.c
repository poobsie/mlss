#include "global.h"
#include "common.h"
#include "process/process.h"
#include "screens/mario_bros_save_error.h"
#include "screens/title_screen.h"

void mario_bros_save_error_screen_update(struct MarioBrosSaveErrorScreen* errorScreen) {

    switch (errorScreen->process.state) {
    case MARIO_BROS_SAVE_ERROR_STATE_WAIT:
        if (errorScreen->dialogWindow.progress > 0) {
            window_animation_update(&errorScreen->dialogWindow);
        } else if (--errorScreen->phaseTimer == 0 || (gGameState.field_2A & 0xB)) {
            *(u8*)(*(u32*)0x0839EC80 + 1) |= 0x20;
            errorScreen->dialogWindow.isClosing = 1;
            errorScreen->dialogWindow.progress = 7;
            errorScreen->process.state = MARIO_BROS_SAVE_ERROR_STATE_CLOSE;
        }
        break;
    case MARIO_BROS_SAVE_ERROR_STATE_CLOSE:
        window_animation_update(&errorScreen->dialogWindow);
        {
        s8 value = errorScreen->dialogWindow.progress;
        if (value == 0) {
            if (errorScreen != 0) {
                errorScreen->process.definition = &gMarioBrosSaveErrorScreenProcessDefinition;
                if (errorScreen->windowAnimationTilemap != 0)
                    free_heap_8018D9C(errorScreen->windowAnimationTilemap);
                if (errorScreen->graphicsWorkAllocation != 0)
                    free_heap_8018D9C(errorScreen->graphicsWorkAllocation);
                if (errorScreen->dialogTilemap != 0)
                    free_heap_8018D9C(errorScreen->dialogTilemap);
                if (errorScreen->textEngineCode != 0)
                    free_heap_8018D9C(errorScreen->textEngineCode);
                free_heap_8018DA8(errorScreen->textContext);
                *(u16*)0x02000000 = value;
                *(u16*)0x02000050 = value;
                process_remove(&errorScreen->process, 3);
            }
            title_screen_create(alloc_Zero(0xE4, 0, (char*)0x081E2714, 0), 8,
                              (char*)0x081E2714, 2);
        }
        }
        break;
    }
}

void mario_bros_save_error_screen_prepare_dialog(struct MarioBrosSaveErrorScreen* errorScreen) {
    u8* dimensions = (u8*)0x083A2978;
    u8 width = (u32)(dimensions[0] << 24) >> 24;
    u8 height = (u32)(dimensions[2] << 24) >> 24;
    u8 x = 15 - width / 2;
    u8 y = 10 - height / 2;

    window_animation_prepare(
        &errorScreen->dialogWindow,
        errorScreen->windowAnimationTilemap,
        x,
        y,
        width,
        height,
        0xE000);
    *(u8*)(*(u32*)0x0839EC80 + 0x4A) |= 0x10;
}

void mario_bros_save_error_screen_destroy(struct MarioBrosSaveErrorScreen* errorScreen, u32 flags) {
    errorScreen->process.definition = &gMarioBrosSaveErrorScreenProcessDefinition;
    if (errorScreen->windowAnimationTilemap != 0)
        free_heap_8018D9C(errorScreen->windowAnimationTilemap);
    if (errorScreen->graphicsWorkAllocation != 0)
        free_heap_8018D9C(errorScreen->graphicsWorkAllocation);
    if (errorScreen->dialogTilemap != 0)
        free_heap_8018D9C(errorScreen->dialogTilemap);
    if (errorScreen->textEngineCode != 0)
        free_heap_8018D9C(errorScreen->textEngineCode);
    free_heap_8018DA8(errorScreen->textContext);
    *(u16*)0x02000000 = 0;
    *(u16*)0x02000050 = 0;
    process_remove(&errorScreen->process, flags);
}
