#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.early_code_helpers_3." #name)))
void sub_801BC98();
UnknownWord process_remove();
UnknownWord sub_801B7B0();
UnknownWord free_heap_8018D9C();
UnknownWord sub_805C6B8();
UnknownWord sub_8018218();

SEC(sub_801B820) void sub_801B820(void* arg0) {
    FIELD_AT(arg0, u16*, 0x1E) = (u16)(FIELD_AT(arg0, u16*, 0x1E) + 1);
    sub_801B7B0(arg0, FIELD_AT(arg0, u8*, 0x20), FIELD_AT(arg0, u16*, 0x1E),
                FIELD_AT(arg0, u16*, 0x1C));
    if (((u32)FIELD_AT(arg0, u16*, 0x1E) >= (u32)FIELD_AT(arg0, u16*, 0x1C)) && (arg0 != NULL)) {
        FIELD_AT(arg0, s32*, 0x18) = 0x08CDBD98;
        process_remove(arg0, 3);
    }
}

SEC(sub_801BD30) void sub_801BD30(void) {
    s32 temp_r0;

    temp_r0 = *(s32*)0x03000D44;
    if (temp_r0 != 0) {
        sub_801BC98(temp_r0, 3);
        *(s32*)0x03000D44 = 0;
    }
}

SEC(sub_801BC98) void sub_801BC98(void* arg0, s32 arg1) {
    FIELD_AT(arg0, s32*, 0x18) = 0x08CDBDA8;
    if (FIELD_AT(arg0, s32*, 0x1C) != 0) {
        free_heap_8018D9C();
    }
    process_remove(arg0, arg1);
}

SEC(sub_8029788) void sub_8029788(void* arg0) {
    if (((s32)(FIELD_AT(arg0, u16*, 0xFC) << 0x15) >> 0x1C) == 0) {
        sub_805C6B8(FIELD_AT(arg0, s32*, 0x304));
    }
    FIELD_AT(arg0, u16*, 0xFC) = (u16)(FIELD_AT(arg0, u16*, 0xFC) | 0x780);
}

SEC(sub_8029460) void sub_8029460(void* arg0) {
    sub_8018218(FIELD_AT(FIELD_AT(FIELD_AT(arg0, void**, 0x1C), void**, 0), s32*, 8), 0x06010400, 0x4C0,
                0x20, 0);
    sub_8018218(FIELD_AT(FIELD_AT(FIELD_AT(arg0, void**, 0x1C), void**, 0xC), s32*, 8), 0x060108C0,
                0x500, 0x20, 0);
}
