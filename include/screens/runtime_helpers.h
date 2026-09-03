#ifndef GUARD_SCREENS_RUNTIME_HELPERS_H
#define GUARD_SCREENS_RUNTIME_HELPERS_H

#include "global.h"

#define screen_configure_layer20_default_and_mark_156 sub_81219EC
#define screen_launch_menu_or_save sub_8122BA0
#define screen_configure_layer15c_and_fade_music sub_8127ADC
#define screen_configure_layer20_and_mark_69 sub_812A8AC
#define screen_configure_layer20_default sub_812F528
#define screen_launch_shop sub_812F5A4

struct ScreenLayerOwner20;
struct ScreenLayerOwner15C;

void screen_configure_layer20_default_and_mark_156(
    struct ScreenLayerOwner20* owner);
void screen_launch_menu_or_save(s32 menuArgument, s32 useSaveScreen);
void screen_configure_layer15c_and_fade_music(
    struct ScreenLayerOwner15C* owner, u16 value);
void screen_configure_layer20_and_mark_69(
    struct ScreenLayerOwner20* owner, u16 value);
void screen_configure_layer20_default(struct ScreenLayerOwner20* owner);
void screen_launch_shop(s32 firstMode, s32 secondMode);

#endif
