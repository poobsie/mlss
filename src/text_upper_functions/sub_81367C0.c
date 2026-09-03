#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.upper_gate." #name)))
UnknownWord process_add(void*, u8); /* extern */

SEC(sub_81367C0) void* sub_81367C0(void* arg0, u8 arg1) {
    process_add(arg0, arg1);
    FIELD_AT(arg0, s32*, 0x18) = 0x08CDC4A0;
    return arg0;
}
