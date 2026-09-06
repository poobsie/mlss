#ifndef GUARD_FIELD_ALTERNATE_VISUAL_TRANSITION_H
#define GUARD_FIELD_ALTERNATE_VISUAL_TRANSITION_H

#include "global.h"

struct FieldAlternateVisualTransition {
    u8 unknown00[4];
    void (*callback)(struct FieldAlternateVisualTransition* transition);
};

#define field_continue_when_alternate_visual_finishes sub_8106FFC

void field_continue_when_alternate_visual_finishes(
    struct FieldAlternateVisualTransition* transition);

#endif
