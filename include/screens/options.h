#ifndef GUARD_SCREENS_OPTIONS_H
#define GUARD_SCREENS_OPTIONS_H

#include "process/types.h"

struct Sprite;
struct struc_15;

#define OPTION_SETTINGS_SHIFT_EASY_SLEEP 0
#define OPTION_SETTINGS_SHIFT_RUMBLE     1
#define OPTION_SETTINGS_SHIFT_AUTO_SLEEP 2

#define OPTION_SETTINGS_EASY_SLEEP (1 << OPTION_SETTINGS_SHIFT_EASY_SLEEP)
#define OPTION_SETTINGS_RUMBLE     (1 << OPTION_SETTINGS_SHIFT_RUMBLE)
#define OPTION_SETTINGS_AUTO_SLEEP (1 << OPTION_SETTINGS_SHIFT_AUTO_SLEEP)

enum OptionScreenStates {
    OPTIONS_SCREEN_STATE_FADE_IN = 0,
    OPTIONS_SCREEN_STATE_SELECT_OPTION,
    OPTIONS_SCREEN_STATE_EASY_SLEEP_CONFIRMATION,
    OPTIONS_SCREEN_STATE_RUMBLE_CONFIRMATION,
    OPTIONS_SCREEN_STATE_AUTO_SLEEP_CONFIRMATION,
    OPTIONS_SCREEN_STATE_SAVE_ERROR,
    OPTIONS_SCREEN_STATE_SAVE_ERROR_CONFIRMATION,
    OPTIONS_SCREEN_STATE_LEAVE,
};

struct WindowAnimation {
    bool8 isClosing : 1;
    s8 progress;
    u8 centerX;
    u8 centerY;
    u8 width;
    u8 height;
};

struct OptionsScreen {
    struct Process process;
    s8 fadeTimer;
    s8 inputCooldown;
    struct Process* renderProcess;
    u8* graphicsWorkAllocation;
    u8* optionLabelTiles;
    u8* confirmationDialogTiles;
    u16* confirmationDialogTilemaps;
    int* textEngineCode;
    struct struc_15* textContext;
    s8 entryArgument : 1;
    s8 unknownFlags : 3;
    u8 pendingSettings : 3;
    s8 selectedOption;
    int* windowAnimationTilemap;
    u8 okButtonX;
    u8 okButtonY;
    struct WindowAnimation dialogWindow;
    struct Sprite* cursor;
};

extern struct ProcessDefinition gOptionsScreenProcessDefinition __asm__("stru_8CDC1F8");
extern struct ProcessDefinition gOptionsScreenRenderProcessDefinition __asm__("stru_8CDC208");

void window_animation_prepare(
    struct WindowAnimation* animation,
    int* tilemap,
    u8 centerX,
    u8 centerY,
    u8 width,
    u8 height,
    int baseTile);
void window_animation_update(struct WindowAnimation* animation);
struct OptionsScreen* options_screen_create(
    struct OptionsScreen* optionsScreen,
    u8 priority,
    char* label,
    int entryArgument);
void options_screen_update(struct OptionsScreen* optionsScreen);
int options_screen_save_settings(struct OptionsScreen* optionsScreen);
void options_screen_build_option_labels(struct OptionsScreen* optionsScreen, int copyToVram);
void options_screen_build_save_error_dialog(struct OptionsScreen* optionsScreen);
void options_screen_prepare_save_error_dialog(struct OptionsScreen* optionsScreen);
void options_screen_prepare_confirmation_dialog(
    struct OptionsScreen* optionsScreen,
    int width,
    int height);

#endif
