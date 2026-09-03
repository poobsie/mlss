#include "global.h"
#include "audio/music.h"

#define SECTION(name) __attribute__((section(name)))

extern int sub_819BA2C(void);
extern void sub_819B984(int player);
extern void sub_819B99C(int player);

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
    sub_819B984(player + 1);
    gMusicState.volumes[player] = 0;
}

SECTION(".text.audio_music")
void music_resume(int player, int volume, u8 fadeDuration) {
    sub_819B99C(player + 1);

    if (volume == MUSIC_VOLUME_UNCHANGED) {
        volume = gMusicState.savedVolumes[player] >> 8;
        if (volume == 0)
            volume = MUSIC_VOLUME_MAX;
    }

    music_set_volume(player, (u8)volume, fadeDuration);
}
