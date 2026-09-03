#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.small_functions_06." #name)))
extern UnknownWord sub_8062F8C;
extern UnknownWord sub_80651B0;
extern UnknownWord sub_806541C;
extern UnknownWord sub_809A178;
extern UnknownWord sub_80A99A8;
UnknownWord sub_8082E1C();
s32 sub_8086858();
UnknownWord sub_80884AC();

SEC(sub_8062F40) void sub_8062F40(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        if (FIELD_AT(arg0, s32*, 0x9C) == 0) {
            sub_8082E1C(arg0, 5, 0, 0);
        } else {
            sub_8082E1C(arg0, 8, 0, 0);
        }
        FIELD_AT(arg0, s16*, 0xAC) = 0x1E;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_8062F8C;
    }
}

SEC(sub_806533C) void sub_806533C(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 3, 0, 0);
        *(s32*)0x03000E3C = sub_8086858(arg0, 0x151D);
        FIELD_AT(arg0, UnknownWord**, 0x5C) = &sub_806541C;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_80651B0;
    }
}

SEC(sub_809A858) void sub_809A858(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        if (!(FIELD_AT(arg0, s32*, 0x98) & 2)) {
            sub_8082E1C(arg0, 5, 0, 0);
        } else {
            sub_8082E1C(arg0, 7, 0, 0);
        }
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_809A178;
    }
}

SEC(sub_80AC4AC) void sub_80AC4AC(void) {
    s32 temp_r1;
    void* temp_r0;
    void* temp_r4;
    void* temp_r5;
    void* temp_r6;
    void* temp_r7;

    temp_r0 = *(void**)0x03000FD8;
    temp_r5 = FIELD_AT(temp_r0, void**, 0x70);
    temp_r7 = temp_r5 + 8;
    temp_r4 = FIELD_AT(temp_r0, void**, 0x74);
    temp_r6 = temp_r4 + 8;
    sub_80884AC(temp_r6);
    if (0x20 & FIELD_AT(temp_r4, u8*, 0x81)) {
        temp_r1 = 6 & FIELD_AT(temp_r5, u8*, 0x7E);
        if ((temp_r1 == 2) || (temp_r1 == 4)) {
            FIELD_AT(temp_r7, UnknownWord**, 0x4C) = &sub_80A99A8;
        }
        FIELD_AT(temp_r6, s32*, 0x4C) = 0;
    }
}
