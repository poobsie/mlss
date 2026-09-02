#include "global.h"
#include "common.h"

void nullsub_17(void) {
}

void sub_8018A4C(u32 value) {
    u8* field;

    gGameState.playTime = value;
    field = (u8*)&gGameState + 0x889;
    *field = *field | 1;
}
