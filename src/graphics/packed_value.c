#include "global.h"
#include "graphics/functions.h"

#define SEC(symbol) __attribute__((section(".text.middle." #symbol)))
#define SEC_SMALL(symbol) __attribute__((section(".text.small_functions_01." #symbol)))

#define GRAPHICS_PACKED_VALUE_MODE (*(vu16*)0x02000008)

struct GraphicsPackedValueSource {
    u8 unknown000[0x188];
    u16* mode188;
};

struct GraphicsPackedValueOwner {
    u8 unknown00[4];
    struct GraphicsPackedValueSource* source04;
};

SEC_SMALL(sub_80E8F1C)
u32 graphics_extract_owner_mode_relative_index(
    struct GraphicsPackedValueOwner* owner,
    s32 value)
{
    return (u32)((value - ((*owner->source04->mode188 & 0xC) << 12)) << 16) >> 21;
}

SEC(sub_8127E38) u32 graphics_extract_mode_relative_index(u32 value)
{
    return (value - ((GRAPHICS_PACKED_VALUE_MODE & 0xC) << 12)) << 17 >> 22;
}
