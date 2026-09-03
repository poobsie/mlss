#include "global.h"
#include "audio/sound_effects.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.small_functions_02." #name)))
extern UnknownWord sub_8060360;
extern UnknownWord sub_806048C;
extern UnknownWord sub_8060CB8;
extern UnknownWord sub_80610D4;
extern UnknownWord sub_80618A4;
extern UnknownWord sub_8062548;
extern UnknownWord sub_8062F40;
extern UnknownWord sub_8063524;
UnknownWord free_heap_8018D9C();
UnknownWord process_remove();
UnknownWord sub_8029888();
UnknownWord sub_80184F4();
UnknownWord sub_807F4FC();
UnknownWord sub_8082E1C();
UnknownWord free_heap_8018DA8();
u8 sub_801B1C8();
UnknownWord sub_807C298();
s32 sub_8082B00();

SEC(sub_8059F24) void sub_8059F24(void* arg0) {
    FIELD_AT((void*)0x02000014, s16*, 0) = (s16)(0x1FF & FIELD_AT(arg0, u16*, 0x5A));
    FIELD_AT((void*)0x02000014, s16*, 4) = (s16)(0x1FF & FIELD_AT(arg0, u16*, 0x5C));
    *(s16*)0x0200001C = 0x1FF & FIELD_AT(arg0, u16*, 0x5E);
    FIELD_AT((void*)0x02000016, s16*, 0) = (s16)FIELD_AT(arg0, u8*, 0x60);
    FIELD_AT((void*)0x02000016, s16*, 4) = (s16)FIELD_AT(arg0, u8*, 0x62);
    FIELD_AT(((void*)0x02000016 + 4), s16*, 4) = (s16)FIELD_AT(arg0, u8*, 0x64);
}

SEC(sub_805C73C) void sub_805C73C(void* arg0, s32 arg1) {
    FIELD_AT(arg0, s32*, 0x18) = 0x08CDC2B8;
    *(s16*)0x040000BA = 0;
    sub_8029888(0, 0);
    FIELD_AT(arg0, s8*, 0x1C) = 0;
    if (*(s32*)0x03000E04 != 0) {
        free_heap_8018D9C();
    }
    if (*(s32*)0x03000E00 != 0) {
        free_heap_8018D9C();
    }
    process_remove(arg0, arg1);
}

SEC(sub_805DA1C) void sub_805DA1C(void* arg0, s32 arg1) {
    FIELD_AT(arg0, s32*, 0x18) = 0x08CDC2C8;
    sub_80184F4(0x06000000);
    if (FIELD_AT(arg0, s32*, 0xA4) != 0) {
        free_heap_8018D9C();
    }
    if (FIELD_AT(arg0, s32*, 0xA8) != 0) {
        free_heap_8018D9C();
    }
    if (FIELD_AT(arg0, s32*, 0x98) != 0) {
        free_heap_8018D9C();
    }
    if (FIELD_AT(arg0, s32*, 0x94) != 0) {
        free_heap_8018D9C();
    }
    process_remove(arg0, arg1);
}

SEC(sub_8060324) void sub_8060324(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        sound_effect_stop(0x5C);
        sub_807F4FC(arg0);
        FIELD_AT(arg0, UnknownWord**, 0x60) = &sub_8060360;
        sub_8082E1C(arg0, 4, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_806048C;
    }
}

SEC(sub_8060B68) void sub_8060B68(void* arg0) {
    if (sub_801B1C8(*(s32*)0x03000E18, 0x03000E1C, 0x03000E20) == 1) {
        FIELD_AT(arg0, s32*, 0x10) = (s32) * (s32*)0x03000E1C;
        FIELD_AT(arg0, s32*, 0x14) = (s32) * (s32*)0x03000E20;
        return;
    }
    FIELD_AT(arg0, s32*, 0x10) = (s32) * (s32*)0x03000E1C;
    FIELD_AT(arg0, s32*, 0x14) = (s32) * (s32*)0x03000E20;
    free_heap_8018DA8(*(s32*)0x03000E18);
    FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_8060CB8;
}

SEC(sub_80612FC) void sub_80612FC(void* arg0) {
    if (((u32)FIELD_AT(arg0, u16*, 0xAC) <= 0x3FFFU)
        && ((s32)FIELD_AT(FIELD_AT(arg0, void**, 0x2C), s32*, 0x40) > 0)) {
        FIELD_AT(arg0, s32*, 0xA8) = 1;
    }
    FIELD_AT(arg0, u16*, 0xAC) = (u16)(FIELD_AT(arg0, u16*, 0xAC) + 1);
    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        sub_8082E1C(arg0, 3, 0, 0);
        FIELD_AT(FIELD_AT(arg0, void**, 8), s8*, 0x20) = 0x10;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_80610D4;
    }
}

SEC(sub_8062188) void sub_8062188(void* arg0) {
    s32 temp_r1;

    if (FIELD_AT(arg0, s32*, 0x30) != 0) {
        sub_807C298();
    }
    if (sub_8082B00() == 0) {
        temp_r1 = FIELD_AT(arg0, s32*, 0x9C) & 1;
        switch (temp_r1) { /* irregular */
            case 0:
                sub_8082E1C(arg0, 2, 0, 0);
                break;
            case 1:
                sub_8082E1C(arg0, 6, 0, 0);
                break;
        }
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_80618A4;
    }
}

SEC(sub_80624FC) void sub_80624FC(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        sound_effect_stop(0x81);
        if (FIELD_AT(arg0, s32*, 0x9C) == 0) {
            sub_8082E1C(arg0, 5, 0, 0);
        } else {
            sub_8082E1C(arg0, 7, 0, 0);
        }
        FIELD_AT(arg0, s16*, 0xAC) = 4;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_8062548;
    }
}

SEC(sub_8062F00) void sub_8062F00(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        if (FIELD_AT(arg0, s32*, 0x9C) == 0) {
            sub_8082E1C(arg0, 4, 0, 0);
        } else {
            sub_8082E1C(arg0, 7, 0, 0);
        }
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_8062F40;
    }
}

SEC(sub_80634DC) void sub_80634DC(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        if (FIELD_AT(arg0, s32*, 0x9C) == 0) {
            sub_8082E1C(arg0, 4, 0, 0);
        } else {
            sub_8082E1C(arg0, 5, 0, 0);
        }
        FIELD_AT(arg0, s16*, 0xAC) = 1;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_8063524;
    }
}
