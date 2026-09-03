#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.upper." #name)))
UnknownWord alloc_Zero(s32, s32, s32, s32); /* extern */
s32 sub_8161698();                          /* extern */
s32 sub_8161AAC();                          /* extern */

SEC(sub_8158044) void* sub_8158044(void* arg0) {
    FIELD_AT(arg0, s32*, 0) = 0;
    FIELD_AT(arg0, s32*, 4) = 0x08CDC4D0;
    FIELD_AT(arg0, s32*, 0x10) = 0;
    FIELD_AT(arg0, s32*, 0x14) = 0;
    FIELD_AT(arg0, s32*, 8) = 0;
    FIELD_AT(arg0, s32*, 0xC) = 0;
    if ((s32)((s32)(*(u8*)0x03001010 << 0x1B) >> 0x1B) <= 5) {
        alloc_Zero(0x34, 1, 0x082126E0, 0);
        FIELD_AT(arg0, s32*, 0xC) = sub_8161AAC();
    } else {
        alloc_Zero(0x34, 1, 0x082126E0, 0);
        FIELD_AT(arg0, s32*, 8) = sub_8161698();
    }
    return arg0;
}
