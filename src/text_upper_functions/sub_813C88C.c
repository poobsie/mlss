#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.upper." #name)))
UnknownWord sub_81387C8(void*, s32); /* extern */
UnknownWord sub_8139030(void*, s32); /* extern */
UnknownWord sub_813B380(s32, void*); /* extern */
extern UnknownWord sub_813C758;

SEC(sub_813C88C) void sub_813C88C(s32 arg0, void* arg1) {
    sub_81387C8(arg1, 0);
    sub_8139030(arg1, 0);
    FIELD_AT(arg1, UnknownWord(**)(s32, void*), 0x198) = sub_813B380;
    FIELD_AT(arg1, UnknownWord**, 0x1A0) = &sub_813C758;
    FIELD_AT(arg1, UnknownWord**, 0x1A4) = &sub_813C758;
    sub_813B380(arg0, arg1);
}
