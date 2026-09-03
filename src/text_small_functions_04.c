#include "global.h"
#include "audio/sound_effects.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.small_functions_04." #name)))
extern UnknownWord sub_8065FBC;
extern UnknownWord sub_806BC40;
extern UnknownWord sub_806D048;
extern UnknownWord sub_806D104;
extern UnknownWord sub_806D1D4;
extern UnknownWord sub_806D290;
extern UnknownWord sub_806E8E8;
extern UnknownWord sub_806D6A8;
extern UnknownWord sub_8070424;
extern UnknownWord sub_8070534;
extern UnknownWord sub_806F47C;
extern UnknownWord sub_80711A4;
UnknownWord sub_8082E1C();
UnknownWord sub_810DD7C();
UnknownWord sub_807F4FC();
s32 sub_8199F30();
UnknownWord sub_807C298();

SEC(sub_8066780) void sub_8066780(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        if (FIELD_AT(arg0, s32*, 0x9C) == 0) {
            sub_8082E1C(arg0, 6, 0, 0);
        } else {
            sub_8082E1C(arg0, 0xA, 0, 0);
        }
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_8065FBC;
    }
}

SEC(sub_806BFD4) void sub_806BFD4(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        if (FIELD_AT(arg0, s32*, 0xA8) == 0) {
            sub_8082E1C(arg0, 8, 0, 0);
        } else {
            sub_8082E1C(arg0, 0x10, 0, 0);
        }
        FIELD_AT(arg0, s16*, 0xAC) = 8;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_806BC40;
    }
}

SEC(sub_806D548) s32 sub_806D548(void* arg0, UnknownWord arg1) {
    UnknownWord* var_r0;
    s32 temp_r0;

    sub_810DD7C(arg0, arg1, 0xFF);
    temp_r0 = FIELD_AT(arg0, s32*, 0xA8);
    switch (temp_r0) { /* irregular */
        case 0:
            var_r0 = &sub_806D048;
            break;
        case 1:
            var_r0 = &sub_806D104;
            break;
        case 2:
            var_r0 = &sub_806D1D4;
            break;
        default:
            var_r0 = &sub_806D290;
            break;
    }
    FIELD_AT(arg0, UnknownWord**, 0x4C) = var_r0;
    return 0;
}

SEC(sub_806E624) void sub_806E624(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        sound_effect_stop(0x99);
        sub_8082E1C(arg0, 4, 0, 0);
        sub_807F4FC(arg0);
        sound_effect_play(0x118, SOUND_VOLUME_UNCHANGED);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_806E8E8;
    }
}

SEC(sub_806E98C) void sub_806E98C(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 6, 0, 0);
        sub_8082E1C(FIELD_AT(arg0, void**, 0x30), 6, 0, 0);
        FIELD_AT(arg0, s16*, 0xAC) = 4;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_806D6A8;
    }
}

SEC(sub_80705B4) void sub_80705B4(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 0x1B, 0, 0);
        FIELD_AT(arg0, s32*, 0xA8) = (s32)(1 & sub_8199F30());
        *(s32*)0x03000E3C = 0;
        sub_807F4FC(arg0);
        FIELD_AT(arg0, UnknownWord**, 0x60) = &sub_8070424;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_8070534;
    }
}

SEC(sub_8070D88) void sub_8070D88(void* arg0) {
    s32 temp_r0;

    FIELD_AT(arg0, s32*, 0x18) = (s32)(FIELD_AT(arg0, s32*, 0x18) + FIELD_AT(arg0, s32*, 0x8C));
    FIELD_AT(arg0, s32*, 0x8C) = (s32)(FIELD_AT(arg0, s32*, 0x8C) - 0x80);
    if ((s32)FIELD_AT(arg0, s32*, 0x18) <= 0) {
        FIELD_AT(arg0, s32*, 0x18) = 0;
        temp_r0 = FIELD_AT(arg0, s32*, 0x9C) - 1;
        FIELD_AT(arg0, s32*, 0x9C) = temp_r0;
        if (temp_r0 == 0) {
            FIELD_AT(arg0, s32*, 0x8C) = 0x300;
            return;
        }
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_806F47C;
    }
}

SEC(sub_8071018) s32 sub_8071018(void* arg0) {
    sound_effect_stop(0xA7);
    sub_8082E1C(arg0, 4, 0x40E7, 0);
    FIELD_AT(arg0, s32*, 0x80) = 0;
    FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_80711A4;
    sound_effect_play(0x55, SOUND_VOLUME_UNCHANGED);
    return 0;
}

SEC(sub_80745A8) void sub_80745A8(void* arg0) {
    void* temp_r4;
    void* temp_r5;
    void* temp_r6;

    temp_r6 = FIELD_AT(arg0, void**, 0x30);
    temp_r5 = FIELD_AT(temp_r6, void**, 0x30);
    temp_r4 = FIELD_AT(temp_r5, void**, 0x30);
    sub_807C298(FIELD_AT(temp_r4, void**, 0x30));
    sub_807C298(temp_r4);
    sub_807C298(temp_r5);
    sub_807C298(temp_r6);
    sound_effect_stop(0x5E);
    FIELD_AT(arg0, s32*, 0x4C) = 0;
}

SEC(sub_8075DF4) void sub_8075DF4(void* arg0) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r1;
    void* temp_r1_2;

    if (FIELD_AT(arg0, s32*, 0x9C) == 2) {
        temp_r1 = FIELD_AT(arg0, s32*, 0xA0) + 0xFFFFFA00;
        FIELD_AT(arg0, s32*, 0xA0) = temp_r1;
        FIELD_AT(FIELD_AT(arg0, void**, 8), s16*, 0xC) = (s16)temp_r1;
    }
    temp_r0 = FIELD_AT(arg0, s32*, 0xA4);
    if (temp_r0 > 0) {
        temp_r0_2 = temp_r0 - 8;
        FIELD_AT(arg0, s32*, 0xA4) = temp_r0_2;
        temp_r1_2 = FIELD_AT(arg0, void**, 8);
        FIELD_AT(temp_r1_2, s16*, 6) = (s16)temp_r0_2;
        FIELD_AT(temp_r1_2, s16*, 4) = (s16)temp_r0_2;
    }
    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        sub_807C298(arg0);
    }
}
