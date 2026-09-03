#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.upper_gate." #name)))
UnknownWord sub_81396A8(UnknownWord, void*); /* extern */
extern UnknownWord sub_813967C;

SEC(sub_8139988) void sub_8139988(UnknownWord arg0, void* arg1) {
    FIELD_AT(arg1, UnknownWord(**)(UnknownWord, void*), 0x198) = sub_81396A8;
    FIELD_AT(arg1, UnknownWord**, 0x1A0) = &sub_813967C;
    FIELD_AT(arg1, UnknownWord**, 0x1A4) = &sub_813967C;
    FIELD_AT(arg1, UnknownWord**, 0x1AC) = &sub_813967C;
    sub_81396A8(arg0, arg1);
}
