#include "global.h"
#include "audio/sound_effects.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.upper." #name)))
UnknownWord sub_8082E1C(void*, s32, s32, s32); /* extern */
extern UnknownWord sub_8133BC0;

SEC(sub_8133C20) void sub_8133C20(void* arg0) {
    s32 temp_r0;

    FIELD_AT(arg0, s32*, 0x18) = (s32)(FIELD_AT(arg0, s32*, 0x18) + FIELD_AT(arg0, s32*, 0x8C));
    temp_r0 = FIELD_AT(arg0, s32*, 0x8C) - FIELD_AT(arg0, s32*, 0x94);
    FIELD_AT(arg0, s32*, 0x8C) = temp_r0;
    if (temp_r0 <= 0) {
        FIELD_AT(arg0, s32*, 0x18) = (s32)(FIELD_AT(arg0, s32*, 0x18) + 0x1000);
        FIELD_AT(arg0, s32*, 0xA4) = 0xC;
        FIELD_AT((arg0 + 0xA4), s32*, 4) = 0;
        sub_8082E1C(arg0, 0xC, 0, 0);
        sound_effect_play(0xD5, SOUND_VOLUME_UNCHANGED);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_8133BC0;
    }
}
