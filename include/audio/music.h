#ifndef GUARD_AUDIO_MUSIC_H
#define GUARD_AUDIO_MUSIC_H

#include "gba/types.h"

#define MUSIC_VOLUME_UNCHANGED (-1)
#define MUSIC_VOLUME_MAX 0xFF

void music_play(int player, int songId, int volume);
void music_set_volume(int player, u8 volume, u8 duration);
void music_set_tempo(int player, u8 tempo, u8 duration);

int music_is_playing(int player);
u16 music_get_song_id(int player);
void music_stop(int player);
void music_resume(int player, int volume, u8 fadeDuration);

#endif
