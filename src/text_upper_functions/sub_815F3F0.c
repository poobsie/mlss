#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.upper_gate." #name)))
UnknownWord sub_8021308();
UnknownWord sub_815FB14(void*, s32);

SEC(sub_815F3F0) void sub_815F3F0(void* arg0, s32 arg1) {
    FIELD_AT(arg0, s32*, 0x30) = 0x08CDCDD0;
    if (FIELD_AT(arg0, s32*, 0x40) != 0) {
        sub_8021308();
        FIELD_AT(arg0, s32*, 0x40) = 0;
    }
    if (FIELD_AT(arg0, s32*, 0x3C) != 0) {
        sub_8021308();
        FIELD_AT(arg0, s32*, 0x3C) = 0;
    }
    sub_815FB14(arg0, arg1);
}
