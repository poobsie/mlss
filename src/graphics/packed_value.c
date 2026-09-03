#include "global.h"
#include "graphics/functions.h"

#define SEC(symbol) __attribute__((section(".text.middle." #symbol)))

#define GRAPHICS_PACKED_VALUE_MODE (*(vu16*)0x02000008)

SEC(sub_8127E38) u32 graphics_extract_mode_relative_index(u32 value)
{
    return (value - ((GRAPHICS_PACKED_VALUE_MODE & 0xC) << 12)) << 17 >> 22;
}
