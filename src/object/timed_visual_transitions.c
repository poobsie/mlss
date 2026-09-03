#include "object/functions.h"
#include "object/runtime_object.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(symbol) \
    __attribute__((section(".text.misc_helpers_03." STRINGIFY(symbol))))

void sub_8082E1C(
    struct RuntimeObject* object, s32 animation, s32 command, s32 argument);
void sub_8060500(struct RuntimeObject* object);
void sub_8060694(struct RuntimeObject* object);
void sub_8063AD4(struct RuntimeObject* object);
void sub_806E414(struct RuntimeObject* object);
void sub_806EADC(struct RuntimeObject* object);
void sub_80700C8(struct RuntimeObject* object);
void sub_806FBD0(struct RuntimeObject* object);

#define DEFINE_TIMED_VISUAL_TRANSITION(name, animation, duration, next)      \
    SEC(name) void name(struct RuntimeObject* object)                        \
    {                                                                        \
        if (object->visual->flags & 8) {                                     \
            sub_8082E1C(object, animation, 0, 0);                            \
            object->timer = duration;                                       \
            object->update = next;                                          \
        }                                                                    \
    }

DEFINE_TIMED_VISUAL_TRANSITION(object_on_visual_complete_animation_12_delay_8,
                               0xC, 8, sub_8060500)
DEFINE_TIMED_VISUAL_TRANSITION(object_on_visual_complete_animation_6_delay_1,
                               6, 1, sub_8060694)
DEFINE_TIMED_VISUAL_TRANSITION(object_on_visual_complete_animation_10_delay_3,
                               0xA, 3, sub_8063AD4)
DEFINE_TIMED_VISUAL_TRANSITION(object_on_visual_complete_animation_5_delay_10,
                               5, 0xA, sub_806E414)
DEFINE_TIMED_VISUAL_TRANSITION(object_on_visual_complete_animation_10_delay_60,
                               0xA, 0x3C, sub_806EADC)
DEFINE_TIMED_VISUAL_TRANSITION(object_on_visual_complete_animation_39_delay_1,
                               0x27, 1, sub_80700C8)
DEFINE_TIMED_VISUAL_TRANSITION(object_on_visual_complete_animation_29_delay_5,
                               0x1D, 5, sub_806FBD0)
