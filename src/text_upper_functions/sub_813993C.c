#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.upper." #name)))
UnknownWord sub_81398C4(UnknownWord, void*); /* extern */
extern UnknownWord sub_813955C;

SEC(sub_813993C) void sub_813993C(UnknownWord arg0, void* arg1) {
    FIELD_AT(arg1, UnknownWord(**)(UnknownWord, void*), 0x198) = sub_81398C4;
    FIELD_AT(arg1, UnknownWord**, 0x1A0) = &sub_813955C;
    FIELD_AT(arg1, UnknownWord**, 0x1A4) = &sub_813955C;
    sub_81398C4(arg0, arg1);
}
