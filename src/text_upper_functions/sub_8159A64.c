#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.upper_gate." #name)))
UnknownWord free_heap_8018DA8(void*);
UnknownWord sub_8021308();

SEC(sub_8159A64) void sub_8159A64(void* arg0, s32 arg1) {
    if (FIELD_AT(arg0, s32*, 0x524) != 0)
        sub_8021308();
    if (1 & arg1)
        free_heap_8018DA8(arg0);
}
