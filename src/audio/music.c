#include "global.h"
#include "audio/music.h"
#include "audio/driver.h"

#define SECTION(name) __attribute__((section(name)))

extern int sub_819BA2C(void);

struct MusicStateOverlay {
    u8 padding[0x898];
    u16 songIds[2];
    u16 volumes[2];
    u16 savedVolumes[2];
};

extern struct MusicStateOverlay gMusicState __asm__("gGameState");

SECTION(".text.audio_music")
int music_is_playing(int player) {
    return (sub_819BA2C() >> (player + 1)) & 1;
}

SECTION(".text.audio_music")
u16 music_get_song_id(int player) {
    return gMusicState.songIds[player];
}

SECTION(".text.audio_music")
void music_stop(int player) {
    audio_driver_stop_music_player(player + 1);
    gMusicState.volumes[player] = 0;
}

SECTION(".text.audio_music")
void music_resume(int player, int volume, u8 fadeDuration) {
    audio_driver_resume_music_player(player + 1);

    if (volume == MUSIC_VOLUME_UNCHANGED) {
        volume = gMusicState.savedVolumes[player] >> 8;
        if (volume == 0)
            volume = MUSIC_VOLUME_MAX;
    }

    music_set_volume(player, (u8)volume, fadeDuration);
}
