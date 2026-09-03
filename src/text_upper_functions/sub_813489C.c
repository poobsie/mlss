#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.upper." #name)))
UnknownWord sub_8134560();              /* extern */
UnknownWord sub_81345E8(s32, s32, s32); /* extern */
UnknownWord sub_813481C(s32);           /* extern */

SEC(sub_813489C) s32 sub_813489C(s32 arg0) {
    sub_8134560();
    sub_813481C(arg0);
    sub_81345E8(arg0, 0, 0);
    return 0;
}
