#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.upper." #name)))
s32 sub_8082B00();                             /* extern */
UnknownWord sub_8082E1C(void*, s32, s32, s32); /* extern */
extern UnknownWord sub_8132E34;

SEC(sub_8132DE4) void sub_8132DE4(void* arg0) {
    if (sub_8082B00() == 0) {
        sub_8082E1C(arg0, 8, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_8132E34;
    }
}
