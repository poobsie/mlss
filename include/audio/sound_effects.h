#ifndef GUARD_AUDIO_SOUND_EFFECTS_H
#define GUARD_AUDIO_SOUND_EFFECTS_H

#include "gba/types.h"

#define SOUND_VOLUME_UNCHANGED (-1)
#define SOUND_VOLUME_MAX 0xFF

int sound_effect_is_playing(int soundId);
void sound_effects_stop_all(void);
void sound_effect_stop(int soundId);
void sound_effect_play(int soundId, int volume);
void sound_effects_set_volume(u8 volume, u8 duration);

#endif
