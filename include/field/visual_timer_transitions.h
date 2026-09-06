#ifndef GUARD_FIELD_VISUAL_TIMER_TRANSITIONS_H
#define GUARD_FIELD_VISUAL_TIMER_TRANSITIONS_H

#include "global.h"
#include "graphics/linked_visual.h"

struct FieldVisualTimerTransition {
    u8 unknown00[4];
    void (*callback)(struct FieldVisualTimerTransition* transition);
    struct GraphicsLinkedVisual* visual;
    u8 unknown0C[4];
    s16 timer10;
};

#define field_wait_deactivate_visual_then_continue_20 sub_8106840
#define field_wait_deactivate_visual_then_continue_10 sub_8106874

void field_wait_deactivate_visual_then_continue_20(
    struct FieldVisualTimerTransition* transition);
void field_wait_deactivate_visual_then_continue_10(
    struct FieldVisualTimerTransition* transition);

#endif
