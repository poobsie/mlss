#include "global.h"
#include "field/actor.h"
#include "field/functions.h"

#define SEC(name) __attribute__((section(".text.actor_animation_transitions." #name)))

extern void sub_8082E1C(void *, s32, s32, s32);

#define DEFINE_ANIMATION_TRANSITION(name, animation, next)               \
    extern void next(void);                                              \
    SEC(name) void name(struct FieldAction *action)                      \
    {                                                                    \
        s32 mask;                                                        \
        s32 flag_value;                                                  \
        volatile u8 *flags;                                              \
        sub_8082E1C(action, animation, 0, 0);                            \
        flags = &action->visual->flags;                                 \
        flag_value = *flags;                                             \
        mask = -7;                                                       \
        flag_value &= mask;                                              \
        flag_value |= 2;                                                 \
        *flags = flag_value;                                             \
        action->update = next;                                          \
    }

DEFINE_ANIMATION_TRANSITION(field_start_animation_2_a, 2, sub_80DA4B8)
DEFINE_ANIMATION_TRANSITION(field_start_animation_13_a, 13, sub_80DD7F0)
DEFINE_ANIMATION_TRANSITION(field_start_animation_13_b, 13, sub_80DD878)
DEFINE_ANIMATION_TRANSITION(field_start_animation_9_a, 9, sub_80DD8C8)
DEFINE_ANIMATION_TRANSITION(field_start_animation_9_b, 9, sub_80DD944)
DEFINE_ANIMATION_TRANSITION(field_start_animation_10, 10, sub_80DEDEC)
DEFINE_ANIMATION_TRANSITION(field_start_animation_2_b, 2, sub_81100B0)
