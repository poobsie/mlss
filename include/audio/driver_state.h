#ifndef GUARD_AUDIO_DRIVER_STATE_H
#define GUARD_AUDIO_DRIVER_STATE_H

#include "global.h"

struct AudioDriverState {
    u8 unknown000[0x494];
    u8 playerFlags[3];
    u8 unknown497[0x0D];
    s32 playerTempo[3];
};

void audio_driver_set_player_tempo(s32 player, s32 tempo);
void audio_driver_mark_player_active(u32 player);
void sub_819B0F8(s32 player, s32 tempo);
void sub_819B19C(u32 player);

#endif
