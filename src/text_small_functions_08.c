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

SEC(sub_8106D9C) void sub_8106D9C(void* arg0) {
    void* temp_r2;

    if ((sub_810591C() << 0x18) != 0) {
        temp_r2 = *(void**)0x03000FD8;
        if (!(4 & FIELD_AT(temp_r2, u8*, 0x2BF))) {
            if (FIELD_AT(temp_r2, u8*, 0x346) == 2) {
                sub_810CB04(0, 0);
                sub_810CB04(1, 0);
            }
            FIELD_AT(arg0, UnknownWord**, 4) = &sub_80FCC78;
        }
    }
}

SEC(sub_810CDB4) void sub_810CDB4(void) {
    void* temp_r1;

    temp_r1 = *(void**)0x03000FD8;
    if (FIELD_AT(temp_r1, void**, 0x290) != NULL) {
        sub_8085260(FIELD_AT(temp_r1, s32*, 0x250), 4);
        sub_8085260(FIELD_AT(*(void**)0x03000FD8, s32*, 0x250), 5);
        FIELD_AT(FIELD_AT(*(void**)0x03000FD8, void**, 0x290), s32*, 4) = 0x0810CD99;
    }
}

SEC(sub_810D038) void sub_810D038(s32 arg0) {
    sub_810D00C();
    sub_8084578(FIELD_AT(*(void**)0x03000FD8, s32*, 0x250), 0, 0, 0xD, 0, 0x12, 3);
    sub_80847B0(FIELD_AT(*(void**)0x03000FD8, s32*, 0x250), 1, 0, 0);
    sub_808520C(FIELD_AT(*(void**)0x03000FD8, s32*, 0x250), 0, 7, 6, arg0, 0x91);
}

SEC(sub_810FD10) void sub_810FD10(void* arg0) {
    void* temp_r2;

    temp_r2 = FIELD_AT(arg0, void**, 0x30);
    if (8 & FIELD_AT(FIELD_AT(temp_r2, void**, 8), u8*, 0x12)) {
        sub_8082E1C(temp_r2, 0, 0, 0);
        sub_80883A0(arg0, 0xC);
        sound_effect_play(0x10F, SOUND_VOLUME_UNCHANGED);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_810F824;
    }
}

SEC(sub_811090C) s32 sub_811090C(void* arg0) {
    s32 var_r0;
    void* var_r1;

    var_r0 = sub_8086C64();
    if (var_r0 == 0) {
        var_r1 = FIELD_AT(arg0, void**, 0x30);
        if (var_r1 != NULL) {
            do {
                FIELD_AT(var_r1, s32*, 0xA8) = 1;
                var_r1 = FIELD_AT(var_r1, void**, 0x30);
            } while (var_r1 != NULL);
        }
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_81109D0;
        sound_effect_stop(0x10F);
        var_r0 = 0;
    }
    return var_r0;
}

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

SEC(sub_8112350) void sub_8112350(s32 arg0) {
    void* temp_r2;
    void* temp_r2_2;

    temp_r2 = FIELD_AT(*(void**)0x03000FD8, void**, 0x80);
    if ((6 & FIELD_AT(temp_r2, u8*, 0x7E)) == 2) {
        FIELD_AT(temp_r2, s32*, 0x54) = arg0;
    }
    temp_r2_2 = FIELD_AT(*(void**)0x03000FD8, void**, 0x84);
    if ((temp_r2_2 != NULL) && ((6 & FIELD_AT(temp_r2_2, u8*, 0x7E)) == 2)) {
        FIELD_AT(temp_r2_2, s32*, 0x54) = arg0;
    }
}

SEC(sub_81124D0) void sub_81124D0(void* arg0) {
    sub_808843C(arg0, 0x8A, 0x6C, 0, 0x100);
    sub_80880C4(arg0, 0x380);
    sub_8082E1C(arg0, 0xA, 0, 0);
    FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_81127B8;
    sound_effect_play(0x11B, SOUND_VOLUME_UNCHANGED);
}

SEC(sub_811448C) void sub_811448C(void* arg0) {
    u8 temp_r5;
    void* temp_r2;

    temp_r5 = sub_8087CE4();
    if (temp_r5 == 0) {
        temp_r2 = *(void**)0x03000FD8;
        FIELD_AT(temp_r2, u8*, 0xC) = (u8)(FIELD_AT(temp_r2, u8*, 0xC) | 0x80);
        sub_8082E1C(arg0, -1, -1, 0);
        FIELD_AT(FIELD_AT(arg0, void**, 8), s8*, 0x20) = 0x10;
        FIELD_AT(arg0, s32*, 0x4C) = (s32)temp_r5;
    }
}

SEC(sub_811458C) void sub_811458C(void* arg0) {
    sub_8082E1C(FIELD_AT(FIELD_AT(arg0, void**, 0x30), s32*, 0x30), 4, 0, 0);
    FIELD_AT(arg0, s16*, 0xAC) = 0x20;
    FIELD_AT(arg0, UnknownWord**, 0x50) = &sub_81135C0;
    FIELD_AT(arg0, s32*, 0x4C) = 0x081141F5;
    sound_effect_play(0x120, SOUND_VOLUME_UNCHANGED);
}
