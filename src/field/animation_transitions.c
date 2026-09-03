#include "global.h"
#include "field/actor.h"

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

DEFINE_ANIMATION_TRANSITION(sub_80DABD0, 2, sub_80DA4B8)
DEFINE_ANIMATION_TRANSITION(sub_80DD740, 13, sub_80DD7F0)
DEFINE_ANIMATION_TRANSITION(sub_80DD76C, 13, sub_80DD878)
DEFINE_ANIMATION_TRANSITION(sub_80DD798, 9, sub_80DD8C8)
DEFINE_ANIMATION_TRANSITION(sub_80DD7C4, 9, sub_80DD944)
DEFINE_ANIMATION_TRANSITION(sub_80DED84, 10, sub_80DEDEC)
DEFINE_ANIMATION_TRANSITION(sub_810FF4C, 2, sub_81100B0)
