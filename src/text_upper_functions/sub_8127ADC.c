#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.upper_gate." #name)))
UnknownWord sub_80193B4(s32, s32, s32);                          /* extern */
UnknownWord sub_81151E4(s32, s32, u16, s32, s32, s32, s32, s32); /* extern */

SEC(sub_8127ADC) void sub_8127ADC(void* arg0, u16 arg1) {
    sub_81151E4(FIELD_AT(arg0, s32*, 0x15C), 4, arg1, 0x10, 0xFFFF, 0xFFFF, 0, 0);
    sub_80193B4(0, 0, 0x10);
    FIELD_AT(arg0, s8*, 0xEF) = 1;
}
