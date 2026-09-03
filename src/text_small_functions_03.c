#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.small_functions_03." #name)))
extern UnknownWord sub_8063B80;
extern UnknownWord sub_8063C8C;
extern UnknownWord sub_8064614;
extern UnknownWord sub_8065310;
extern UnknownWord sub_806533C;
extern UnknownWord sub_806670C;
extern UnknownWord sub_8066E5C;
extern UnknownWord sub_806A348;
extern UnknownWord sub_806B5F8;
extern UnknownWord sub_806C9A4;
UnknownWord sub_807C298();
UnknownWord sub_810DD7C();
UnknownWord sub_8082E1C();
s32 sub_8086858();
UnknownWord play_sfx_80195B4();
UnknownWord stop_sfx_80195A8();
u32 sub_8199F30();

SEC(sub_8062C48) void sub_8062C48(void* arg0) {
    s32 temp_r1_2;
    u16 temp_r1;
    void* temp_r0;
    void* temp_r2;

    temp_r2 = FIELD_AT(arg0, void**, 0x2C);
    if (!(0x80 & FIELD_AT(temp_r2, u8*, 0x76)) && (FIELD_AT(temp_r2, s32*, 0x18) == 0)) {
        sub_810DD7C(arg0, temp_r2, 0xFF);
    }
    temp_r1 = FIELD_AT(arg0, u16*, 0xAC);
    FIELD_AT(arg0, u16*, 0xAC) = (u16)(temp_r1 - 1);
    if ((s32)(temp_r1 << 0x10) <= 0) {
        temp_r0 = FIELD_AT(arg0, void**, 0x28);
        temp_r1_2 = FIELD_AT(temp_r0, s32*, 0x38);
        if (temp_r1_2 == 0) {
            FIELD_AT(temp_r0, s16*, 0xB4) = (s16)temp_r1_2;
        }
        sub_807C298(arg0);
    }
}

SEC(sub_8063BA8) void sub_8063BA8(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 0xC, 0, 0);
        sub_8086858(arg0, 0x1485);
        FIELD_AT(arg0, UnknownWord**, 0x5C) = &sub_8063B80;
        FIELD_AT(arg0, s16*, 0xAC) = 3;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_8063C8C;
    }
}

SEC(sub_8064D20) void sub_8064D20(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        if (FIELD_AT(arg0, s32*, 0xA0) == 0) {
            sub_8082E1C(arg0, 5, 0, 0);
        } else {
            sub_8082E1C(arg0, 9, 0, 0);
        }
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_8064614;
    }
}

SEC(sub_80651CC) void sub_80651CC(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 2, 0, 0);
        *(s32*)0x03000E3C = sub_8086858(arg0, 0x1509);
        FIELD_AT(arg0, UnknownWord**, 0x5C) = &sub_8065310;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_806533C;
    }
}

SEC(sub_80665AC) void sub_80665AC(void* arg0) {
    void* var_r0;

    if (FIELD_AT(arg0, s32*, 0xA0) == 1) {
        var_r0 = FIELD_AT(FIELD_AT(arg0, void**, 0x30), void**, 0x30);
    } else {
        var_r0 = FIELD_AT(arg0, void**, 0x30);
    }
    if (var_r0 == NULL) {
        play_sfx_80195B4(0x114, -1);
        if (FIELD_AT(arg0, s32*, 0x9C) == 0) {
            sub_8082E1C(arg0, 8, 0, 0);
        } else {
            sub_8082E1C(arg0, 0xC, 0, 0);
        }
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_806670C;
    }
}

SEC(sub_8066E0C) void sub_8066E0C(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        if (FIELD_AT(arg0, s32*, 0x9C) == 0) {
            sub_8082E1C(arg0, 4, 0, 0);
        } else {
            sub_8082E1C(arg0, 5, 0, 0);
        }
        FIELD_AT(arg0, s16*, 0xAC) = 4;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_8066E5C;
        play_sfx_80195B4(0xD5, -1);
    }
}

SEC(sub_8068798) void sub_8068798(void* arg0) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 var_r1;

    FIELD_AT(arg0, s32*, 0x10) = (s32)(FIELD_AT(arg0, s32*, 0x10) + 0xFFFFFECD);
    temp_r0 = FIELD_AT(arg0, s32*, 0x18);
    if (temp_r0 > 0x800) {
        temp_r0_2 = temp_r0 + 0xFFFFFF00;
        FIELD_AT(arg0, s32*, 0x18) = temp_r0_2;
        if (temp_r0_2 <= 0x800) {
            FIELD_AT(arg0, s32*, 0x18) = 0x800;
            sub_8082E1C(arg0, 1, 0, 0);
        }
    }
    var_r1 = FIELD_AT(arg0, s32*, 0x10);
    if (var_r1 < 0) {
        var_r1 += 0xFF;
    }
    if ((s32)(var_r1 >> 8) <= -0x20) {
        sub_807C298(arg0);
    }
}

SEC(sub_806A24C) void sub_806A24C(void* arg0) {
    u32 temp_r4;

    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        stop_sfx_80195A8(0x81);
        temp_r4 = FIELD_AT(arg0, s32*, 0xA4) - FIELD_AT(arg0, s32*, 0xA0);
        FIELD_AT(arg0, s32*, 0xA8) = (s32)(FIELD_AT(arg0, s32*, 0xA0) + (sub_8199F30() % temp_r4));
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_806A348;
    }
}

SEC(sub_806B5A8) void sub_806B5A8(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        if (FIELD_AT(arg0, s32*, 0xA8) == 0) {
            sub_8082E1C(arg0, FIELD_AT(arg0, s32*, 0xA4) + 1, 0, 0);
        } else {
            sub_8082E1C(arg0, FIELD_AT(arg0, s32*, 0xA4) + 4, 0, 0);
        }
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_806B5F8;
    }
}

SEC(sub_806C94C) void sub_806C94C(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        FIELD_AT(arg0, s32*, 0xA8) = (s32)((FIELD_AT(arg0, s32*, 0xA8) + 1) & 1);
        FIELD_AT(arg0, s32*, 0x9C) = 0;
        FIELD_AT((arg0 + 0x9C), s32*, 8) = 0;
        if (FIELD_AT(arg0, s32*, 0xA8) == 0) {
            sub_8082E1C(arg0, 7, 0, 0);
        } else {
            sub_8082E1C(arg0, 0xD, 0, 0);
        }
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_806C9A4;
    }
}
