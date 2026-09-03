#include "global.h"
#include "common.h"
#include "screens/options.h"

void options_screen_prepare_save_error_dialog(struct OptionsScreen* optionsScreen) {
    u8* dimensions = (u8*)0x083A2918;
    u8 width = (u32)(dimensions[0] << 24) >> 24;
    u8 height = (u32)(dimensions[2] << 24) >> 24;
    u8 x = 15 - width / 2;
    u8 y = 10 - height / 2;

    window_animation_prepare(
        &optionsScreen->dialogWindow,
        optionsScreen->windowAnimationTilemap,
        x,
        y,
        width,
        height,
        0xC800);
}

void options_screen_prepare_confirmation_dialog(
    struct OptionsScreen* optionsScreen, int width, int height) {
    u8 x = 15 - width / 2;
    u8 y = 10 - height / 2;

    window_animation_prepare(
        &optionsScreen->dialogWindow,
        optionsScreen->windowAnimationTilemap,
        x,
        y,
        width,
        height,
        0xC800);
    optionsScreen->okButtonX = x * 8 + width * 4 - 16;
    optionsScreen->okButtonY = (y + height) * 8 - 22;
}
