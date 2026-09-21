#include "audio/sound_effects.h"
#include "object/runtime_leaf_callbacks.h"
#include "runtime_leaf_internal.h"

#define SEC(name) \
    __attribute__((section(".text.runtime_leaf_callbacks." #name)))

#define OBJECT_SEQUENCE_COUNTER (*(u8*)0x03000ED0)
#define OBJECT_SEQUENCE_VARIANT (*(s32*)0x03000F6C)

SEC(sub_8079394)
void object_finish_and_advance_sequence_counter(struct RuntimeObject* object)
{
    if (object->behaviorState != 0) {
        if (object->behaviorState == 1)
            OBJECT_SEQUENCE_COUNTER = 0;
        else
            OBJECT_SEQUENCE_COUNTER++;
        object->update = NULL;
    }
}

SEC(sub_80793C4)
void object_start_animation_1_with_sound_ad_when_value80_clears(
    struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        sub_8082E1C(object, 1, 0, 0);
        object->update = sub_80798A8;
        sound_effect_play(0xAD, SOUND_VOLUME_UNCHANGED);
    }
}

SEC(sub_8079450)
void object_clear_animation_and_stop_on_visual_complete_variant(
    struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 0, 0, 0);
        object->update = NULL;
    }
}
SEC(sub_8079450)
const u16 sub_8079450_padding = 0;

SEC(sub_807953C)
void object_move_left_until_screen_exit_variant(struct RuntimeObject* object)
{
    object->currentPositionX -= 0x280;
    if (object->currentPositionX / 0x100 <= -32)
        sub_807C298(object);
}

SEC(sub_8079688)
void object_clear_animation_and_stop_on_visual_complete_second_variant(
    struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 0, 0, 0);
        object->update = NULL;
    }
}
SEC(sub_8079688)
const u16 sub_8079688_padding = 0;

SEC(sub_80796C4)
void object_prepare_fixed_state_when_value80_clears(
    struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        object->behaviorState = 0x100;
        object->value8C = 0x10;
        object->timer = 1;
        object->verticalVelocity = 0;
        object->update = sub_8078678;
        sound_effect_play(0x9C, SOUND_VOLUME_UNCHANGED);
    }
}

SEC(sub_80797E0)
s32 object_finish_effect_2aa6_and_signal_owner_when_runtime_ready(
    struct RuntimeObject* object)
{
    s32 result = sub_8086D80(object);
    if (result == 0) {
        sub_807F47C(object);
        sound_effect_play(0xE3, SOUND_VOLUME_UNCHANGED);
        sub_80DF024(0x2AA6, object->positionX / 0x100,
                    object->positionY / 0x100,
                    object->positionZBase / 0x100, object);
        sub_807C298(object);
        object->state->valueA4 = 1;
        object->state->eventSignal = 1;
        return -1;
    }
    return result;
}

SEC(sub_8079850)
void object_finish_linked_effect_2aa6(struct RuntimeObject* object)
{
    struct RuntimeObject* linked = object->linkedObject;
    sub_80DF024(0x2AA6, linked->positionX / 0x100,
                linked->positionY / 0x100,
                linked->positionZBase / 0x100, linked);
    sub_807C298(object->linkedObject);
    object->update = NULL;
    sound_effect_play(0x55, SOUND_VOLUME_UNCHANGED);
    OBJECT_SEQUENCE_COUNTER = 0;
}

SEC(sub_80798C4)
void object_start_variant_command_4029_on_visual_complete(
    struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        if (OBJECT_SEQUENCE_VARIANT == 0)
            sub_8082E1C(object, 3, 0x4029, 0);
        else
            sub_8082E1C(object, 8, 0x4029, 0);
        object->timer = 6;
        object->update = sub_8079B48;
    }
}

SEC(sub_807995C)
void object_start_animation_15_effect_2a8b_and_sound_119(
    struct RuntimeObject* object)
{
    sub_8082E1C(object, 15, 0, 0);
    sub_80DF024(0x2A8B, object->positionX / 0x100,
                object->positionY / 0x100,
                object->positionZBase / 0x100, object);
    sound_effect_play(0x119, SOUND_VOLUME_UNCHANGED);
    object->update = sub_8078E2C;
}

SEC(sub_80799EC)
void object_start_animation_21_and_effect_2a58(struct RuntimeObject* object)
{
    sub_8082E1C(object, 21, 0, 0);
    sub_80DF024(0x2A58, object->positionX / 0x100,
                object->positionY / 0x100,
                object->positionZBase / 0x100, object);
    object->update = sub_8079BD0;
}

SEC(sub_8079A38)
void object_start_animation_19_effect_29d2_and_sound_10c(
    struct RuntimeObject* object)
{
    sub_8082E1C(object, 19, 0, 0);
    sub_80DF024(0x29D2, object->positionX / 0x100,
                object->positionY / 0x100,
                object->positionZBase / 0x100, object);
    sound_effect_play(0x10C, SOUND_VOLUME_UNCHANGED);
    object->update = sub_8078524;
}

SEC(sub_8079AD8)
void object_start_random_animation_7_to_10(struct RuntimeObject* object)
{
    object->behaviorState = sub_8199F30() & 3;
    switch (object->behaviorState) {
    case 0:
        sub_8082E1C(object, 7, 0, 0);
        break;
    case 1:
        sub_8082E1C(object, 8, 0, 0);
        break;
    case 2:
        sub_8082E1C(object, 9, 0, 0);
        break;
    default:
        sub_8082E1C(object, 10, 0, 0);
        break;
    }
    object->update = sub_8077704;
    object->timer = 4;
    sound_effect_play(0x42, SOUND_VOLUME_UNCHANGED);
}

SEC(sub_8079B48)
void object_advance_variant_command_4029_after_visual_countdown(
    struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        object->timer--;
        if (object->timer <= 0) {
            if (OBJECT_SEQUENCE_VARIANT == 0)
                sub_8082E1C(object, 5, 0x4029, 0);
            else
                sub_8082E1C(object, 9, 0x4029, 0);
            object->update = sub_8079C0C;
        }
    }
}

SEC(sub_8079BD0)
void object_prepare_animation_22_countdown_on_visual_complete(
    struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 22, 0, 0);
        object->timer = 6;
        object->behaviorState = 0;
        object->update = sub_8078894;
    }
}

SEC(sub_8079C3C)
void object_finish_visual_and_advance_sequence_counter(
    struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 0, 0, 0);
        object->update = NULL;
        OBJECT_SEQUENCE_COUNTER++;
    }
}
