#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.upper_gate." #name)))
UnknownWord sub_8082E1C(void*, s32, s32, s32); /* extern */
extern UnknownWord sub_808750C;

SEC(sub_81333D8) void sub_81333D8(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0x30) == 0) {
        sub_8082E1C(arg0, 0xD, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_808750C;
    }
}
