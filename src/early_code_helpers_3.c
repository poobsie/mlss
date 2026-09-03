#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.early_code_helpers_3." #name)))
UnknownWord sub_805C6B8();
UnknownWord sub_8018218();

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
