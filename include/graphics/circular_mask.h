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
    u8 unknown14[8];
    s16 value1C;
    u8 unknown1E[2];
    u32 value20;
    u8 unknown24[8];
    u16 flags;
    u8 unknown2E[2];
    s32 radius;
    s32 scale;
};

#define circular_mask_set_radius sub_8150DE8
#define circular_mask_get_scale sub_8150DEC
#define circular_mask_clear_value_20 sub_81582C4
#define circular_mask_get_value_1c sub_8158308
#define circular_mask_disable sub_8150E2C
#define circular_mask_enable sub_8150E38

void circular_mask_set_radius(struct CircularMask* mask, u32 radius);
u32 circular_mask_get_scale(struct CircularMask* mask);
void circular_mask_clear_value_20(struct CircularMask* mask);
s32 circular_mask_get_value_1c(struct CircularMask* mask);
void circular_mask_disable(struct CircularMask* mask);
void circular_mask_enable(struct CircularMask* mask);

#endif
