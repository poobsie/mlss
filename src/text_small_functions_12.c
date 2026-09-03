#include "global.h"
#include "audio/sound_effects.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.small_functions_12." #name)))
extern UnknownWord sub_806499C;
extern UnknownWord sub_8079018;
extern UnknownWord sub_809D91C;
UnknownWord free_heap_8018D9C();
UnknownWord process_remove();
UnknownWord sub_80184F4();
UnknownWord sub_805C6B8();
UnknownWord free_heap_8018DA8();
u8 sub_801B1C8();
UnknownWord sub_807C298();
UnknownWord sub_807FC08();
UnknownWord sub_80790CC();
UnknownWord sub_8082E1C();
UnknownWord sub_80880C4();
UnknownWord sub_808843C();
UnknownWord free_heap_memory_8018C68();
UnknownWord sub_80E5968();
UnknownWord sub_80E8EFC();
UnknownWord sub_80FAEFC();
UnknownWord sub_808842C();
UnknownWord sub_8106F8C();
UnknownWord sub_810C950();

SEC(sub_8057B58) void sub_8057B58(void* arg0, s32 arg1) {
    FIELD_AT(arg0, s32*, 0x18) = 0x08CDC288;
    if (FIELD_AT(arg0, u8*, 0x584) != 0) {
        sub_805C6B8(arg0);
    }
    sub_80184F4(0x06000000);
    if (FIELD_AT(arg0, s32*, 0xA4) != 0) {
        free_heap_8018D9C();
    }
    if (FIELD_AT(arg0, s32*, 0xA0) != 0) {
        free_heap_8018D9C();
    }
    if (FIELD_AT(arg0, s32*, 0x9C) != 0) {
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

SEC(sub_8063248) void sub_8063248(void* arg0) {
    s32 sp0;
    s32 sp4;
    s32 sp8;
    s32 temp_r2;
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r0_3;

    if (sub_801B1C8(*(s32*)0x03000E18, 0x03000E40, 0x03000E44) == 1) {
        var_r0 = *(s32*)0x03000E40;
        FIELD_AT(arg0, s32*, 0x10) = var_r0;
        temp_r2 = *(s32*)0x03000E44;
        FIELD_AT(arg0, s32*, 0x14) = temp_r2;
        if (var_r0 < 0) {
            var_r0 += 0xFF;
        }
        sp0 = var_r0 >> 8;
        var_r0_2 = temp_r2;
        if (var_r0_2 < 0) {
            var_r0_2 += 0xFF;
        }
        sp4 = var_r0_2 >> 8;
        var_r0_3 = FIELD_AT(arg0, s32*, 0x18);
        if (var_r0_3 < 0) {
            var_r0_3 += 0xFF;
        }
        sp8 = var_r0_3 >> 8;
        sub_807FC08(&sp0, &sp4, &sp8, 0);
        return;
    }
    free_heap_8018DA8(*(s32*)0x03000E18);
    sub_807C298(arg0);
}

SEC(sub_8064908) void sub_8064908(void* arg0) {
    s32 sp0;
    s32 sp4;
    s32 sp8;
    s32 temp_r2;
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r0_3;
    void* temp_r1;

    temp_r1 = FIELD_AT(arg0, void**, 8);
    FIELD_AT(temp_r1, u16*, 0xC) = (u16)(FIELD_AT(temp_r1, u16*, 0xC) + 0x1000);
    if (sub_801B1C8(*(s32*)0x03000E18, 0x03000E60, 0x03000E64) == 1) {
        var_r0 = *(s32*)0x03000E60;
        FIELD_AT(arg0, s32*, 0x10) = var_r0;
        temp_r2 = *(s32*)0x03000E64;
        FIELD_AT(arg0, s32*, 0x18) = temp_r2;
        if (var_r0 < 0) {
            var_r0 += 0xFF;
        }
        sp0 = var_r0 >> 8;
        var_r0_2 = FIELD_AT(arg0, s32*, 0x14);
        if (var_r0_2 < 0) {
            var_r0_2 += 0xFF;
        }
        sp4 = var_r0_2 >> 8;
        var_r0_3 = temp_r2;
        if (var_r0_3 < 0) {
            var_r0_3 += 0xFF;
        }
        sp8 = (var_r0_3 >> 8) + 0x20;
        sub_807FC08(&sp0, &sp4, &sp8, 0);
        return;
    }
    free_heap_8018DA8(*(s32*)0x03000E18);
    FIELD_AT(arg0, s16*, 0xAC) = 0;
    FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_806499C;
}

SEC(sub_8079C9C) void sub_8079C9C(void* arg0) {
    s32 temp_r0;
    s32 temp_r0_2;

    temp_r0 = FIELD_AT(arg0, s32*, 0xA4) - 1;
    FIELD_AT(arg0, s32*, 0xA4) = temp_r0;
    if (temp_r0 <= 0) {
        sub_80790CC(arg0);
        sound_effect_play(0x86, SOUND_VOLUME_UNCHANGED);
        FIELD_AT(arg0, s32*, 0xA4) = 6;
        temp_r0_2 = FIELD_AT(arg0, s32*, 0xA8) + 1;
        FIELD_AT(arg0, s32*, 0xA8) = temp_r0_2;
        if ((temp_r0_2 > 5) && (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12))) {
            if (*(s32*)0x03000F6C == 0) {
                sub_8082E1C(arg0, 6, 0x4029, 0);
            } else {
                sub_8082E1C(arg0, 0xA, 0x4029, 0);
            }
            FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_8079018;
        }
    }
}

SEC(sub_809D4E4) void sub_809D4E4(void* arg0) {
    s32 var_r1;
    s32 var_r1_2;
    s32 var_r2;
    s32 var_r2_2;
    void* temp_r0;
    void* temp_r4;
    void* temp_r5;
    void* temp_r7;
    void* temp_r8;

    temp_r0 = *(void**)0x03000FD8;
    temp_r4 = FIELD_AT(temp_r0, void**, 0x70);
    temp_r8 = temp_r4 + 8;
    temp_r5 = FIELD_AT(temp_r0, void**, 0x74);
    temp_r7 = temp_r5 + 8;
    sub_8082E1C(arg0, 8, 0, 0);
    if ((6 & FIELD_AT(temp_r4, u8*, 0x7E)) != 2) {
        var_r2 = FIELD_AT(temp_r7, s32*, 0x3C);
        goto block_4;
    }
    if ((6 & FIELD_AT(temp_r5, u8*, 0x7E)) != 2) {
        var_r2 = FIELD_AT(temp_r8, s32*, 0x3C);
    block_4:
        if (var_r2 < 0) {
            var_r2 += 0xFF;
        }
        var_r2_2 = var_r2 >> 8;
    } else {
        var_r1 = FIELD_AT(temp_r8, s32*, 0x3C) + FIELD_AT(temp_r7, s32*, 0x3C);
        if (var_r1 < 0) {
            var_r1 += 0x1FF;
        }
        var_r2_2 = var_r1 >> 9;
    }
    var_r1_2 = FIELD_AT(FIELD_AT(arg0, void**, 0x2C), s32*, 0x38);
    if (var_r1_2 < 0) {
        var_r1_2 += 0xFF;
    }
    sub_808843C(arg0, (var_r1_2 >> 8) + 0x38, var_r2_2, 0, 0x100);
    sub_80880C4(arg0, 0x180);
    sound_effect_play(0x99, SOUND_VOLUME_UNCHANGED);
    FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_809D91C;
}

SEC(sub_80FAFD8) void sub_80FAFD8(void* arg0, s32 arg1) {
    s32 temp_r0;
    s32 temp_r0_2;
    void* temp_r1;

    FIELD_AT(arg0, s32*, 0x18) = 0x08CDC328;
    sub_80FAEFC(arg0);
    temp_r0 = FIELD_AT(arg0, s32*, 0x20);
    if (temp_r0 != 0) {
        sub_80E8EFC(temp_r0, 3);
        FIELD_AT(arg0, s32*, 0x20) = 0;
    }
    temp_r0_2 = FIELD_AT(arg0, s32*, 0x28);
    if (temp_r0_2 != 0) {
        sub_80E5968(temp_r0_2, 3);
        FIELD_AT(arg0, s32*, 0x28) = 0;
    }
    free_heap_memory_8018C68(FIELD_AT(arg0, s32*, 0x24));
    temp_r1 = *(void**)0x03000FC0;
    FIELD_AT(temp_r1, s32*, 0x55C) = (s32) * (s32*)0x083B9704;
    FIELD_AT(temp_r1, s32*, 0x560) = (s32) * (s32*)0x083B98C4;
    FIELD_AT(temp_r1, s32*, 0x564) = (s32) * (s32*)0x083B9D00;
    FIELD_AT(temp_r1, s32*, 0x568) = (s32) * (s32*)0x083BA13C;
    FIELD_AT(temp_r1, s32*, 0x56C) = (s32) * (s32*)0x083BA4A8;
    process_remove(arg0, arg1);
}

SEC(sub_80FD8BC) void sub_80FD8BC(void* arg0) {
    s32 var_r2;
    s32 var_r4;
    s32 var_r5;
    s32 var_r6;
    void* temp_r2;

    if (!(4 & FIELD_AT(*(void**)0x03000FD8, u8*, 0xB))) {
        sub_810C950();
        temp_r2 = *(void**)0x03000FD8;
        if (4 & FIELD_AT(temp_r2, u8*, 0x2C0)) {
            var_r4 = FIELD_AT(temp_r2, s32*, 0x80) + 8;
            var_r6 = 0x28;
            var_r5 = 0x7C;
            var_r2 = 0x2039;
        } else {
            var_r4 = FIELD_AT(temp_r2, s32*, 0x84) + 8;
            var_r6 = 0x36;
            var_r5 = 0x5C;
            var_r2 = 0x2068;
        }
        sub_8082E1C(var_r4, 3, var_r2, 0);
        sub_808843C(var_r4, var_r6, var_r5, 0, 0x100);
        sub_808842C(var_r4, 0x400, 0x20);
        FIELD_AT(arg0, UnknownWord(**)(void*), 4) = sub_8106F8C;
        sub_8106F8C(arg0);
        sound_effect_play(0x2B, SOUND_VOLUME_UNCHANGED);
    }
}
