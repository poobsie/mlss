#include "graphics/circular_mask.h"

void circular_mask_disable(struct CircularMask* mask)
    __attribute__((section(".text.state_field_helpers.sub_8150E2C")));
void circular_mask_disable(struct CircularMask* mask) {
    s32 value = mask->flags;
    s32 clearEnabled = ~CIRCULAR_MASK_ENABLED;
    clearEnabled &= value;
    mask->flags = clearEnabled;
}

void circular_mask_enable(struct CircularMask* mask)
    __attribute__((section(".text.state_field_helpers.sub_8150E38")));
void circular_mask_enable(struct CircularMask* mask) {
    s32 value = mask->flags;
    s32 enabled = CIRCULAR_MASK_ENABLED;
    enabled |= value;
    mask->flags = enabled;
}

__attribute__((section(".text.state_field_helpers.sub_8150E38")))
const u16 circular_mask_enable_padding = 0;
