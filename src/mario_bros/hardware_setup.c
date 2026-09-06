#include "global.h"
#include "gba/m4a_internal.h"
#include "mario_bros/functions.h"

#define MB_LATE_SECTION(name) __attribute__((section(".text.mariobros_late." #name)))

void _08F6F340(u32);
void TrackStop(struct MusicPlayerInfo*, struct MusicPlayerTrack*);

MB_LATE_SECTION(sub_8F510CC) void mario_bros_disable_interrupts(void) {
    *(volatile u16*)0x04000004 = 0;
    *(volatile u16*)0x04000200 = 0;
    *(volatile u16*)0x04000208 = 0;
}

MB_LATE_SECTION(sub_8F5C06C) void mario_bros_reset_platform_state(void) {
    *(u32*)0x0203FFF8 = 0;
    *(u8*)0x0203FFFC = 0;
    *(u8*)0x0203FFFF = (*(u8*)0x0203FFFF & 0xFC) | 2;
    _08F6F340(0x9C);
}

MB_LATE_SECTION(sub_8F950A4)
void mario_bros_reset_sound_dma_if_ident_changed(void)
{
    struct SoundInfo* soundInfo = SOUND_INFO_PTR;
    u32 ident = soundInfo->ident;

    if (ident != ID_NUMBER) {
        *(vu16*)0x040000C6 = 0xB600;
        *(vu16*)0x040000D2 = 0xB600;
        soundInfo->pcmDmaCounter = 0;
        soundInfo->ident = ident - 10;
    }
}

MB_LATE_SECTION(sub_8F9523C)
void m4aMPlayStop(struct MusicPlayerInfo* mplayInfo)
{
    struct MusicPlayerTrack* track;
    int trackCount;

    if (mplayInfo->ident == ID_NUMBER) {
        mplayInfo->ident++;
        mplayInfo->status |= MUSICPLAYER_STATUS_PAUSE;
        trackCount = mplayInfo->trackCount;
        track = mplayInfo->tracks;
        while (trackCount > 0) {
            TrackStop(mplayInfo, track);
            trackCount--;
            track++;
        }
        mplayInfo->ident = ID_NUMBER;
    }
}
