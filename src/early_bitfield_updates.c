#include "global.h"

#define SEC(name) __attribute__((section(".text.early_bitfield_updates." #name)))

SEC(sub_80290CC) void sub_80290CC(void *object, s32 value)
{
    s32 current;
    s32 bits;
    object = (u8 *)object + 0x12C;
    value <<= 2;
    current = *(u8 *)object;
    bits = 3;
    bits &= current;
    bits |= value;
    *(u8 *)object = bits;
}

SEC(sub_8047B5C) void sub_8047B5C(void *object, u16 value)
{
    s32 offset = 0x266;
    u16 *source = (u16 *)((u8 *)object + offset);
    u16 previous = *source;
    offset = 0x268;
    *(u16 *)((u8 *)object + offset) = previous;
    *source = value;
}
