#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.upper_gate." #name)))
UnknownWord sub_8021308(); /* extern */

SEC(sub_8134928) void sub_8134928(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0xC) != 0) {
        sub_8021308();
        FIELD_AT(arg0, s32*, 0xC) = 0;
    }
}
