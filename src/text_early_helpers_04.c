#include "global.h"
#include "audio/sound_effects.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.text_early_helpers_04." #name)))
UnknownWord sub_805BFF0();
UnknownWord sub_80494D4();
UnknownWord sub_804FCD4();
UnknownWord free_heap_8018DA8();
u8 sub_8041FFC();

SEC(sub_80297B8) void sub_80297B8(void* arg0) {
    if (((s32)(FIELD_AT(arg0, u16*, 0xFC) << 0x15) >> 0x1C) == 0) {
        sub_805BFF0(FIELD_AT(arg0, s32*, 0x304));
    }
}

SEC(sub_803C610) void sub_803C610(void) {
    sound_effect_stop(0x157);
    sound_effect_stop(0x87);
    sound_effect_stop(0xDB);
    sound_effect_stop(0xDA);
    sound_effect_stop(0xDA);
}

SEC(sub_803C638) void sub_803C638(void* arg0) {
    u16 temp_r2;
    void* temp_r1;

    temp_r1 = FIELD_AT(arg0, void**, 0x200);
    temp_r2 = FIELD_AT(temp_r1, u16*, 4);
    if ((u32)(u16)(temp_r2 - 5) <= 4U) {
        sub_804FCD4(temp_r1);
        return;
    }
    if ((u32)(u16)(temp_r2 - 0xA) <= 2U) {
        sub_80494D4(temp_r1);
    }
}

SEC(sub_8048040) void sub_8048040(void* arg0, s32 arg1) {
    FIELD_AT(arg0, s32*, 0x338) = 0x08CDBDE8;
    if (1 & arg1) {
        free_heap_8018DA8(arg0);
    }
}

SEC(sub_804FBDC) u8 sub_804FBDC(void* arg0) {
    u8 var_r4;

    var_r4 = 0;
    if (((0x801 & FIELD_AT(arg0, u16*, 0x20C)) == 0x801) && !(2 & FIELD_AT(arg0, u8*, 0x35A))) {
        FIELD_AT(arg0, s32*, 0x348) = (s32)FIELD_AT(arg0, s32*, 0xC);
        FIELD_AT(arg0, s32*, 0x34C) = (s32)FIELD_AT(arg0, s32*, 0x10);
        var_r4 = sub_8041FFC(arg0);
    }
    return var_r4;
}
