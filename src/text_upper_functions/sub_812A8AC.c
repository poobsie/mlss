#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.upper." #name)))
UnknownWord sub_81151E4(s32, s32, u16, s32, s32, s32, s32, s32); /* extern */

SEC(sub_812A8AC) void sub_812A8AC(void* arg0, u16 arg1) {
    sub_81151E4(FIELD_AT(arg0, s32*, 0x20), 4, arg1, 8, 0xFFFF, 0xFFFF, 0, 0);
    FIELD_AT(arg0, s8*, 0x69) = 1;
}
