#ifndef GUARD_AUDIO_DRIVER_STATE_H
#define GUARD_AUDIO_DRIVER_STATE_H

#include "global.h"

struct AudioDriverVoice {
    u16 flags;
    u8 unknown02[0x10];
    u8 voiceIndex;
    u8 playerIndex;
    u8 unknown14[0x0C];
};

struct AudioDriverState {
    struct AudioDriverVoice voices[3][12];
    u16 commandQueue[8];
    s16 commandReadIndex;
    s16 commandWriteIndex;
    u8 playerFlags[3];
    u8 unknown497;
    u16 playerSoundIds[3];
    u8 unknown49E[6];
    s32 playerTempo[3];
    u8 unknown4B0[0x48];
    u8 unknown4F8;
};

void audio_driver_set_player_tempo(s32 player, s32 tempo);
void audio_driver_mark_player_active(u32 player);
void sub_819B0F8(s32 player, s32 tempo);
void sub_819B19C(u32 player);
u32 sub_819B418(u16 command);
void sub_819A928(void);
void sub_819AFA8(void* buffer);
void sub_819B0AC(u32 player);
void sub_819B2E0(void);

#define audio_driver_enqueue_command sub_819B418
#define audio_driver_initialize_sound_hardware sub_819A928
#define audio_driver_initialize_state sub_819AFA8

u32 sub_819BA10(u32 command, u32 argument);

#endif
