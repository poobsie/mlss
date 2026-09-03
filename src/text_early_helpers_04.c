#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.text_early_helpers_04." #name)))
UnknownWord sub_805BFF0();

SEC(sub_80297B8) void sub_80297B8(void* arg0) {
    if (((s32)(FIELD_AT(arg0, u16*, 0xFC) << 0x15) >> 0x1C) == 0) {
        sub_805BFF0(FIELD_AT(arg0, s32*, 0x304));
    }
}
