#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.upper." #name)))
UnknownWord free_heap_8018DA8(void*);
UnknownWord sub_8021308();
SEC(sub_8163B60) void sub_8163B60(void* arg0, s32 arg1) {
    FIELD_AT(arg0, s32*, 0xC) = 0x08CDD0F8;
    if (FIELD_AT(arg0, s32*, 0x10) != 0)
        sub_8021308();
    if (FIELD_AT(arg0, s32*, 0x14) != 0)
        sub_8021308();
    FIELD_AT(arg0, s32*, 0xC) = 0x08CDD118;
    if (1 & arg1)
        free_heap_8018DA8(arg0);
}
