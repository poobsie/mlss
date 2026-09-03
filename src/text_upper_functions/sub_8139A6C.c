#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.upper_gate." #name)))
UnknownWord sub_81398C4(UnknownWord, void*); /* extern */
extern UnknownWord sub_8139880;

SEC(sub_8139A6C) void sub_8139A6C(UnknownWord arg0, void* arg1) {
    FIELD_AT(arg1, UnknownWord(**)(UnknownWord, void*), 0x198) = sub_81398C4;
    FIELD_AT(arg1, UnknownWord**, 0x1A0) = &sub_8139880;
    FIELD_AT(arg1, UnknownWord**, 0x1A4) = &sub_8139880;
    sub_81398C4(arg0, arg1);
}
