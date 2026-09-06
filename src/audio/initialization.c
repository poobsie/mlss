#include "global.h"
#include "audio/driver.h"
#include "audio/driver_state.h"

#define SEC(name) __attribute__((section(".text.audio_initialization." #name)))

struct AudioInitializationState {
    u8 unknown000[0x88C];
    u8 enabledFlags;
    u8 unknown88D[3];
    u16 soundVolume;
    u8 unknown892[0x0A];
    u16 musicVolumes[2];
    u16 unknown8A0[2];
    u16 musicTempos[2];
};

extern struct AudioInitializationState gAudioInitializationState
    __asm__("gGameState");

void sub_819A43C(void);
void sub_8018E88(s32 first, s32 second);

SEC(sub_8018E24)
void audio_initialize(void)
{
    u8 enabledFlags;

    gAudioInitializationState.soundVolume = 0xFF00;
    gAudioInitializationState.musicVolumes[0] = 0xFF00;
    gAudioInitializationState.musicVolumes[1] = 0xFF00;
    gAudioInitializationState.musicTempos[0] = 0x4B00;
    gAudioInitializationState.musicTempos[1] = 0x4B00;
    sub_819A43C();
    audio_driver_initialize_state((void*)0x02000480);
    enabledFlags = gAudioInitializationState.enabledFlags;
    enabledFlags |= 6;
    gAudioInitializationState.enabledFlags = enabledFlags;
    sub_8018E88(0, 0x64);
}
