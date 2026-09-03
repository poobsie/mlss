#include "global.h"
#define SEC(name) __attribute__((section(".text.upper_gate." #name)))
typedef u32 UnknownWord;
UnknownWord free_heap_8018DA8(s32*);
UnknownWord sub_8021308(s32);
SEC(sub_8161C08) void sub_8161C08(s32* arg0, s32 arg1) {
    sub_8021308(*arg0);
    if (1 & arg1)
        free_heap_8018DA8(arg0);
}
