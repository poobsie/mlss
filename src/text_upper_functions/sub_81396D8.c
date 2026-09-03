#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.upper." #name)))
UnknownWord sub_80473DC(void*); /* extern */

SEC(sub_81396D8) void sub_81396D8(s32 arg0, void* arg1, void* arg2) {
    if (0x40 & FIELD_AT(arg1, u8*, 0x214)) {
        sub_80473DC(arg1);
    }
    FIELD_AT(arg2, UnknownWord(**)(s32, void*, void*), 4)(arg0, arg1, arg2);
}
