#ifndef GUARD_GRAPHICS_BLEND_TRANSITION_H
#define GUARD_GRAPHICS_BLEND_TRANSITION_H

#include "global.h"

struct GraphicsBlendTransition {
    u16 mode;
    u16 current;
    u16 target;
};

#define graphics_initialize_blend_transition_default sub_8134B64

void graphics_initialize_blend_transition_default(
    struct GraphicsBlendTransition* transition);

#endif
