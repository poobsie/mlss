#include "global.h"

#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.state_field_helpers." #name)))

SEC(sub_819B0F8) void sub_819B0F8(s32 index, s32 value)
{
    void *global = *(void **)0x03007FF0;
    s32 offset;
    index <<= 2;
    offset = 0x4A4;
    global = (u8 *)global + offset;
    global = (u8 *)global + index;
    FIELD(global, s32, 0) = value;
}
