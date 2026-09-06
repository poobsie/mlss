#ifndef GUARD_GRAPHICS_BLEND_TRANSITION_H
#define GUARD_GRAPHICS_BLEND_TRANSITION_H

#include "global.h"

struct GraphicsBlendTransition {
    u16 mode;
    u16 current;
    u16 target;
    u8 unknown06[2];
    const void* descriptor;
};

#define graphics_initialize_blend_transition_default sub_8134B64
#define graphics_blend_transition_is_complete sub_8134B24
#define graphics_begin_blend_transition sub_8134B38
#define graphics_destroy_blend_transition sub_8134B70
#define graphics_interpolate_blend_value sub_8134BD0

void graphics_initialize_blend_transition_default(
    struct GraphicsBlendTransition* transition);
s32 graphics_blend_transition_is_complete(
    const struct GraphicsBlendTransition* transition);
void graphics_begin_blend_transition(
    struct GraphicsBlendTransition* transition, u16 mode, u16 target);
void graphics_destroy_blend_transition(
    struct GraphicsBlendTransition* transition, u32 flags);
s32 graphics_interpolate_blend_value(
    s32 start, s32 end, s32 duration, s32 step);

#endif
