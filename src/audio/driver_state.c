#include "audio/driver_state.h"

#define SEC(name) __attribute__((section(".text.audio_driver_state." #name)))

#define AUDIO_DRIVER_STATE (*(struct AudioDriverState**)0x03007FF0)

SEC(sub_819B0F8) void sub_819B0F8(s32 player, s32 tempo)
{
    struct AudioDriverState* driver = AUDIO_DRIVER_STATE;
    s32 offset;

    player <<= 2;
    offset = 0x4A4;
    driver = (struct AudioDriverState*)((u8*)driver + offset);
    driver = (struct AudioDriverState*)((u8*)driver + player);
    *(s32*)driver = tempo;
}

SEC(sub_819B19C) void sub_819B19C(u32 player)
{
    struct AudioDriverState* driver = AUDIO_DRIVER_STATE;
    u32 offset = 0x494;
    u8* entry = (u8*)driver + offset + player;
    u32 value = *entry;
    u32 bits = 1;

    bits |= value;
    *entry = bits;
}

void audio_driver_set_player_tempo(s32 player, s32 tempo)
    __attribute__((alias("sub_819B0F8")));
void audio_driver_mark_player_active(u32 player)
    __attribute__((alias("sub_819B19C")));
