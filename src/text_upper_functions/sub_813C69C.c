#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.upper." #name)))
UnknownWord sub_81387C8(void*, s32); /* extern */
UnknownWord sub_8138FF0(void*, s32); /* extern */
UnknownWord sub_813C5FC(s32, void*); /* extern */
extern UnknownWord sub_813C810;

SEC(sub_813C69C) void sub_813C69C(s32 arg0, void* arg1) {
    sub_81387C8(arg1, 0x15);
    sub_8138FF0(arg1, 0x28);
    FIELD_AT(arg1, UnknownWord(**)(s32, void*), 0x198) = sub_813C5FC;
    FIELD_AT(arg1, UnknownWord**, 0x1A0) = &sub_813C810;
    FIELD_AT(arg1, UnknownWord**, 0x1A4) = &sub_813C810;
    sub_813C5FC(arg0, arg1);
}
