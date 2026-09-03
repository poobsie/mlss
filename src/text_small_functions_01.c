#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.small_functions_01." #name)))
extern UnknownWord sub_805F638;
extern UnknownWord sub_808750C;
extern UnknownWord sub_8060E90;
extern UnknownWord sub_8061B8C;
extern UnknownWord sub_8067A84;
extern UnknownWord sub_8068F3C;
extern UnknownWord sub_80694B4;
extern UnknownWord sub_806E98C;
extern UnknownWord sub_806F90C;
extern UnknownWord sub_806FCF0;
extern UnknownWord sub_80801A0;
extern UnknownWord sub_808C868;
extern UnknownWord sub_80DA098;
extern UnknownWord sub_80DB860;
extern UnknownWord sub_810192C;
void* sub_807D2D0(UnknownWord*, s32, s32);
extern UnknownWord sub_810D5F4;
extern UnknownWord sub_810D624;
extern UnknownWord sub_810FF78;
extern UnknownWord sub_8110078;
UnknownWord play_sfx_80195B4();
s32 sub_8082B00();
UnknownWord sub_8082E1C();
UnknownWord stop_sfx_80195A8();
UnknownWord sub_807DC8C();
u8 sub_8080168();
UnknownWord sub_8082AAC();
UnknownWord free_heap_8018DA8();
UnknownWord free_heap_memory_8018C68();
s32 sub_8087CE4();
UnknownWord sub_807F4FC();
UnknownWord sub_80873B8();
u8 sub_8120E90();
UnknownWord sub_81059D8();
s32 sub_8199F30();
u32 sub_81DD77C();
UnknownWord sub_8087360();
UnknownWord sub_80883A0();
UnknownWord sub_81147B4();

SEC(sub_805F604) void sub_805F604(void* arg0) {
    if (sub_8082B00() == 0) {
        sub_8082E1C(arg0, 2, 0, 0);
        play_sfx_80195B4(0x118, -1);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_805F638;
    }
}

SEC(sub_80613FC) void sub_80613FC(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 0, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_808750C;
    }
}

SEC(sub_8061480) void sub_8061480(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 3, 0, 0);
        FIELD_AT(FIELD_AT(arg0, void**, 8), s8*, 0x20) = 0x10;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_8060E90;
    }
}

SEC(sub_8062150) void sub_8062150(void* arg0) {
    UnknownWord* var_r0;

    if (FIELD_AT(arg0, s32*, 0x30) != 0) {
        var_r0 = &sub_808750C;
        goto block_4;
    }
    if (sub_8082B00() == 0) {
        sub_8082E1C(arg0, 0xA, 0, 0);
        var_r0 = &sub_8061B8C;
    block_4:
        FIELD_AT(arg0, UnknownWord**, 0x4C) = var_r0;
    }
}

SEC(sub_8065ED4) void sub_8065ED4(void* arg0) {
    u8 var_r0;
    void* var_r1;

    var_r0 = 0;
    var_r1 = FIELD_AT(arg0, void**, 0x30);
    if (var_r1 != NULL) {
        do {
            var_r0 += 1;
            var_r1 = FIELD_AT(var_r1, void**, 0x30);
        } while (var_r1 != NULL);
    }
    if (var_r0 == 0) {
        sub_8082E1C(arg0, 0xC, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_808750C;
    }
}

SEC(sub_8067A4C) void sub_8067A4C(void* arg0) {
    FIELD_AT(arg0, s32*, 0x10) = (s32)(FIELD_AT(arg0, s32*, 0x10) + 0x200);
    FIELD_AT(arg0, s32*, 0x18) = (s32)(FIELD_AT(arg0, s32*, 0x18) - FIELD_AT(arg0, s32*, 0x8C));
    FIELD_AT(arg0, s32*, 0x8C) = (s32)(FIELD_AT(arg0, s32*, 0x8C) + 0x66);
    if ((s32)FIELD_AT(arg0, s32*, 0x18) <= 0) {
        FIELD_AT(arg0, s32*, 0x18) = 0;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_808750C;
    }
}

SEC(sub_806829C) void sub_806829C(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 3, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_8067A84;
    }
}

SEC(sub_806947C) void sub_806947C(void* arg0) {
    if (sub_8082B00() == 0) {
        sub_8082E1C(arg0, 2, 0, 0);
        FIELD_AT(arg0, s32*, 0xA4) = 0x300;
        FIELD_AT((arg0 + 0xA4), s32*, 4) = 0x66;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_8068F3C;
    }
}

SEC(sub_806A3C0) void sub_806A3C0(void* arg0) {
    if (sub_8082B00() == 0) {
        sub_8082E1C(arg0, 2, 0, 0);
        FIELD_AT(arg0, s32*, 0x8C) = 0x300;
        FIELD_AT((arg0 + 0x8C), s32*, 0x1C) = 0x66;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_80694B4;
    }
}

SEC(sub_806E794) void sub_806E794(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        stop_sfx_80195A8(0x6C);
        sub_8082E1C(arg0, 5, 0, 0);
        sub_8082E1C(FIELD_AT(arg0, void**, 0x30), 5, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_806E98C;
    }
}

SEC(sub_8070F98) void sub_8070F98(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        stop_sfx_80195A8(0x11C);
        sub_8082E1C(arg0, 0x16, 0, 0);
        FIELD_AT(arg0, s16*, 0xAC) = 4;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_806F90C;
    }
}

SEC(sub_807116C) void sub_807116C(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        stop_sfx_80195A8(0x11C);
        FIELD_AT(arg0, s32*, 0x8C) = 0x14;
        sub_8082E1C(arg0, 0x25, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_806FCF0;
    }
}

SEC(sub_807F648) void sub_807F648(void* arg0) {
    u8 temp_r2;
    void* temp_r4;

    temp_r4 = FIELD_AT(arg0, void**, 8);
    temp_r2 = sub_8080168(temp_r4);
    if (8 & FIELD_AT(FIELD_AT(temp_r4, void**, 8), u8*, 0x12)) {
        if (temp_r2 == 0) {
            sub_807DC8C(arg0);
            return;
        }
        FIELD_AT(arg0, UnknownWord**, 4) = &sub_80801A0;
    }
}

SEC(sub_8081E74) void sub_8081E74(void) {
    sub_8082AAC(0x2027);
    sub_8082AAC(0x2046);
    sub_8082AAC(0x2056);
    sub_8082AAC(0x2075);
    sub_8082AAC(0x2089);
}

SEC(sub_80854F8) void sub_80854F8(void* arg0, s32 arg1) {
    *(s16*)0x02000000 = (s16) * (s32*)0x03000F70;
    free_heap_memory_8018C68(FIELD_AT(arg0, s32*, 0x288));
    if (1 & arg1) {
        free_heap_8018DA8(arg0);
    }
}

SEC(sub_80886BC) void sub_80886BC(void* arg0) {
    sub_8087CE4();
    if (0x20 & FIELD_AT(arg0, u8*, 0x79)) {
        FIELD_AT(arg0, s32*, 0x4C) = (s32)FIELD_AT(arg0, s32*, 0x50);
        FIELD_AT(arg0, s32*, 0x50) = 0;
    }
}

SEC(sub_808C6EC) void sub_808C6EC(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        stop_sfx_80195A8(0x81);
        sub_807F4FC(arg0);
        FIELD_AT(arg0, s16*, 0xAC) = 0x18;
        sub_80873B8(arg0, 3, 0);
        FIELD_AT(arg0, UnknownWord**, 0x50) = &sub_808C868;
    }
}

SEC(sub_80DA0E0) void sub_80DA0E0(void* arg0) {
    u8 temp_r2;

    temp_r2 = FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x21);
    if (temp_r2 == 0) {
        FIELD_AT(arg0, s16*, 0xAC) = (s16)temp_r2;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_80DA098;
    }
}

SEC(sub_80DBDE8) void sub_80DBDE8(void* arg0) {
    sub_8082E1C(arg0, 2, 0, 0);
    play_sfx_80195B4(0x11A, -1);
    FIELD_AT(arg0, s16*, 0xAC) = 0x30;
    FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_80DB860;
}

SEC(sub_80E8F1C) u32 sub_80E8F1C(void* arg0, s32 arg1) {
    return (u32)((arg1 - ((0xC & *FIELD_AT(FIELD_AT(arg0, void**, 4), u16**, 0x188)) << 0xC)) << 0x10)
           >> 0x15;
}

SEC(sub_80F7590) void sub_80F7590(s32 arg0) {
    void* temp_r2;

    temp_r2 = FIELD_AT(FIELD_AT(*(void**)0x03000FD8, void**, 0x244), void**, 0x2C);
    FIELD_AT(temp_r2, s32*, 0x1788) = (s32)(FIELD_AT(temp_r2, s32*, 0x1788) & ~arg0);
}

SEC(sub_80FAEC4) void sub_80FAEC4(void* arg0, void* arg1, u8 arg2) {
    if (sub_8120E90(FIELD_AT(arg0, s32*, 0x14), arg2) == 1) {
        FIELD_AT(arg1, u16*, 0xA0) = (u16)(FIELD_AT(arg1, u16*, 0xA0) ^ 2);
    }
}

SEC(sub_8106928) void sub_8106928(void) {
    u32 temp_r0;
    u32 var_r1;

    temp_r0 = sub_81DD77C(0x64, sub_8199F30());
    var_r1 = (u32)~temp_r0 >> 0x1F;
    if ((s32)temp_r0 > 0x5B) {
        var_r1 += 1;
    }
    if ((s32)temp_r0 > 0x61) {
        var_r1 += 1;
    }
    sub_81059D8(0x200, var_r1);
}

SEC(sub_81069B4) void sub_81069B4(s8 arg0) {
    void* temp_r2;

    FIELD_AT(*(void**)0x03000FD8, s8*, 0x3A5) = arg0;
    temp_r2 = *(void**)0x03000FD8;
    FIELD_AT(temp_r2, u8*, 0xB) = (u8)(FIELD_AT(temp_r2, u8*, 0xB) | 0x40);
}

SEC(sub_81072A8) void sub_81072A8(void* arg0) {
    if (!(4 & FIELD_AT(*(void**)0x03000FD8, u8*, 0xB)) && ((sub_8082B00() << 0x18) == 0)) {
        sub_8087360();
        FIELD_AT(arg0, UnknownWord**, 4) = &sub_810192C;
    }
}

SEC(sub_810CCC8) void sub_810CCC8(void) {
    void* temp_r0;

    temp_r0 = sub_807D2D0(&sub_810D624, 0, 0);
    FIELD_AT(temp_r0, s16*, 0x14) = 0;
    FIELD_AT(sub_807D2D0(&sub_810D5F4, 0x18, 0), void**, 8) = temp_r0;
}

SEC(sub_810FE94) void sub_810FE94(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 0xE, 0, 0);
        sub_80883A0(arg0, 0x1E);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_810FF78;
    }
}

SEC(sub_810FF18) void sub_810FF18(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 0xE, 0, 0);
        sub_80883A0(arg0, 0x1E);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_8110078;
    }
}

SEC(sub_811488C) void sub_811488C(void* arg0) {
    if ((sub_8087CE4(FIELD_AT(FIELD_AT(arg0, void**, 0x30), s32*, 0x30)) << 0x18) == 0) {
        stop_sfx_80195A8(0xD5);
        FIELD_AT(arg0, UnknownWord(**)(void*), 0x4C) = sub_81147B4;
        sub_81147B4(arg0);
    }
}
