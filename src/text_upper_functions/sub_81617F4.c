#include "global.h"
#define SEC(name) __attribute__((section(".text.upper_gate." #name)))
typedef u32 UnknownWord;
UnknownWord free_heap_8018DA8(s32*);
UnknownWord sub_8021308(s32);
SEC(sub_81617F4) void sub_81617F4(s32* arg0, s32 arg1) {
    sub_8021308(*arg0);
    if (1 & arg1)
        free_heap_8018DA8(arg0);
}
