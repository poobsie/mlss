#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.upper." #name)))
UnknownWord sub_814E8B0(s32, s32, void*); /* extern */
UnknownWord sub_815041C(s32, s32);        /* extern */

SEC(sub_81506B4) void sub_81506B4(s32 arg0, s32 arg1, void* arg2) {
    sub_815041C(arg1, 0);
    FIELD_AT(arg2, UnknownWord(**)(s32, s32, void*), 0xC) = sub_814E8B0;
    sub_814E8B0(arg0, arg1, arg2);
}
