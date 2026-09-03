#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.upper." #name)))
s32 alloc_Zero(s32, s32, s32, s32);                    /* extern */
UnknownWord sub_812A9A0(s32, s32, s32, s32, s32, s32); /* extern */

SEC(sub_812F5A4) void sub_812F5A4(s32 arg0, s32 arg1) {
    sub_812A9A0(alloc_Zero(0xC8, 0, 0x08211B20, 0), 8, 0x08211B20, arg0, arg1, -2);
}
