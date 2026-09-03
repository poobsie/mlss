#ifndef GUARD_SAVE_PROFILE_H
#define GUARD_SAVE_PROFILE_H

#include "global.h"

struct SaveState {
    char name[8];
    u8 value8_0 : 3;
    u8 easySleepEnabled : 1;
    u8 rumbleEnabled : 1;
    u8 autoSleepEnabled : 1;
    u8 unknown8_6 : 1;
};

struct TitleSaveSummary {
    u32 value0;
    u8 value4;
    u8 value5;
    u8 value6;
    u8 titleState : 2;
    u8 easySleepEnabled : 1;
    u8 autoSleepEnabled : 1;
    u8 value7_4 : 3;
    u8 gameBoyPlayerDetected : 1;
};

#define save_get_title_summary sub_81251DC

struct TitleSaveSummary* save_get_title_summary(void);

extern struct SaveState* gSaveState __asm__("dword_3000FFC");
extern struct TitleSaveSummary gTitleSaveSummary __asm__("stru_203FFF8");

#endif
