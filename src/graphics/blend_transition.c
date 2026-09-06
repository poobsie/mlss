#include "graphics/blend_transition.h"

#define SEC(symbol) __attribute__((section(".text.middle." #symbol)))

enum {
    DEFAULT_BLEND_TRANSITION_TARGET = 0x10,
};

s32 sub_8134AA8(struct GraphicsBlendTransition* transition);
void free_heap_8018DA8(void* allocation);
extern u8 loc_8198220[];
extern u8 loc_819832C[];

typedef s32 (*GraphicsDivideFunction)(s32 dividend, s32 divisor);

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

SEC(sub_8134BD0)
s32 graphics_interpolate_blend_value(
    s32 start, s32 end, s32 duration, s32 step)
{
    GraphicsDivideFunction divide;

    if (duration <= 0)
        duration = 1;
    if (step < 0)
        step = 0;
    if (step >= duration)
        step = duration;

    divide = (GraphicsDivideFunction)(*(u8**)0x03001038
                                      + (loc_819832C - loc_8198220));
    return start + divide((end - start) * step, duration);
}
