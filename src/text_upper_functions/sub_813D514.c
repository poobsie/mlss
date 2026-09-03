#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.upper." #name)))
UnknownWord sub_8138944(void*, s32); /* extern */
UnknownWord sub_8138FD4(void*, s32); /* extern */
UnknownWord sub_8139030(void*, s32); /* extern */
UnknownWord sub_813D284(s32, void*); /* extern */
extern UnknownWord sub_8139420;

SEC(sub_813D514) void sub_813D514(s32 arg0, void* arg1) {
    sub_8138944(arg1, 0);
    sub_8139030(arg1, 0);
    sub_8138FD4(arg1, 0xB);
    sub_8138944(FIELD_AT(arg1, void**, 0x344), 0xF);
    FIELD_AT(arg1, UnknownWord(**)(s32, void*), 0x198) = sub_813D284;
    FIELD_AT(arg1, UnknownWord**, 0x1A0) = &sub_8139420;
    FIELD_AT(arg1, UnknownWord**, 0x1A4) = &sub_8139420;
    sub_813D284(arg0, arg1);
}
