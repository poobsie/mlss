#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.small_functions_05." #name)))
extern UnknownWord sub_80706B0;
extern UnknownWord sub_8079284;
extern UnknownWord sub_80797E0;
extern UnknownWord sub_80798C4;
extern UnknownWord sub_8086F0C;
extern UnknownWord sub_8091938;
extern UnknownWord sub_8092AC8;
extern UnknownWord sub_8093B14;
extern UnknownWord sub_809A858;
UnknownWord sub_807F47C();
UnknownWord sub_8082E1C();
UnknownWord sub_810DD7C();
UnknownWord play_sfx_80195B4();
UnknownWord sub_807F4FC();
UnknownWord sub_807C298();
UnknownWord free_heap_memory_8018C68();
UnknownWord process_remove();
UnknownWord sub_80E4FC8();
UnknownWord sub_808DD2C();

SEC(sub_8070670) s32 sub_8070670(void* arg0, UnknownWord arg1) {
    sub_810DD7C(arg0, arg1, 0xFF);
    sub_807F47C(arg0);
    FIELD_AT(arg0, s32*, 0x10) =
        (s32)FIELD_AT(FIELD_AT(FIELD_AT(arg0, void**, 0x2C), void**, 0x28), s32*, 0xD8);
    sub_8082E1C(arg0, 8, 0, 0);
    FIELD_AT(arg0, s16*, 0xAC) = 2;
    FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_80706B0;
    return 0;
}

SEC(sub_8079348) void sub_8079348(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        sub_8082E1C(arg0, 4, 0x4029, 0);
        play_sfx_80195B4(0xE6, -1);
        FIELD_AT(arg0, s16*, 0xAC) = 4;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_8079284;
        sub_807F4FC(arg0);
        FIELD_AT(arg0, UnknownWord**, 0x60) = &sub_80797E0;
    }
}

SEC(sub_807940C) void sub_807940C(void* arg0) {
    if (*(s32*)0x03000F6C == 0) {
        sub_8082E1C(arg0, 2, 0x4029, 0);
    } else {
        sub_8082E1C(arg0, 7, 0x4029, 0);
    }
    FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_80798C4;
}

SEC(sub_80794FC) void sub_80794FC(void* arg0) {
    s32 temp_r0;
    s32 var_r1_2;
    s32 var_r2;
    void* var_r1;

    var_r2 = FIELD_AT(arg0, s32*, 0x10);
    FIELD_AT(arg0, s32*, 0x10) = (s32)(var_r2 + 0xFFFFFD80);
    var_r1 = FIELD_AT(arg0, void**, 0xC);
    if (var_r1 != NULL) {
        do {
            temp_r0 = FIELD_AT(var_r1, s32*, 4);
            FIELD_AT(var_r1, s32*, 4) = var_r2;
            var_r2 = temp_r0;
            var_r1 = FIELD_AT(var_r1, void**, 0);
        } while (var_r1 != NULL);
    }
    var_r1_2 = FIELD_AT(arg0, s32*, 0x10);
    if (var_r1_2 < 0) {
        var_r1_2 += 0xFF;
    }
    if ((s32)(var_r1_2 >> 8) <= -0x28) {
        sub_807C298(arg0);
    }
}

SEC(sub_807A658) void sub_807A658(void* arg0, s32 arg1) {
    UnknownWord (*temp_r1)(s32);

    FIELD_AT(arg0, s32*, 0x18) = 0x08CDC2D8;
    if (FIELD_AT(arg0, s32*, 0x1C) != -1) {
        sub_80E4FC8();
        if (FIELD_AT(arg0, s32*, 0x1C) != 0) {
            free_heap_memory_8018C68();
        }
        temp_r1 = FIELD_AT(arg0, UnknownWord(**)(s32), 0x20);
        if (temp_r1 != NULL) {
            temp_r1(FIELD_AT(arg0, s32*, 0x24));
        }
    }
    process_remove(arg0, arg1);
}

SEC(sub_8087AE0) void sub_8087AE0(void* arg0) {
    void* temp_r0;
    void* temp_r2;
    void* temp_r3;

    temp_r0 = *(void**)0x03000FD8;
    temp_r2 = FIELD_AT(temp_r0, void**, 0x70);
    temp_r3 = FIELD_AT(temp_r0, void**, 0x74);
    if ((6 & FIELD_AT(temp_r2, u8*, 0x7E)) == 2) {
        FIELD_AT(temp_r2, u8*, 0x81) = (u8)(FIELD_AT(temp_r2, u8*, 0x81) | 4);
    }
    if ((6 & FIELD_AT(temp_r3, u8*, 0x7E)) == 2) {
        FIELD_AT(temp_r3, u8*, 0x81) = (u8)(FIELD_AT(temp_r3, u8*, 0x81) | 4);
    }
    FIELD_AT(arg0, UnknownWord**, 4) = &sub_8086F0C;
}

SEC(sub_8091B30) void sub_8091B30(void* arg0) {
    s32 temp_r0;
    void* temp_r1;
    void* temp_r2;

    if (0x38 & FIELD_AT(arg0, u8*, 0x76)) {
        sub_808DD2C(arg0);
        return;
    }
    temp_r0 = FIELD_AT(arg0, s32*, 0x9C);
    if (temp_r0 > 0) {
        FIELD_AT(arg0, s32*, 0x9C) = (s32)(temp_r0 - 1);
        return;
    }
    temp_r1 = FIELD_AT(arg0, void**, 0x30);
    FIELD_AT(temp_r1, s32*, 0xA0) = 0xB400;
    FIELD_AT(temp_r1, s32*, 0xA4) = 0xA00;
    sub_8082E1C(arg0, 2, 0, 0);
    temp_r2 = FIELD_AT(arg0, void**, 8);
    FIELD_AT(temp_r2, u8*, 0x12) = (u8)(FIELD_AT(temp_r2, u8*, 0x12) | 0x10);
    FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_8091938;
}

SEC(sub_8092CC0) void sub_8092CC0(void* arg0) {
    s32 temp_r0;
    void* temp_r1;
    void* temp_r2;

    if (0x38 & FIELD_AT(arg0, u8*, 0x76)) {
        sub_808DD2C(arg0);
        return;
    }
    temp_r0 = FIELD_AT(arg0, s32*, 0x9C);
    if (temp_r0 > 0) {
        FIELD_AT(arg0, s32*, 0x9C) = (s32)(temp_r0 - 1);
        return;
    }
    temp_r1 = FIELD_AT(arg0, void**, 0x30);
    FIELD_AT(temp_r1, s32*, 0xA0) = 0xB400;
    FIELD_AT(temp_r1, s32*, 0xA4) = 0xA00;
    sub_8082E1C(arg0, 2, 0, 0);
    temp_r2 = FIELD_AT(arg0, void**, 8);
    FIELD_AT(temp_r2, u8*, 0x12) = (u8)(FIELD_AT(temp_r2, u8*, 0x12) | 0x10);
    FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_8092AC8;
}

SEC(sub_8093D0C) void sub_8093D0C(void* arg0) {
    s32 temp_r0;
    void* temp_r1;
    void* temp_r2;

    if (0x38 & FIELD_AT(arg0, u8*, 0x76)) {
        sub_808DD2C(arg0);
        return;
    }
    temp_r0 = FIELD_AT(arg0, s32*, 0x9C);
    if (temp_r0 > 0) {
        FIELD_AT(arg0, s32*, 0x9C) = (s32)(temp_r0 - 1);
        return;
    }
    temp_r1 = FIELD_AT(arg0, void**, 0x30);
    FIELD_AT(temp_r1, s32*, 0xA0) = 0xB400;
    FIELD_AT(temp_r1, s32*, 0xA4) = 0xA00;
    sub_8082E1C(arg0, 2, 0, 0);
    temp_r2 = FIELD_AT(arg0, void**, 8);
    FIELD_AT(temp_r2, u8*, 0x12) = (u8)(FIELD_AT(temp_r2, u8*, 0x12) | 0x10);
    FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_8093B14;
}

SEC(sub_809A808) void sub_809A808(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        if (!(FIELD_AT(arg0, s32*, 0x98) & 1)) {
            sub_8082E1C(arg0, 3, 0, 0);
        } else {
            sub_8082E1C(arg0, 4, 0, 0);
        }
        play_sfx_80195B4(0x88, -1);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_809A858;
    }
}
