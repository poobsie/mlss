#include "global.h"
#include "gba/m4a_internal.h"
#include "mario_bros/functions.h"

#define MB_LATE_SECTION(name) __attribute__((section(".text.mariobros_late." #name)))

void _08F6F340(u32);
u32 umul3232H32(u32, u32);
void TrackStop(struct MusicPlayerInfo*, struct MusicPlayerTrack*);
void mario_bros_call_secondary_object_callback_b(void*);

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

MB_LATE_SECTION(sub_8F948FC)
u32 MidiKeyToFreq(struct WaveData* wave, u8 key, u8 fineAdjust)
{
    u32 value1;
    u32 value2;
    u32 fineAdjustShifted = fineAdjust << 24;

    if (key > 178) {
        key = 178;
        fineAdjustShifted = 255 << 24;
    }

    value1 = gScaleTable[key];
    value1 = gFreqTable[value1 & 0xF] >> (value1 >> 4);
    value2 = gScaleTable[key + 1];
    value2 = gFreqTable[value2 & 0xF] >> (value2 >> 4);
    return umul3232H32(
        wave->freq,
        value1 + umul3232H32(value2 - value1, fineAdjustShifted));
}

MB_LATE_SECTION(sub_8F950E0)
void MPlayOpen(
    struct MusicPlayerInfo* mplayInfo,
    struct MusicPlayerTrack* tracks,
    u8 trackCount)
{
    struct SoundInfo* soundInfo;

    if (trackCount == 0)
        return;
    if (trackCount > MAX_MUSICPLAYER_TRACKS)
        trackCount = MAX_MUSICPLAYER_TRACKS;

    soundInfo = SOUND_INFO_PTR;
    if (soundInfo->ident != ID_NUMBER)
        return;

    soundInfo->ident++;
    mario_bros_call_secondary_object_callback_b(mplayInfo);
    mplayInfo->tracks = tracks;
    mplayInfo->trackCount = trackCount;
    mplayInfo->status = MUSICPLAYER_STATUS_PAUSE;
    while (trackCount != 0) {
        tracks->flags = 0;
        trackCount--;
        tracks++;
    }

    if (soundInfo->MPlayMainHead != NULL) {
        mplayInfo->MPlayMainNext = soundInfo->MPlayMainHead;
        mplayInfo->musicPlayerNext = soundInfo->musicPlayerHead;
        soundInfo->MPlayMainHead = NULL;
    }
    soundInfo->musicPlayerHead = mplayInfo;
    soundInfo->MPlayMainHead = (MPlayMainFunc)0x0201B929;
    soundInfo->ident = ID_NUMBER;
    mplayInfo->ident = ID_NUMBER;
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

MB_LATE_SECTION(sub_8F959CC)
void m4aMPlayVolumeControl(
    struct MusicPlayerInfo* mplayInfo, u16 trackBits, u16 volume)
{
    struct MusicPlayerTrack* track;
    u32 bit;
    int trackCount;

    if (mplayInfo->ident == ID_NUMBER) {
        mplayInfo->ident++;
        trackCount = mplayInfo->trackCount;
        track = mplayInfo->tracks;
        bit = 1;
        while (trackCount > 0) {
            if ((trackBits & bit) != 0 && (track->flags & MPT_FLG_EXIST) != 0) {
                track->volX = volume >> 2;
                track->flags |= MPT_FLG_VOLCHG;
            }
            trackCount--;
            track++;
            bit <<= 1;
        }
        mplayInfo->ident = ID_NUMBER;
    }
}
