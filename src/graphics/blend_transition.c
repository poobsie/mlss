#include "graphics/blend_transition.h"

#define SEC(symbol) __attribute__((section(".text.middle." #symbol)))

enum {
    DEFAULT_BLEND_TRANSITION_TARGET = 0x10,
};

s32 sub_8134AA8(struct GraphicsBlendTransition* transition);
void free_heap_8018DA8(void* allocation);

SEC(sub_8134B24)
s32 graphics_blend_transition_is_complete(
    const struct GraphicsBlendTransition* transition)
{
    if (transition->current >= transition->target)
        return 1;
    return 0;
}

SEC(sub_8134B38)
void graphics_begin_blend_transition(
    struct GraphicsBlendTransition* transition, u16 mode, u16 target)
{
    if (mode > 3)
        mode = 3;
    transition->mode = mode;
    transition->current = 0;
    transition->target = target;
    if (target == 0) {
        transition->target = 1;
        sub_8134AA8(transition);
    }
}

SEC(sub_8134B64) void graphics_initialize_blend_transition_default(
    struct GraphicsBlendTransition* transition)
{
    transition->mode = 0;
    transition->current = 0;
    transition->target = DEFAULT_BLEND_TRANSITION_TARGET;
}

SEC(sub_8134B70)
void graphics_destroy_blend_transition(
    struct GraphicsBlendTransition* transition, u32 flags)
{
    transition->descriptor = (const void*)0x08CDC460;
    if (flags & 1)
        free_heap_8018DA8(transition);
}
