#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.upper." #name)))
UnknownWord sub_804761C(s32, s32); /* extern */
UnknownWord sub_804776C(s32, s32); /* extern */

SEC(sub_8150590) void sub_8150590(s32 arg0) {
    sub_804776C(arg0, 0);
    sub_804761C(arg0, 0);
}
