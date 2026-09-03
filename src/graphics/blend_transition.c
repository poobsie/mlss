#include "graphics/blend_transition.h"

#define SEC(symbol) __attribute__((section(".text.middle." #symbol)))

enum {
    DEFAULT_BLEND_TRANSITION_TARGET = 0x10,
};

SEC(sub_8134B64) void graphics_initialize_blend_transition_default(
    struct GraphicsBlendTransition* transition)
{
    transition->mode = 0;
    transition->current = 0;
    transition->target = DEFAULT_BLEND_TRANSITION_TARGET;
}
