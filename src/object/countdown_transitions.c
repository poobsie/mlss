#include "global.h"
#include "object/functions.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.countdown_transitions." #name)))
#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define MISC3_SEC(name) \
    __attribute__((section(".text.misc_helpers_03." STRINGIFY(name))))

extern void sub_8082E1C(struct RuntimeObject*, s32, s32, s32);

#define DEFINE_COUNTDOWN_TRANSITION(name, kind, next)                   \
    extern void next(struct RuntimeObject*);                             \
    SEC(name) void name(struct RuntimeObject* object)                    \
    {                                                                    \
        s32 current;                                                     \
        if (object->visual->flags & 8) {                                \
            current = (u16)object->timer - 1;                            \
            object->timer = current;                                    \
            if ((s32)(current << 16) <= 0) {                            \
                sub_8082E1C(object, kind, 0, 0);                        \
                object->update = next;                                  \
            }                                                            \
        }                                                                \
    }

DEFINE_COUNTDOWN_TRANSITION(sub_805DF4C, 5, sub_805DA78)
DEFINE_COUNTDOWN_TRANSITION(sub_8063C8C, 13, sub_8063C60)
DEFINE_COUNTDOWN_TRANSITION(sub_806EADC, 11, sub_808750C)

extern void sub_808AA60(struct RuntimeObject*);
extern void sub_808A8F8(struct RuntimeObject*);
extern void sub_808A7B0(struct RuntimeObject*);
extern void sub_808A660(struct RuntimeObject*);
extern void sub_808A4D0(struct RuntimeObject*);
extern void sub_808A3C4(struct RuntimeObject*);
extern void sub_808A27C(struct RuntimeObject*);

#define DEFINE_PREDECREMENT_TIMER_TRANSITION(name, animation, next)          \
    MISC3_SEC(name) void name(struct RuntimeObject* object)                  \
    {                                                                        \
        u16 current = object->timer;                                         \
        object->timer = current - 1;                                         \
        if ((s32)(current << 16) <= 0) {                                    \
            sub_8082E1C(object, animation, 0, 0);                            \
            object->update = next;                                          \
        }                                                                    \
    }

DEFINE_PREDECREMENT_TIMER_TRANSITION(object_countdown_then_animation_8_variant_a,
                                     8, sub_808AA60)
DEFINE_PREDECREMENT_TIMER_TRANSITION(object_countdown_then_animation_4_variant_a,
                                     4, sub_808A8F8)
DEFINE_PREDECREMENT_TIMER_TRANSITION(object_countdown_then_animation_8_variant_b,
                                     8, sub_808A7B0)
DEFINE_PREDECREMENT_TIMER_TRANSITION(object_countdown_then_animation_4_variant_b,
                                     4, sub_808A660)
DEFINE_PREDECREMENT_TIMER_TRANSITION(object_countdown_then_animation_9_variant_a,
                                     9, sub_808A4D0)
DEFINE_PREDECREMENT_TIMER_TRANSITION(object_countdown_then_animation_5_variant_a,
                                     5, sub_808A3C4)
DEFINE_PREDECREMENT_TIMER_TRANSITION(object_countdown_then_animation_5_variant_b,
                                     5, sub_808A27C)
