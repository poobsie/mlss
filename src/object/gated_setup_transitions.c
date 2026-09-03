#include "audio/sound_effects.h"
#include "object/functions.h"
#include "object/runtime_object.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(symbol) \
    __attribute__((section(".text.misc_helpers_03." STRINGIFY(symbol))))

s32 sub_8082B00(void);
void sub_8082E1C(
    struct RuntimeObject* object, s32 animation, s32 command, s32 argument);
void sub_8060404(struct RuntimeObject* object);
void sub_8060438(struct RuntimeObject* object);
void sub_8060A58(struct RuntimeObject* object);
void sub_8065510(struct RuntimeObject* object);
void sub_8068AA8(struct RuntimeObject* object);
void sub_806CBCC(struct RuntimeObject* object);
void sub_806CED0(struct RuntimeObject* object);
void sub_80DABFC(struct RuntimeObject* object);
void sub_80DC638(struct RuntimeObject* object);

SEC(object_when_value80_clear_stop_sound_5c_variant_a)
void object_when_value80_clear_stop_sound_5c_variant_a(
    struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        sound_effect_stop(0x5C);
        sub_8082E1C(object, 4, 0, 0);
        object->update = sub_8060404;
    }
}

SEC(object_when_value80_clear_stop_sound_5c_variant_b)
void object_when_value80_clear_stop_sound_5c_variant_b(
    struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        sound_effect_stop(0x5C);
        sub_8082E1C(object, 4, 0, 0);
        object->update = sub_8060438;
    }
}

SEC(object_start_animation_2_values_84_8c_variant_a)
void object_start_animation_2_values_84_8c_variant_a(
    struct RuntimeObject* object)
{
    sub_8082E1C(object, 2, 0, 0);
    object->value84 = 0x300;
    object->value8C = 0x33;
    object->update = sub_806CED0;
}

SEC(object_start_animation_2_values_84_8c_variant_b)
void object_start_animation_2_values_84_8c_variant_b(
    struct RuntimeObject* object)
{
    sub_8082E1C(object, 2, 0, 0);
    object->value84 = 0x300;
    object->value8C = 0x33;
    object->update = sub_806CBCC;
}

#define DEFINE_VALUE80_TIMED_TRANSITION(name, animation, duration, next)     \
    SEC(name) void name(struct RuntimeObject* object)                        \
    {                                                                        \
        if (object->value80 == 0) {                                         \
            sub_8082E1C(object, animation, 0, 0);                            \
            object->timer = duration;                                       \
            object->update = next;                                          \
        }                                                                    \
    }

DEFINE_VALUE80_TIMED_TRANSITION(object_when_value80_clear_animation_5_delay_2,
                                5, 2, sub_8060A58)
DEFINE_VALUE80_TIMED_TRANSITION(object_when_value80_clear_animation_3_delay_24,
                                3, 0x18, sub_80DABFC)
DEFINE_VALUE80_TIMED_TRANSITION(object_when_value80_clear_animation_7_delay_32,
                                7, 0x20, sub_80DC638)

SEC(object_when_value80_clear_animation_4_then_stop_sound_81)
void object_when_value80_clear_animation_4_then_stop_sound_81(
    struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        sub_8082E1C(object, 4, 0, 0);
        object->update = sub_8065510;
        sound_effect_stop(0x81);
    }
}

SEC(object_when_ready_animation_2_set_value8c_300)
void object_when_ready_animation_2_set_value8c_300(
    struct RuntimeObject* object)
{
    if (sub_8082B00() == 0) {
        sub_8082E1C(object, 2, 0, 0);
        object->value8C = 0x300;
        object->update = sub_8068AA8;
    }
}
