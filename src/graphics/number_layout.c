#include "global.h"
#include "graphics/functions.h"

#define SEC(symbol) __attribute__((section(".text.middle." #symbol)))

enum {
    GRAPHICS_NIBBLE_ADVANCE = 4,
};

SEC(sub_810D260) u8* graphics_advance_by_nibble_width(u32 value, u8* base)
{
    int offset = 0;
    do {
        value >>= 4;
        offset += GRAPHICS_NIBBLE_ADVANCE;
    } while (value != 0);
    return base + offset;
}
