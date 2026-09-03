#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.upper_gate." #name)))
s32 sub_8082B00();                             /* extern */
UnknownWord sub_8082E1C(void*, s32, s32, s32); /* extern */
extern UnknownWord sub_8133424;

SEC(sub_81333FC) void sub_81333FC(void* arg0) {
    if (sub_8082B00() == 0) {
        sub_8082E1C(arg0, 2, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_8133424;
    }
}
