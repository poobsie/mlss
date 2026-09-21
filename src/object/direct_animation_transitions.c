#include "audio/sound_effects.h"
#include "object/functions.h"
#include "object/runtime_leaf_callbacks.h"
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
void sub_807F47C(struct RuntimeObject* object);
void sub_8085B38(struct RuntimeObject* object);
void sub_808750C(struct RuntimeObject* object);
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
    object->update =
        object_after_nonpositive_countdown_begin_forward_motion_3000;
}

SEC(sub_808A5DC)
void object_after_nonpositive_countdown_begin_forward_motion_3000(
    struct RuntimeObject* object)
{
    u32 timer;
    s32 value80 = object->value80;

    if (value80 == 0) {
        timer = *(u16 *)(void *)&object->timer - 1;
        object->timer = timer;
        if ((s32)((u32)timer << 16) <= 0) {
            sub_807F47C(object);
            object->value84 = object->positionX + 0x3000;
            object->value88 = object->positionY;
            object->value8C = object->positionZBase;
            {
                s32 flagValue = object->flags79;
                s32 mask = 0x20;
                flagValue |= mask;
                object->flags79 = flagValue;
            }
            object->unknown7C = 0x600;
            object->unknown7A = value80;
            sub_8085B38(object);
            sub_8082E1C(object, 2, 0, 0);
            {
                s32 mask;
                s32 flagValue;
                volatile u8 *visualFlags;
                visualFlags = &object->visual->flags;
                flagValue = *visualFlags;
                mask = -7;
                flagValue &= mask;
                *visualFlags = flagValue;
            }
            object->update = sub_808750C;
        }
    }
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
