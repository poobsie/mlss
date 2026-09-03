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
void sub_80605A4(struct RuntimeObject* object);
void sub_80613FC(struct RuntimeObject* object);
void sub_8070C5C(struct RuntimeObject* object);
void sub_807197C(struct RuntimeObject* object);
void sub_805DEB4(struct RuntimeObject* object);
void sub_8063C24(struct RuntimeObject* object);
void sub_806A8B0(struct RuntimeObject* object);
void sub_8072BE8(struct RuntimeObject* object);
void sub_80DB014(struct RuntimeObject* object);
s32 sub_8086C64();
s32 sub_8082B00(void);
s32 sub_8087124(void* state);
void sub_80D9F34(void* state);
void sub_807C298(struct RuntimeObject* object);

#define SEC(symbol) __attribute__((section(".text.small_functions_01." #symbol)))
#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define MISC_SEC(symbol) \
    __attribute__((section(".text.misc_helpers_01." STRINGIFY(symbol))))
#define MISC2_SEC(symbol) \
    __attribute__((section(".text.misc_helpers_02." STRINGIFY(symbol))))

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

#define DEFINE_VALUE80_ANIMATION(name, animation, next)                \
    MISC2_SEC(name) void name(struct RuntimeObject* object)             \
    {                                                                   \
        if (object->value80 == 0) {                                    \
            sub_8082E1C(object, animation, 0, 0);                     \
            object->update = next;                                     \
        }                                                               \
    }

DEFINE_VALUE80_ANIMATION(
    object_when_value80_clear_start_animation_4, 4, sub_80605A4)
DEFINE_VALUE80_ANIMATION(
    object_when_value80_clear_start_animation_9, 9, sub_808750C)
DEFINE_VALUE80_ANIMATION(
    object_when_value80_clear_start_animation_7, 7, sub_80613FC)
DEFINE_VALUE80_ANIMATION(
    object_when_value80_clear_start_animation_0, 0, sub_808750C)
DEFINE_VALUE80_ANIMATION(
    object_when_value80_clear_start_animation_18, 0x18, sub_8070C5C)
DEFINE_VALUE80_ANIMATION(
    object_when_value80_clear_start_animation_16, 0x16, sub_807197C)

MISC2_SEC(object_when_value80_clear_start_animation_0_and_stop)
void object_when_value80_clear_start_animation_0_and_stop(
    struct RuntimeObject* object)
{
    s32 value;

    value = object->value80;
    if (value == 0) {
        sub_8082E1C(object, 0, 0, 0);
        object->update = (RuntimeObjectCallback)value;
    }
}

MISC2_SEC(object_when_value80_clear_stop_sound_11b)
void object_when_value80_clear_stop_sound_11b(struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        object->update = sub_805DEB4;
        sound_effect_stop(0x11B);
    }
}

MISC2_SEC(object_move_x_by_behavior_until_value84)
void object_move_x_by_behavior_until_value84(struct RuntimeObject* object)
{
    s32 position;

    position = object->currentPositionX - object->behaviorState;
    object->currentPositionX = position;
    if (position <= object->value84)
        sub_807C298(object);
}
MISC2_SEC(object_move_x_by_behavior_until_value84)
const u16 object_move_x_by_behavior_until_value84_padding = 0;

MISC2_SEC(object_when_value80_clear_delay_255)
void object_when_value80_clear_delay_255(struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        sound_effect_stop(0x81);
        object->timer = 0xFF;
        object->update = sub_806A8B0;
    }
}

MISC2_SEC(object_when_setup_ready_delay_value84_16)
s32 object_when_setup_ready_delay_value84_16(struct RuntimeObject* object)
{
    s32 result;

    result = sub_8086C64();
    if (result == 0) {
        object->update = sub_8063C24;
        object->value84 = 0x10;
    }
    return result;
}

MISC2_SEC(object_when_value80_clear_play_sound_10e)
void object_when_value80_clear_play_sound_10e(struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        sound_effect_play(0x10E, SOUND_VOLUME_UNCHANGED);
        object->update = sub_8072BE8;
    }
}

MISC2_SEC(object_move_right_until_past_screen)
void object_move_right_until_past_screen(struct RuntimeObject* object)
{
    s32 previous;
    s32 position;

    previous = object->currentPositionX;
    position = previous + 0x200;
    object->currentPositionX = position;
    if (position < 0)
        position = previous + 0x2FF;
    if ((position >> 8) > 0xFF)
        sub_807C298(object);
}
MISC2_SEC(object_move_right_until_past_screen)
const u16 object_move_right_until_past_screen_padding = 0;

MISC2_SEC(object_when_field_ready_play_sound_8d)
void object_when_field_ready_play_sound_8d(struct RuntimeObject* object)
{
    if (sub_8082B00() == 0) {
        sound_effect_play(0x8D, SOUND_VOLUME_UNCHANGED);
        object->update = sub_80DB014;
    }
}

MISC2_SEC(object_update_state_subobject)
s32 object_update_state_subobject(struct RuntimeObject* object)
{
    s32 result;
    void* stateSubobject;

    stateSubobject = (u8*)object->state + 8;
    result = sub_8087124(stateSubobject);
    if (result == 0)
        sub_80D9F34(stateSubobject);
    return result;
}
MISC2_SEC(object_update_state_subobject)
const u16 object_update_state_subobject_padding = 0;
