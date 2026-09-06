#ifndef GUARD_FIELD_DISPLAY_VALUE_TRANSITION_H
#define GUARD_FIELD_DISPLAY_VALUE_TRANSITION_H

#include "global.h"

struct FieldDisplayValueVisual {
    u8 unknown00[0x12];
    u8 flags12;
};

struct FieldDisplayValueTransition {
    u8 unknown00[4];
    void (*callback)(struct FieldDisplayValueTransition* transition);
    struct FieldDisplayValueVisual* visual08;
    u8 unknown0C[4];
    s16 timer10;
    s16 unknown12;
    s16 step14;
    s16 value16;
};

#define field_draw_value_until_visual_finishes sub_8106A30
#define field_advance_scaled_step_sequence sub_8106A88
#define field_draw_value_then_push_callback_node sub_8107248

void field_draw_value_until_visual_finishes(
    struct FieldDisplayValueTransition* transition);
void field_advance_scaled_step_sequence(
    struct FieldDisplayValueTransition* transition);
void field_draw_value_then_push_callback_node(
    struct FieldDisplayValueTransition* transition);

#endif
