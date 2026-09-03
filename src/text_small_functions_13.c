#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.small_functions_13." #name)))
extern UnknownWord sub_8106AC8;
UnknownWord sub_8082C58();
s32 sub_8082D50();
UnknownWord sub_8082E1C();

SEC(sub_81040DC) void sub_81040DC(void* arg0) {
    s32 sp4;
    s32 sp8;
    s32 spC;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 var_r0;
    void* temp_r1;
    void* temp_r4;
    void* temp_r5;

    temp_r1 = *(void**)0x03000FD8;
    temp_r4 = FIELD_AT(temp_r1, void**, 0x37C);
    temp_r5 = FIELD_AT(temp_r1, void**, 0x278);
    temp_r0 = FIELD_AT(temp_r4, s32*, 0x10) + 0xFFFFFF00;
    FIELD_AT(temp_r4, s32*, 0x10) = temp_r0;
    FIELD_AT(temp_r5, s32*, 0x10) = temp_r0;
    var_r0 = FIELD_AT(temp_r4, s32*, 0x10);
    if (var_r0 < 0) {
        var_r0 += 0xFF;
    }
    sp4 = var_r0 >> 8;
    sp8 = 0;
    spC = 0;
    sub_8082C58(FIELD_AT(temp_r1, s32*, 0x24C), &sp4, &sp8, &spC, 0);
    if (sp4 <= 0xD0) {
        temp_r0_2 =
            ((s32)(sub_8082D50(FIELD_AT(*(void**)0x03000FD8, s32*, 0x24C)) << 0x10) >> 8) + 0xD000;
        FIELD_AT(temp_r4, s32*, 0x10) = temp_r0_2;
        FIELD_AT(temp_r5, s32*, 0x10) = temp_r0_2;
        sub_8082E1C(temp_r5, 4, 0, 0);
        FIELD_AT(*(void**)0x03000FD8, s8*, 0x342) = 0;
        FIELD_AT(arg0, UnknownWord**, 4) = &sub_8106AC8;
    }
}
