#include "common.h"
#include "runtime/functions.h"

void nullsub_17(void) __attribute__((section(".text.nullsub_17")));
void nullsub_17(void) {
}
__attribute__((section(".text.nullsub_17")))
const u16 nullsub_17_padding = 0;

void game_state_set_play_time(u32 playTime)
    __attribute__((section(".text.sub_8018A4C")));
void game_state_set_play_time(u32 playTime) {
    u8* flags;

    gGameState.playTime = playTime;
    flags = (u8*)&gGameState + 0x889;
    *flags |= 1;
}
