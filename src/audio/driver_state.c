#include "audio/driver_state.h"
#include "gba/io_reg.h"

#define SEC(name) __attribute__((section(".text.audio_driver_state." #name)))

#define AUDIO_DRIVER_STATE (*(struct AudioDriverState**)0x03007FF0)

void sub_819B070(u32 unused, struct AudioDriverVoice* voice);

SEC(sub_819B2E0) void sub_819B2E0(void)
{
    s32 index = 0;
    struct AudioDriverVoice* voice = AUDIO_DRIVER_STATE->voices[0];

    for (; index < 12; index++, voice++) {
        if (voice->flags & 1) {
            sub_819B070(index, voice);
            voice->flags &= 0xFFFE;
        }
    }
}

SEC(sub_819B0AC) void sub_819B0AC(u32 player)
{
    s32 index = 0;
    struct AudioDriverVoice* voice = AUDIO_DRIVER_STATE->voices[player];

    for (; index < 12; index++, voice++) {
        if (voice->flags & 1) {
            sub_819B070(index, voice);
        }
    }
    AUDIO_DRIVER_STATE->playerFlags[player] &= 0xFE;
}

SEC(sub_819A928) void audio_driver_initialize_sound_hardware(void)
{
    *(vu8*)REG_ADDR_SOUNDCNT_L = 0x77;
    *(vu8*)REG_ADDR_SOUNDCNT_X = 0x8F;
    REG_SOUNDCNT_H = (REG_SOUNDCNT_H & 0xFFFC) | 2;
    *(vu8*)(REG_ADDR_SOUND1CNT_X + 1) = 0x80;
    AUDIO_DRIVER_STATE->unknown4F8 = 0xFF;
}

SEC(sub_819AFA8) void audio_driver_initialize_state(void* buffer)
{
    struct AudioDriverState** driverAddress =
        (struct AudioDriverState**)0x03007FF0;
    struct AudioDriverState* driver;
    s32 player;

    *driverAddress = buffer;
    audio_driver_initialize_sound_hardware();
    driver = *driverAddress;
    driver->commandWriteIndex = 0;
    driver->commandReadIndex = 0;
    (*driverAddress)->playerFlags[0] = 1;
    (*driverAddress)->playerFlags[1] = 0;
    (*driverAddress)->playerFlags[2] = 0;
    (*driverAddress)->playerTempo[0] = 75;

    for (player = 0; player < 3; player++) {
        s32 voice;
        (*driverAddress)->playerSoundIds[player] = 0xFFFF;
        for (voice = 0; voice < 12; voice++) {
            (*driverAddress)->voices[player][voice].flags = 0;
            (*driverAddress)->voices[player][voice].voiceIndex = voice;
            (*driverAddress)->voices[player][voice].playerIndex = player;
        }
    }
}

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

SEC(sub_819B418) u32 audio_driver_enqueue_command(u16 command)
{
    struct AudioDriverState** driverAddress =
        (struct AudioDriverState**)0x03007FF0;

    {
        struct AudioDriverState* driver = *driverAddress;
        driver->commandQueue[driver->commandWriteIndex] = command;
    }
    {
        struct AudioDriverState* driver = *driverAddress;
        driver->commandWriteIndex = (driver->commandWriteIndex + 1) & 7;
    }
    return 0;
}
