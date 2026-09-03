#include "audio/sound_effects.h"
#include "object/small_state_helpers.h"

s32 sub_8087CE4();
void sub_8082E1C(struct RuntimeObject* object, s32 animation, s32 command, s32 argument);
void sub_808750C(struct RuntimeObject* object);
void sub_81147B4(struct RuntimeObject* object);
void sub_8070534(struct RuntimeObject* object);
void sub_807F4FC();
void sub_80874B4(struct RuntimeObject* object);
void sub_80886E0(struct RuntimeObject* object);
void sub_8111CA8(struct RuntimeObject* object);
void sub_811458C();

#define SEC(symbol) __attribute__((section(".text.small_functions_01." #symbol)))
#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define MISC_SEC(symbol) \
    __attribute__((section(".text.misc_helpers_01." STRINGIFY(symbol))))

SEC(sub_8065ED4)
void object_when_link_chain_empty_start_animation_0c(struct RuntimeObject* object)
{
    u8 linkCount;
    struct RuntimeObject* linked;

    linkCount = 0;
    linked = object->linkedObject;
    if (linked != 0) {
        do {
            linkCount += 1;
            linked = linked->linkedObject;
        } while (linked != 0);
    }
    if (linkCount == 0) {
        sub_8082E1C(object, 0x0C, 0, 0);
        object->update = sub_808750C;
    }
}

SEC(sub_8067A4C)
void object_move_right_and_fall_to_ground(struct RuntimeObject* object)
{
    object->currentPositionX += 0x200;
    object->verticalPosition -= object->value8C;
    object->value8C += 0x66;
    if (object->verticalPosition <= 0) {
        object->verticalPosition = 0;
        object->update = sub_808750C;
    }
}

SEC(sub_80886BC)
void object_restore_saved_update_on_flag_20(struct RuntimeObject* object)
{
    sub_8087CE4();
    if (object->flags79 & 0x20) {
        object->update = object->followup;
        object->followup = 0;
    }
}

SEC(sub_811488C)
void object_when_nested_link_ready_continue(struct RuntimeObject* object)
{
    if ((sub_8087CE4(object->linkedObject->linkedObject) << 0x18) == 0) {
        sound_effect_stop(0xD5);
        object->update = sub_81147B4;
        sub_81147B4(object);
    }
}

MISC_SEC(object_stop_sound_11a_and_idle)
void object_stop_sound_11a_and_idle(struct RuntimeObject* object)
{
    sound_effect_stop(0x11A);
    object->update = sub_808750C;
}

MISC_SEC(object_sync_linked_position_and_stop_when_value80_clear)
void object_sync_linked_position_and_stop_when_value80_clear(
    struct RuntimeObject* object)
{
    s32 value;
    struct RuntimeObject* linked;

    linked = object->linkedObject;
    linked->currentPositionX = object->currentPositionX;
    linked->currentPositionY = object->currentPositionY;
    linked->verticalPosition = object->verticalPosition;
    value = object->value80;
    if (value == 0) {
        object->update = (RuntimeObjectCallback)value;
        linked->update = (RuntimeObjectCallback)value;
    }
}

MISC_SEC(object_when_value80_clear_increment_value_a8)
void object_when_value80_clear_increment_value_a8(struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        object->valueA8 += 1;
        object->update = sub_8070534;
    }
}

MISC_SEC(object_stop_update)
void object_stop_update(struct RuntimeObject* object)
{
    object->update = 0;
}
MISC_SEC(object_stop_update)
const u16 object_stop_update_padding = 0;

MISC_SEC(object_when_value80_clear_mark_state_2)
void object_when_value80_clear_mark_state_2(struct RuntimeObject* object)
{
    s32 value;
    struct RuntimeObjectState* state;

    value = object->value80;
    if (value == 0) {
        object->update = (RuntimeObjectCallback)value;
        state = object->state;
        state->valueA4 = 2;
        state->value113 = 2;
    }
}

MISC_SEC(object_state_get_value_source_byte6)
s8 object_state_get_value_source_byte6(struct RuntimeObjectState* state)
{
    return state->valueSourceE4->value6;
}

MISC_SEC(object_when_visual_value21_clear_install_update)
void object_when_visual_value21_clear_install_update(
    struct RuntimeObject* object)
{
    if (object->visual->value21 == 0)
        object->update = sub_80874B4;
}

#define DEFINE_SAVE_AND_INSTALL(name, next)                            \
    MISC_SEC(name) void name(struct RuntimeObject* object)              \
    {                                                                   \
        object->followup = object->update;                              \
        object->update = next;                                         \
    }

DEFINE_SAVE_AND_INSTALL(
    object_save_update_and_install_flag_wait_a, sub_80886BC)
DEFINE_SAVE_AND_INSTALL(
    object_save_update_and_install_flag_wait_b, sub_80886E0)

MISC_SEC(object_prepare_and_install_callback_808a201)
void object_prepare_and_install_callback_808a201(struct RuntimeObject* object)
{
    sub_807F4FC();
    object->update = (RuntimeObjectCallback)0x0808A201;
}

MISC_SEC(object_when_state_value113_clear_delay_16)
void object_when_state_value113_clear_delay_16(struct RuntimeObject* object)
{
    if (object->state->value113 == 0) {
        object->timer = 16;
        object->update = sub_8111CA8;
    }
}

MISC_SEC(object_when_flags_38_clear_stop_and_clear_owner_state)
void object_when_flags_38_clear_stop_and_clear_owner_state(
    struct RuntimeObject* object)
{
    s32 value;
    struct RuntimeObject* owner;

    value = object->flags76 & 0x38;
    if (value == 0) {
        object->update = (RuntimeObjectCallback)value;
        owner = object->positionOwner;
        owner->state->value113 = (s8)value;
    }
}

MISC_SEC(object_prepare_and_clear_state_value113)
void object_prepare_and_clear_state_value113(struct RuntimeObject* object)
{
    sub_811458C();
    object->state->value113 = 0;
}
