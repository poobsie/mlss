#include "object/functions.h"
#include "object/runtime_object.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(symbol) \
    __attribute__((section(".text.misc_helpers_03." STRINGIFY(symbol))))

void sub_8082E1C(
    struct RuntimeObject* object, s32 animation, s32 command, s32 argument);

void sub_805DF88(struct RuntimeObject* object);
void sub_80602B4(struct RuntimeObject* object);
void sub_8061DA8(struct RuntimeObject* object);
void sub_806259C(struct RuntimeObject* object);
void sub_806688C(struct RuntimeObject* object);
void sub_806C454(struct RuntimeObject* object);
void sub_8070DCC(struct RuntimeObject* object);
void sub_80712D8(struct RuntimeObject* object);
void sub_80874B4(struct RuntimeObject* object);
void sub_808750C(struct RuntimeObject* object);
void sub_8095548(struct RuntimeObject* object);
void sub_8099BE4(struct RuntimeObject* object);
void sub_809A120(struct RuntimeObject* object);
void sub_809A14C(struct RuntimeObject* object);
void sub_8111848(struct RuntimeObject* object);

#define DEFINE_VISUAL_TRANSITION(name, animation, continuation)              \
    SEC(name) void name(struct RuntimeObject* object)                         \
    {                                                                         \
        if (object->visual->flags & 8) {                                      \
            sub_8082E1C(object, animation, 0, 0);                             \
            object->update = continuation;                                   \
        }                                                                     \
    }

DEFINE_VISUAL_TRANSITION(object_on_visual_complete_animation_4_variant_a,
                         4, sub_805DF88)
DEFINE_VISUAL_TRANSITION(object_on_visual_complete_animation_2_variant_a,
                         2, sub_80602B4)
DEFINE_VISUAL_TRANSITION(object_on_visual_complete_animation_0_variant_a,
                         0, sub_8061DA8)
DEFINE_VISUAL_TRANSITION(object_on_visual_complete_animation_0_then_idle_a,
                         0, sub_808750C)
DEFINE_VISUAL_TRANSITION(object_on_visual_complete_animation_11_variant_a,
                         0xB, sub_806259C)
DEFINE_VISUAL_TRANSITION(object_on_visual_complete_animation_0_variant_b,
                         0, sub_80874B4)
DEFINE_VISUAL_TRANSITION(object_on_visual_complete_animation_11_then_idle_a,
                         0xB, sub_808750C)
DEFINE_VISUAL_TRANSITION(object_on_visual_complete_animation_7_variant_a,
                         7, sub_806688C)
DEFINE_VISUAL_TRANSITION(object_on_visual_complete_animation_11_then_idle_b,
                         0xB, sub_808750C)
DEFINE_VISUAL_TRANSITION(object_on_visual_complete_animation_9_then_idle_a,
                         9, sub_808750C)
DEFINE_VISUAL_TRANSITION(object_on_visual_complete_animation_21_variant_a,
                         0x15, sub_806C454)
DEFINE_VISUAL_TRANSITION(object_on_visual_complete_animation_5_variant_a,
                         5, sub_8070DCC)
DEFINE_VISUAL_TRANSITION(object_on_visual_complete_animation_21_variant_b,
                         0x15, sub_80712D8)
DEFINE_VISUAL_TRANSITION(object_on_visual_complete_animation_8_variant_a,
                         8, sub_8095548)
DEFINE_VISUAL_TRANSITION(object_on_visual_complete_animation_8_variant_b,
                         8, sub_809A120)
DEFINE_VISUAL_TRANSITION(object_on_visual_complete_animation_9_variant_a,
                         9, sub_809A14C)
DEFINE_VISUAL_TRANSITION(object_on_visual_complete_animation_10_variant_a,
                         0xA, sub_8099BE4)
DEFINE_VISUAL_TRANSITION(object_on_visual_complete_animation_14_variant_a,
                         0xE, sub_8111848)
