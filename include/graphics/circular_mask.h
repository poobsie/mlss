#ifndef GUARD_GRAPHICS_CIRCULAR_MASK_H
#define GUARD_GRAPHICS_CIRCULAR_MASK_H

#include "global.h"

enum CircularMaskFlags {
    CIRCULAR_MASK_ENABLED = 1 << 0,
};

struct CircularMask {
    u16* scanlineBounds;
    s32 screenOffsetX;
    s32 screenOffsetY;
    s32 centerOffsetX;
    s32 centerOffsetY;
    u8 unknown14[0x18];
    u16 flags;
    u8 unknown2E[2];
    s32 radius;
};

#define circular_mask_disable sub_8150E2C
#define circular_mask_enable sub_8150E38

void circular_mask_disable(struct CircularMask* mask);
void circular_mask_enable(struct CircularMask* mask);

#endif
