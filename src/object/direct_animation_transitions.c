#include "audio/sound_effects.h"
#include "object/functions.h"
#include "object/runtime_object.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(name) \
    __attribute__((section(".text.misc_helpers_02." STRINGIFY(name))))

void sub_8065494(struct RuntimeObject* object);
void sub_8071080(struct RuntimeObject* object);
void sub_80758BC(struct RuntimeObject* object);
void sub_8082E1C(
    struct RuntimeObject* object, s32 animation, s32 command, s32 argument);
void sub_808A5DC(struct RuntimeObject* object);
void sub_8111234(struct RuntimeObject* object);

SEC(object_start_animation_2_set_visual_parameter_16)
void object_start_animation_2_set_visual_parameter_16(
    struct RuntimeObject* object)
{
    sub_8082E1C(object, 2, 0, 0);
    object->visual->parameter20 = 0x10;
    object->update = sub_8065494;
}

SEC(object_reset_and_start_animation_2)
void object_reset_and_start_animation_2(struct RuntimeObject* object)
{
    object->value80 = 0;
    object->timer = 0;
    sub_8082E1C(object, 2, 0, 0);
    object->update = sub_808A5DC;
}

#define DEFINE_ANIMATION_SOUND(name, animation, sound, next)           \
    SEC(name) void name(struct RuntimeObject* object)                   \
    {                                                                   \
        sub_8082E1C(object, animation, 0, 0);                          \
        object->update = next;                                         \
        sound_effect_play(sound, SOUND_VOLUME_UNCHANGED);              \
    }

DEFINE_ANIMATION_SOUND(object_start_animation_10_sound_af, 0xA, 0xAF, sub_80758BC)
DEFINE_ANIMATION_SOUND(object_start_animation_9_sound_86, 9, 0x86, sub_8111234)

SEC(object_start_animation_5_sound_46)
void object_start_animation_5_sound_46(struct RuntimeObject* object)
{
    sub_8082E1C(object, 5, 0, 0);
    sound_effect_play(0x46, SOUND_VOLUME_UNCHANGED);
    object->update = sub_8071080;
}
