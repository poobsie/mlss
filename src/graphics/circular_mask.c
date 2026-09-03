#include "graphics/circular_mask.h"

void circular_mask_set_radius(struct CircularMask* mask, u32 radius)
    __attribute__((section(".text.sub_8150DE8")));
void circular_mask_set_radius(struct CircularMask* mask, u32 radius) {
    mask->radius = radius;
}

u32 circular_mask_get_scale(struct CircularMask* mask)
    __attribute__((section(".text.sub_8150DEC")));
u32 circular_mask_get_scale(struct CircularMask* mask) {
    return mask->scale;
}

void circular_mask_clear_value_20(struct CircularMask* mask)
    __attribute__((section(".text.sub_81582C4")));
void circular_mask_clear_value_20(struct CircularMask* mask) {
    mask->value20 = 0;
}

__attribute__((section(".text.sub_81582C4")))
const u16 circular_mask_clear_value_20_padding = 0;

s32 circular_mask_get_value_1c(struct CircularMask* mask)
    __attribute__((section(".text.sub_8158308")));
s32 circular_mask_get_value_1c(struct CircularMask* mask) {
    return mask->value1C;
}

__attribute__((section(".text.sub_8158308")))
const u16 circular_mask_get_value_1c_padding = 0;

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
