#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.upper." #name)))
s32 sub_8087CE4();                   /* extern */
UnknownWord sub_80883A0(void*, s32); /* extern */
extern UnknownWord sub_8132594;

SEC(sub_8132570) void sub_8132570(void* arg0) {
    if ((sub_8087CE4() << 0x18) == 0) {
        sub_80883A0(arg0, 0xA);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = &sub_8132594;
    }
}
