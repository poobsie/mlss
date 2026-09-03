#include "object/functions.h"
#include "object/runtime_object.h"
#include "audio/sound_effects.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SECTION(name) \
    __attribute__((section(".text.text_late_helpers." STRINGIFY(name))))
void sub_8082E1C(struct RuntimeObject* object, u32 command, u32 arg2, u32 arg3);
int sub_8082B00(struct RuntimeObject* object);
void sub_808750C(struct RuntimeObject* object);
void sub_8132E34(struct RuntimeObject* object);
void sub_8132E68(struct RuntimeObject* object);
void sub_8132EA8(struct RuntimeObject* object);
void sub_8133424(struct RuntimeObject* object);
void sub_8133BC0(struct RuntimeObject* object);
void sub_8133C7C(struct RuntimeObject* object);

SECTION(object_on_visual_complete_command_0_and_continue)
void object_on_visual_complete_command_0_and_continue(struct RuntimeObject* object) {
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 0, 0, 0);
        object->update = sub_808750C;
    }
}

SECTION(object_on_visual_complete_command_0_and_stop)
void object_on_visual_complete_command_0_and_stop(struct RuntimeObject* object) {
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 0, 0, 0);
        object->update = 0;
    }
}

__attribute__((section(".text.text_late_helpers.sub_8132D78")))
const u16 object_command_0_and_stop_padding = 0;

SECTION(object_on_visual_complete_command_13_and_continue)
void object_on_visual_complete_command_13_and_continue(struct RuntimeObject* object) {
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 13, 0, 0);
        object->update = sub_808750C;
    }
}

SECTION(object_when_value80_clear_command_10)
void object_when_value80_clear_command_10(struct RuntimeObject* object) {
    if (object->value80 == 0) {
        sub_8082E1C(object, 10, 0, 0);
        object->update = sub_8133C7C;
    }
}

extern void sub_80DBFBC(struct RuntimeObject* object);

SECTION(object_when_value80_clear_start_animation_5)
void object_when_value80_clear_start_animation_5(struct RuntimeObject* object) {
    if (object->value80 == 0) {
        sub_8082E1C(object, 5, 0, 0);
        sound_effect_play(0x84, SOUND_VOLUME_UNCHANGED);
        object->timer = 0x20;
        object->update = sub_80DBFBC;
    }
}

#define DEFINE_READY_ANIMATION_TRANSITION(name, animation, next)        \
    SECTION(name) void name(struct RuntimeObject* object)               \
    {                                                                    \
        if (sub_8082B00(object) == 0) {                                 \
            sub_8082E1C(object, animation, 0, 0);                       \
            object->update = next;                                      \
        }                                                                \
    }

DEFINE_READY_ANIMATION_TRANSITION(
    object_when_ready_start_animation_8, 8, sub_8132E34)
DEFINE_READY_ANIMATION_TRANSITION(
    object_when_ready_start_animation_4_upper, 4, sub_8132E68)
DEFINE_READY_ANIMATION_TRANSITION(
    object_when_ready_start_animation_2_upper, 2, sub_8133424)

SECTION(object_on_visual_complete_start_animation_9_delay_60)
void object_on_visual_complete_start_animation_9_delay_60(
    struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 9, 0, 0);
        object->timer = 0x3C;
        object->update = sub_8132EA8;
    }
}

SECTION(object_when_linked_object_clear_start_animation_13)
void object_when_linked_object_clear_start_animation_13(
    struct RuntimeObject* object)
{
    if (object->linkedObject == 0) {
        sub_8082E1C(object, 0x0D, 0, 0);
        object->update = sub_808750C;
    }
}

SECTION(object_decelerate_vertical_step_then_start_animation_12)
void object_decelerate_vertical_step_then_start_animation_12(
    struct RuntimeObject* object)
{
    object->verticalPosition += object->value8C;
    object->value8C -= object->verticalAcceleration;
    if (object->value8C <= 0) {
        object->verticalPosition += 0x1000;
        object->valueA4 = 0x0C;
        object->valueA8 = 0;
        sub_8082E1C(object, 0x0C, 0, 0);
        sound_effect_play(0xD5, SOUND_VOLUME_UNCHANGED);
        object->update = sub_8133BC0;
    }
}
