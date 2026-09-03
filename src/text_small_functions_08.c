#include "global.h"
#include "audio/sound_effects.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.small_functions_08." #name)))
extern UnknownWord sub_80FCC78;
extern UnknownWord sub_810F824;
extern UnknownWord sub_81109D0;
extern UnknownWord sub_8110A94;
extern UnknownWord sub_81127B8;
extern UnknownWord sub_81135C0;
s32 sub_810591C();
UnknownWord sub_810CB04();
UnknownWord sub_8085260();
UnknownWord sub_8084578();
UnknownWord sub_80847B0();
UnknownWord sub_808520C();
UnknownWord sub_810D00C();
UnknownWord sub_8082E1C();
UnknownWord sub_80883A0();
s32 sub_8086C64();
UnknownWord sub_807FB64();
UnknownWord sub_80880C4();
UnknownWord sub_808843C();
u8 sub_8087CE4();

SEC(sub_8110A30) void sub_8110A30(void* arg0) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    void* temp_r1;

    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_80883A0(arg0, 0x20);
        temp_r1 = FIELD_AT(FIELD_AT(arg0, void**, 0x2C), void**, 0x28);
        temp_r0 = FIELD_AT(temp_r1, s32*, 0xD8) + 0x2000;
        FIELD_AT(arg0, s32*, 0x10) = temp_r0;
        FIELD_AT(arg0, s32*, 0x38) = temp_r0;
        temp_r0_2 = FIELD_AT(temp_r1, s32*, 0xDC);
        FIELD_AT(arg0, s32*, 0x14) = temp_r0_2;
        FIELD_AT(arg0, s32*, 0x3C) = temp_r0_2;
        temp_r0_3 = FIELD_AT(temp_r1, s32*, 0xE0) + 0x800;
        FIELD_AT(arg0, s32*, 0x18) = temp_r0_3;
        FIELD_AT(arg0, s32*, 0x40) = temp_r0_3;
        sub_807FB64(FIELD_AT(arg0, void**, 8));
        sound_effect_stop(0x119);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_8110A94;
    }
}

SEC(sub_811458C) void sub_811458C(void* arg0) {
    sub_8082E1C(FIELD_AT(FIELD_AT(arg0, void**, 0x30), s32*, 0x30), 4, 0, 0);
    FIELD_AT(arg0, s16*, 0xAC) = 0x20;
    FIELD_AT(arg0, UnknownWord**, 0x50) = &sub_81135C0;
    FIELD_AT(arg0, s32*, 0x4C) = 0x081141F5;
    sound_effect_play(0x120, SOUND_VOLUME_UNCHANGED);
}
