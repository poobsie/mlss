#include "global.h"

struct AudioToneRangeRecord {
    u8 minimum;
    u8 maximum;
    u8 unknown02[6];
};

#define AUDIO_TONE_RANGE_TABLE ((const u8*)0x0821D1CC)
#define SEC(name) __attribute__((section(".text.audio_driver_tables." #name)))

#define audio_driver_find_tone_range sub_819A8EC

SEC(sub_819A8EC)
const struct AudioToneRangeRecord* audio_driver_find_tone_range(
    u32 group, s32 value)
{
    const u16* offsets = (const u16*)AUDIO_TONE_RANGE_TABLE;
    const struct AudioToneRangeRecord* record =
        (const struct AudioToneRangeRecord*)(AUDIO_TONE_RANGE_TABLE + offsets[group]);
    const struct AudioToneRangeRecord* end;

    group++;
    end =
        (const struct AudioToneRangeRecord*)(AUDIO_TONE_RANGE_TABLE + offsets[group]);

    for (; record != end; record++) {
        if (record->minimum <= value && record->maximum >= value)
            return record;
    }
    return 0;
}
