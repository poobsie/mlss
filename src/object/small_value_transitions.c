#include "audio/sound_effects.h"
#include "object/small_value_transitions.h"

void sub_806E98C(struct RuntimeObject* object);
void sub_806F90C(struct RuntimeObject* object);
void sub_806FCF0(struct RuntimeObject* object);
void sub_807F4FC(struct RuntimeObject* object);
void sub_8082E1C(struct RuntimeObject* object, s32 animation, s32 command, s32 argument);
void sub_80873B8(struct RuntimeObject* object, s32 value, s32 argument);
void sub_808750C(struct RuntimeObject* object);
void sub_808C868(struct RuntimeObject* object);
void sub_8065EA0(struct RuntimeObject* object);
void sub_8065ED4(struct RuntimeObject* object);
void sub_8067A4C(struct RuntimeObject* object);
void sub_806A2FC(struct RuntimeObject* object);
void sub_806B7BC(struct RuntimeObject* object);
void sub_8071B14(struct RuntimeObject* object);
void sub_807940C(struct RuntimeObject* object);
void sub_808942C(struct RuntimeObject* object);
void sub_809EA4C(struct RuntimeObject* object);
void sub_80DA480(struct RuntimeObject* object);
void sub_8110034(struct RuntimeObject* object);

#define SEC(symbol) __attribute__((section(".text.small_functions_01." #symbol)))
#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define MISC_SEC(symbol) \
    __attribute__((section(".text.misc_helpers_01." STRINGIFY(symbol))))

SEC(sub_806E794)
void object_when_value80_clear_start_paired_animation_5(struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        sound_effect_stop(0x6C);
        sub_8082E1C(object, 5, 0, 0);
        sub_8082E1C(object->linkedObject, 5, 0, 0);
        object->update = sub_806E98C;
    }
}

SEC(sub_8070F98)
void object_when_value80_clear_start_animation_16_delay_4(struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        sound_effect_stop(0x11C);
        sub_8082E1C(object, 0x16, 0, 0);
        object->timer = 4;
        object->update = sub_806F90C;
    }
}

SEC(sub_807116C)
void object_when_value80_clear_start_animation_25(struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        sound_effect_stop(0x11C);
        object->value8C = 0x14;
        sub_8082E1C(object, 0x25, 0, 0);
        object->update = sub_806FCF0;
    }
}

SEC(sub_808C6EC)
void object_when_value80_clear_prepare_followup_after_18(struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        sound_effect_stop(0x81);
        sub_807F4FC(object);
        object->timer = 0x18;
        sub_80873B8(object, 3, 0);
        object->followup = sub_808C868;
    }
}

MISC_SEC(object_count_down_value_a0_then_idle)
void object_count_down_value_a0_then_idle(struct RuntimeObject* object)
{
    s32 value;

    value = object->valueA0 - 1;
    object->valueA0 = value;
    if (value < 0)
        object->update = sub_808750C;
}

#define DEFINE_VALUE80_DELAY(name, duration, next)                     \
    MISC_SEC(name) void name(struct RuntimeObject* object)              \
    {                                                                   \
        if (object->value80 == 0) {                                    \
            object->timer = duration;                                  \
            object->update = next;                                     \
        }                                                               \
    }

DEFINE_VALUE80_DELAY(object_when_value80_clear_delay_20, 20, sub_8065EA0)

MISC_SEC(object_on_visual_complete_install_update)
void object_on_visual_complete_install_update(struct RuntimeObject* object)
{
    if (object->visual->flags & 8)
        object->update = sub_8065ED4;
}

MISC_SEC(object_count_down_value84_then_begin_motion)
void object_count_down_value84_then_begin_motion(struct RuntimeObject* object)
{
    s32 value;

    value = object->value84 - 1;
    object->value84 = value;
    if (value <= 0) {
        object->value8C = 0x300;
        object->update = sub_8067A4C;
    }
}

DEFINE_VALUE80_DELAY(object_when_value80_clear_delay_12, 12, sub_806A2FC)

#define DEFINE_LOWER_TO_IDLE(name)                                    \
    MISC_SEC(name) void name(struct RuntimeObject* object)              \
    {                                                                   \
        s32 position;                                                   \
        position = object->verticalPosition - 0x200;                   \
        object->verticalPosition = position;                           \
        if (position <= 0) {                                           \
            object->verticalPosition = 0;                              \
            object->update = sub_808750C;                              \
        }                                                               \
    }

DEFINE_LOWER_TO_IDLE(object_lower_vertical_position_then_idle_a)
DEFINE_VALUE80_DELAY(object_when_value80_clear_delay_8, 8, sub_806B7BC)
DEFINE_VALUE80_DELAY(object_when_value80_clear_delay_30, 30, sub_8071B14)

MISC_SEC(object_when_value80_clear_install_update)
void object_when_value80_clear_install_update(struct RuntimeObject* object)
{
    if (object->value80 == 0)
        object->update = sub_807940C;
}

#define DEFINE_RESET_AND_INSTALL(name, next)                           \
    MISC_SEC(name) void name(struct RuntimeObject* object)              \
    {                                                                   \
        object->value80 = 0;                                           \
        object->update = next;                                         \
        object->timer = 0;                                             \
    }

DEFINE_RESET_AND_INSTALL(
    object_reset_value80_timer_and_install_update_a, sub_808942C)
DEFINE_RESET_AND_INSTALL(
    object_reset_value80_timer_and_install_update_b, sub_809EA4C)

MISC_SEC(object_on_visual_complete_reset_timer)
void object_on_visual_complete_reset_timer(struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        object->timer = 0;
        object->update = sub_80DA480;
    }
}

MISC_SEC(object_on_visual_complete_delay_12)
void object_on_visual_complete_delay_12(struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        object->timer = 12;
        object->update = sub_8110034;
    }
}

DEFINE_LOWER_TO_IDLE(object_lower_vertical_position_then_idle_b)
