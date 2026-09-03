#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.upper_gate." #name)))
UnknownWord sub_8160E4C(s32);

SEC(sub_81615E4) void sub_81615E4(void) {
    sub_8160E4C(FIELD_AT(*(void**)0x03001024, s32*, 0x2C));
    sub_8160E4C(FIELD_AT(*(void**)0x03001024, s32*, 0x30));
}
