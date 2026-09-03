#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.upper." #name)))
s32 alloc_Zero(s32, s32, s32, s32);                    /* extern */
UnknownWord sub_8117C9C(s32, s32, s32, s32, s32, s32); /* extern */
UnknownWord sub_8127EF8(s32, s32, s32, s32);           /* extern */

SEC(sub_8122BA0) void sub_8122BA0(s32 arg0, s32 arg1) {
    if (arg1 == 0) {
        sub_8117C9C(alloc_Zero(0x260, 0, 0x08202F70, 0), 8, 0x08202F70, arg0, -2, arg1);
        return;
    }
    sub_8127EF8(alloc_Zero(0x128, 0, 0x08202F78, 0), 8, 0x08202F78, -2);
}
