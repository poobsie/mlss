#include "global.h"

#define SEC(name) __attribute__((section(".text.early_bitfield_updates." #name)))

SEC(sub_8047B5C) void sub_8047B5C(void *object, u16 value)
{
    s32 offset = 0x266;
    u16 *source = (u16 *)((u8 *)object + offset);
    u16 previous = *source;
    offset = 0x268;
    *(u16 *)((u8 *)object + offset) = previous;
    *source = value;
}
