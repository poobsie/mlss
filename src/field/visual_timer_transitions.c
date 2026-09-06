#include "field/visual_timer_transitions.h"

#define SEC(symbol) __attribute__((section(".text.field_visual_timer_transitions." #symbol)))

void sub_81067D4(struct FieldVisualTimerTransition* transition);
void sub_8105F28(struct FieldVisualTimerTransition* transition);

SEC(sub_8106840)
void field_wait_deactivate_visual_then_continue_20(
    struct FieldVisualTimerTransition* transition)
{
    if (transition->timer10 != 0) {
        transition->timer10--;
        return;
    }

    graphics_deactivate_linked_visual(transition->visual);
    transition->timer10 = 0x20;
    transition->callback = sub_81067D4;
    transition->callback(transition);
}

SEC(sub_8106874)
void field_wait_deactivate_visual_then_continue_10(
    struct FieldVisualTimerTransition* transition)
{
    if (transition->timer10 != 0) {
        transition->timer10--;
        return;
    }

    graphics_deactivate_linked_visual(transition->visual);
    transition->timer10 = 0x10;
    transition->callback = sub_8105F28;
    transition->callback(transition);
}
