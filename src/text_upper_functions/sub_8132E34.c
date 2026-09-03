#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.upper." #name)))
UnknownWord sub_8082E1C(void*, s32, s32, s32); /* extern */
extern UnknownWord sub_8132EA8;

SEC(sub_8132E34) void sub_8132E34(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 9, 0, 0);
        FIELD_AT(arg0, s16*, 0xAC) = 0x3C;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_8132EA8;
    }
}
