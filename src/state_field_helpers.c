#include "global.h"

#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.state_field_helpers." #name)))

SEC(sub_8116610) void sub_8116610(void *object)
{
    s32 value = FIELD(object, u16, 0x34);
    u16 *destination = (u16 *)((u8 *)object + 0x44);
    s32 zero = 0;
    *destination = value;
    FIELD(object, u16, 0x34) = zero;
}
SEC(sub_8116610) const u16 sub_8116610_padding = 0;

SEC(sub_8150E2C) void sub_8150E2C(void *object)
{
    s32 value = FIELD(object, u16, 0x2C);
    s32 mask = -2;
    mask &= value;
    FIELD(object, u16, 0x2C) = mask;
}

SEC(sub_8150E38) void sub_8150E38(void *object)
{
    s32 value = FIELD(object, u16, 0x2C);
    s32 mask = 1;
    mask |= value;
    FIELD(object, u16, 0x2C) = mask;
}
SEC(sub_8150E38) const u16 sub_8150E38_padding = 0;

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
