#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.upper." #name)))
UnknownWord free_heap_8018D9C(); /* extern */

SEC(sub_8123340) void sub_8123340(void) {
    if (*(s32*)0x03000FF4 != 0) {
        free_heap_8018D9C();
    }
    *(s32*)0x03000FF4 = 0;
}
