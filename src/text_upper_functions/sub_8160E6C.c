#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.upper_gate." #name)))
UnknownWord free_heap_8018D9C();

SEC(sub_8160E6C) void sub_8160E6C(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0x804) != 0) {
        free_heap_8018D9C();
        FIELD_AT(arg0, s32*, 0x804) = 0;
    }
    if (FIELD_AT(arg0, s32*, 0x80C) != 0) {
        free_heap_8018D9C();
        FIELD_AT(arg0, s32*, 0x80C) = 0;
    }
}
