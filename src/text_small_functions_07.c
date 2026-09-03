#include "global.h"
#include "audio/sound_effects.h"
#include "object/runtime_object.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.small_functions_07." #name)))
extern UnknownWord sub_80913A4;
extern UnknownWord sub_8092534;
extern UnknownWord sub_8093580;
extern UnknownWord sub_80D9E34;
extern UnknownWord sub_80DA098;
extern UnknownWord sub_80DBFBC;
extern UnknownWord sub_8104184;
void* sub_8087650(s32);
extern UnknownWord sub_8107360;
UnknownWord sub_807B7A8();
UnknownWord sub_807FF48();
UnknownWord sub_8082E1C();
UnknownWord sub_8086858();
UnknownWord sub_807F708();
UnknownWord sub_810CAD0();
u8 sub_8116620();
UnknownWord sub_807FB34();
UnknownWord sub_8085260();

SEC(sub_8086700) s32 sub_8086700(void* arg0) {
    s32 temp_r1;
    u8 temp_r1_2;
    void* temp_r2;

    temp_r1 = 6 & FIELD_AT(arg0, u8*, 0x76);
    if ((temp_r1 != 6) && (temp_r1 != 2)) {
        temp_r2 = FIELD_AT(arg0, void**, 0x28);
        if (temp_r2 != NULL) {
            temp_r1_2 = 2 & FIELD_AT(temp_r2, u8*, 0x111);
            if (temp_r1_2 == 0) {
                FIELD_AT(arg0, s32*, 0x4C) = 0x08087441;
                FIELD_AT(arg0, s32*, 0x80) = (s32)temp_r1_2;
                sub_807FF48(0x0808742D, temp_r2);
                FIELD_AT(temp_r2, u8*, 0x111) = (u8)(FIELD_AT(temp_r2, u8*, 0x111) | 1);
                sub_807B7A8(FIELD_AT(arg0, void**, 0x28));
                return 1;
            }
        }
    }
    return 0;
}

SEC(sub_8091BE0) void sub_8091BE0(void* arg0) {
    s32 temp_r0;
    void* temp_r1;
    void* temp_r2;

    if (0x38 & FIELD_AT(arg0, u8*, 0x76)) {
        runtime_object_finish_action(arg0);
        return;
    }
    temp_r0 = FIELD_AT(arg0, s32*, 0x9C);
    if (temp_r0 > 0) {
        FIELD_AT(arg0, s32*, 0x9C) = (s32)(temp_r0 - 1);
        return;
    }
    temp_r1 = FIELD_AT(arg0, void**, 0x30);
    FIELD_AT(temp_r1, s32*, 0xA0) = 0xB400;
    FIELD_AT(temp_r1, s32*, 0xA4) = 0xFFFFFE34;
    sub_8082E1C(arg0, 2, 0, 0);
    temp_r2 = FIELD_AT(arg0, void**, 8);
    FIELD_AT(temp_r2, u8*, 0x12) = (u8)(FIELD_AT(temp_r2, u8*, 0x12) | 0x10);
    FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_80913A4;
}

SEC(sub_8092D70) void sub_8092D70(void* arg0) {
    s32 temp_r0;
    void* temp_r1;
    void* temp_r2;

    if (0x38 & FIELD_AT(arg0, u8*, 0x76)) {
        runtime_object_finish_action(arg0);
        return;
    }
    temp_r0 = FIELD_AT(arg0, s32*, 0x9C);
    if (temp_r0 > 0) {
        FIELD_AT(arg0, s32*, 0x9C) = (s32)(temp_r0 - 1);
        return;
    }
    temp_r1 = FIELD_AT(arg0, void**, 0x30);
    FIELD_AT(temp_r1, s32*, 0xA0) = 0xB400;
    FIELD_AT(temp_r1, s32*, 0xA4) = 0xFFFFFE34;
    sub_8082E1C(arg0, 2, 0, 0);
    temp_r2 = FIELD_AT(arg0, void**, 8);
    FIELD_AT(temp_r2, u8*, 0x12) = (u8)(FIELD_AT(temp_r2, u8*, 0x12) | 0x10);
    FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_8092534;
}

SEC(sub_8093DBC) void sub_8093DBC(void* arg0) {
    s32 temp_r0;
    void* temp_r1;
    void* temp_r2;

    if (0x38 & FIELD_AT(arg0, u8*, 0x76)) {
        runtime_object_finish_action(arg0);
        return;
    }
    temp_r0 = FIELD_AT(arg0, s32*, 0x9C);
    if (temp_r0 > 0) {
        FIELD_AT(arg0, s32*, 0x9C) = (s32)(temp_r0 - 1);
        return;
    }
    temp_r1 = FIELD_AT(arg0, void**, 0x30);
    FIELD_AT(temp_r1, s32*, 0xA0) = 0xB400;
    FIELD_AT(temp_r1, s32*, 0xA4) = 0xFFFFFE34;
    sub_8082E1C(arg0, 2, 0, 0);
    temp_r2 = FIELD_AT(arg0, void**, 8);
    FIELD_AT(temp_r2, u8*, 0x12) = (u8)(FIELD_AT(temp_r2, u8*, 0x12) | 0x10);
    FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_8093580;
}

SEC(sub_80D9F50) void sub_80D9F50(void* arg0) {
    s32 temp_r5;

    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        temp_r5 = FIELD_AT(arg0, s32*, 0xA8);
        if (temp_r5 != 0) {
            sub_8082E1C(arg0, 0xA, 0, 0);
        } else {
            sub_8082E1C(arg0, 0xB, 0, 0);
            sub_8086858(arg0, 0x13CA);
            FIELD_AT(arg0, UnknownWord**, 0x5C) = &sub_80D9E34;
            FIELD_AT(arg0, s32*, 0x54) = temp_r5;
        }
        FIELD_AT(arg0, s16*, 0xAC) = 0x18;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_80DA098;
    }
}

SEC(sub_80DC07C) void sub_80DC07C(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        sub_8082E1C(arg0, 5, 0, 0);
        sound_effect_play(0x84, SOUND_VOLUME_UNCHANGED);
        FIELD_AT(arg0, s16*, 0xAC) = 0x20;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_80DBFBC;
    }
}

SEC(sub_8106AC8) void sub_8106AC8(void* arg0) {
    void* temp_r4;

    temp_r4 = FIELD_AT(*(void**)0x03000FD8, void**, 0x278);
    if (8 & FIELD_AT(FIELD_AT(temp_r4, void**, 8), u8*, 0x12)) {
        sub_8082E1C(temp_r4, 5, 0, 0);
        FIELD_AT(FIELD_AT(temp_r4, void**, 8), s8*, 0x20) = 0x10;
        FIELD_AT(arg0, UnknownWord**, 4) = &sub_8104184;
    }
}

SEC(sub_81071F0) void sub_81071F0(void* arg0) {
    s32 temp_r4;
    void* temp_r0;

    if (sub_8116620(FIELD_AT(*(void**)0x03000FD8, s32*, 0x248)) != 1) {
        temp_r4 = FIELD_AT(arg0, s32*, 0xC);
        sub_810CAD0();
        temp_r0 = sub_8087650(temp_r4);
        if (temp_r0 != NULL) {
            sub_807F708(4, 0, 0x20, 0, (s32)FIELD_AT(FIELD_AT(temp_r0, void**, 0x10), u16*, 0x14));
        }
        FIELD_AT(arg0, s16*, 0x10) = 0xC;
        FIELD_AT(arg0, UnknownWord**, 4) = &sub_8107360;
    }
}

SEC(sub_810C950) void sub_810C950(void) {
    void* temp_r4;
    void* temp_r4_2;

    temp_r4 = FIELD_AT(*(void**)0x03000FD8, void**, 0x284);
    if (temp_r4 != NULL) {
        sub_807FB34(FIELD_AT(temp_r4, s32*, 8));
        FIELD_AT(*(void**)0x03000FD8, void**, 0x284) = NULL;
        FIELD_AT(temp_r4, s32*, 4) = 0;
    }
    temp_r4_2 = FIELD_AT(*(void**)0x03000FD8, void**, 0x288);
    if (temp_r4_2 != NULL) {
        sub_807FB34(FIELD_AT(temp_r4_2, s32*, 8));
        FIELD_AT(*(void**)0x03000FD8, void**, 0x288) = NULL;
        FIELD_AT(temp_r4_2, s32*, 4) = 0;
    }
}

SEC(sub_810CCF4) void sub_810CCF4(void) {
    void* temp_r1;
    void* temp_r3;

    temp_r3 = *(void**)0x03000FD8;
    temp_r1 = FIELD_AT(temp_r3, void**, 0x28C);
    if (temp_r1 != NULL) {
        FIELD_AT(temp_r3, void**, 0x28C) = NULL;
        FIELD_AT(temp_r1, s32*, 4) = 0;
        sub_8085260(FIELD_AT(temp_r3, s32*, 0x250), 2);
        sub_8085260(FIELD_AT(*(void**)0x03000FD8, s32*, 0x250), 3);
    }
}
