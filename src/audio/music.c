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

#define FIELD_MUSIC_SEC(name) \
    __attribute__((section(".text.field_music." #name)))

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

FIELD_MUSIC_SEC(sub_8125220)
void field_resume_selected_music_channels(
    u8 channelMask, u32 unused, u8 volume)
{
    (void)unused;
    if (channelMask != 0) {
        if (channelMask & 1)
            music_resume(0, volume, 30);
        if (channelMask & 2)
            music_resume(1, volume, 30);
    }
}
FIELD_MUSIC_SEC(sub_8125220) const u16 sub_8125220_padding = 0;

FIELD_MUSIC_SEC(sub_81252BC)
u8 field_capture_music_channels(u8* songIds, u32 fadeDuration)
{
    u8 playingChannels = 0;

    if ((u8)music_is_playing(0) == 1)
        playingChannels = 1;

    songIds[0] = gMusicState.songIds[0];
    fadeDuration = (u8)fadeDuration;
    music_set_volume(0, 0, fadeDuration);

    if ((u8)music_is_playing(1) == 1)
        playingChannels |= 2;

    songIds[1] = gMusicState.songIds[1];
    music_set_volume(1, 0, fadeDuration);
    return playingChannels;
}
