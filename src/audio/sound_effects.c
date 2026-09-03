#include "global.h"
#include "audio/sound_effects.h"

#define SECTION(name) __attribute__((section(name)))

extern void sub_819BA00(void);
extern void sub_819B9E8(int soundId);
extern void sub_819B9D0(int soundId);
extern int sub_819BABC(int soundId);

struct AudioStateOverlay {
    u8 padding[0x890];
    u16 volume;
};

extern struct AudioStateOverlay gAudioState __asm__("gGameState");

SECTION(".text.audio_sound_effects")
int sound_effect_is_playing(int soundId) {
    int activeChannels = sub_819BABC(soundId);
    return ((u32)(-activeChannels | activeChannels)) >> 31;
}

// Preserve the original zero-filled alignment before the next function.
const u16 sound_effect_is_playing_padding SECTION(".text.audio_sound_effects") = 0;

SECTION(".text.audio_sound_effects")
void sound_effects_stop_all(void) {
    sub_819BA00();
}

SECTION(".text.audio_sound_effects")
void sound_effect_stop(int soundId) {
    sub_819B9E8(soundId);
}

SECTION(".text.audio_sound_effects")
void sound_effect_play(int soundId, int volume) {
    sub_819B9D0(soundId);

    if (volume != SOUND_VOLUME_UNCHANGED || gAudioState.volume == 0) {
        if (gAudioState.volume == 0)
            volume = SOUND_VOLUME_MAX;
        sound_effects_set_volume((u8)volume, 0);
    }
}
