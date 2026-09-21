#include "audio/sound_effects.h"
#include "object/runtime_leaf_callbacks.h"
#include "runtime_leaf_internal.h"

#define SEC(name) \
    __attribute__((section(".text.runtime_leaf_callbacks." #name)))

#define GLOBAL_EFFECT_OBJECT (*(struct RuntimeObject**)0x03000E3C)

SEC(sub_806A180)
s32 object_set_behavior_one_when_runtime_ready(struct RuntimeObject* object)
{
    s32 result = sub_8086D80(object);
    if (result == 0) {
        object->behaviorState = 1;
        return 0;
    }
    return result;
}

SEC(sub_806A1CC)
s32 object_finish_when_runtime_ready(struct RuntimeObject* object)
{
    s32 result = sub_80871A8(object);
    if (result == 0) {
        object->update = sub_808750C;
        return 0;
    }
    return result;
}

SEC(sub_806A204)
void object_finish_animation_6_when_value80_clears(struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        sub_8082E1C(object, 6, 0, 0);
        object->update = sub_808750C;
    }
}

SEC(sub_806A290)
s32 object_select_behavior_from_owner_variant(struct RuntimeObject* object)
{
    u8* owner = *(u8**)((u8*)object->positionOwner + 0x28);
    if (*(s16*)(owner + 0xEC) == -1)
        object->behaviorState = 0;
    else
        object->behaviorState = 1;
    object->update = sub_80695E4;
    return 1;
}

SEC(sub_806A2FC)
void object_finish_timer_with_effect_1810(struct RuntimeObject* object)
{
    object->timer--;
    if (object->timer <= 0) {
        sub_8082E1C(object, 5, 0, 0);
        GLOBAL_EFFECT_OBJECT = (struct RuntimeObject*)sub_8086858(object, 0x1810);
        object->update =
            object_on_visual_complete_prepare_owner_offset_motion_and_decrement_repeat;
        sound_effect_play(0xAF, SOUND_VOLUME_UNCHANGED);
    }
}

SEC(sub_806A730)
s32 object_stop_sound_111_and_resume_auxiliary_motion(
    struct RuntimeObject* object, s32 argument1, s32 argument2)
{
    s32 result;
    sound_effect_stop(0x111);
    result = sub_8086C64(object, argument1, argument2);
    if (result == 0) {
        object->update = sub_806A77C;
        return 0;
    }
    return result;
}

SEC(sub_806A7A0)
void object_stop_update_when_value80_clears(struct RuntimeObject* object)
{
    RuntimeObjectCallback next = (RuntimeObjectCallback)object->value80;
    if (next == NULL) {
        sub_8082E1C(object, 0, 0, 0);
        object->update = next;
    }
}

SEC(sub_806A7CC)
s32 object_stop_sound_81_and_forward_auxiliary_motion(
    struct RuntimeObject* object, s32 argument1, s32 argument2)
{
    sound_effect_stop(0x81);
    return sub_8086C64(object, argument1, argument2);
}
SEC(sub_806A7CC)
const u16 sub_806A7CC_padding = 0;

SEC(sub_806A83C)
void object_start_random_countdown_when_value80_clears(
    struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        sound_effect_stop(0x81);
        sub_8082E1C(object, 4, 0, 0);
        object->timer = object->behaviorState
            + (u32)sub_8199F30() % (u32)object->valueA0;
        object->update = sub_806A47C;
    }
}

SEC(sub_806A8B0)
void object_finish_animation_6_on_countdown(struct RuntimeObject* object)
{
    object->timer--;
    if (object->timer <= 0) {
        sub_8082E1C(object, 6, 0, 0);
        object->update = sub_808750C;
    }
}

SEC(sub_806A97C)
void object_start_long_motion_countdown_when_value80_clears(
    struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        object->timer = 30;
        object->update = sub_806A510;
    }
}

SEC(sub_806AF80)
void object_emit_periodic_effect_until_value80_clears(
    struct RuntimeObject* object)
{
    object->timer--;
    if (object->timer <= 0) {
        sub_80DF024(0xDB2, object->positionX / 0x100,
                    object->positionY / 0x100,
                    object->positionZBase / 0x100, object);
        object->timer = 10;
    }
    if (object->value80 == 0) {
        sound_effect_stop(0x6C);
        object->timer = 20;
        object->update = sub_806AFEC;
    }
}

SEC(sub_806B084)
void object_emit_periodic_effect_then_continue_when_value80_clears(
    struct RuntimeObject* object)
{
    object->timer--;
    if (object->timer <= 0) {
        sub_80DF024(0xDB2, object->positionX / 0x100,
                    object->positionY / 0x100,
                    object->positionZBase / 0x100, object);
        object->timer = 10;
    }
    if (object->value80 == 0) {
        object->timer = 20;
        object->update = sub_806B0EC;
    }
}

SEC(sub_806B208)
void object_emit_periodic_effect_until_stop(struct RuntimeObject* object)
{
    RuntimeObjectCallback next;
    object->timer--;
    if (object->timer <= 0) {
        sub_80DF024(0xDBB, object->positionX / 0x100,
                    object->positionY / 0x100,
                    object->positionZBase / 0x100, object);
        object->timer = 10;
    }
    next = (RuntimeObjectCallback)object->value80;
    if (next == NULL) {
        sub_8082E1C(object, 0, 0, 0);
        object->update = next;
    }
}

SEC(sub_806B26C)
s32 object_remove_when_runtime_ready(struct RuntimeObject* object)
{
    s32 result = sub_80871A8(object);
    if (result == 0) {
        sub_807C298(object);
        return 0;
    }
    return result;
}
SEC(sub_806B26C)
const u16 sub_806B26C_padding = 0;

SEC(sub_806B298)
void object_prepare_saved_position_when_value80_clears(
    struct RuntimeObject* object)
{
    s32 zero = object->value80;
    u8 flags;
    if (zero == 0) {
        sub_8082E1C(object, 1, 0, 0);
        object->value84 = (s32)*(s16*)((u8*)object + 0xAE) << 8;
        object->value88 = (s32)*(s16*)((u8*)object + 0xB0) << 8;
        object->value8C = (s32)*(s16*)((u8*)object + 0xB2) << 8;
        flags = object->motionFlags;
        flags |= 0x20;
        object->motionFlags = flags;
        object->motionSpeed = 0x300;
        object->motionDurationOverride = (s16)zero;
        sub_8085B38(object);
        object->update = sub_806B528;
        sound_effect_play(0xD5, SOUND_VOLUME_UNCHANGED);
    }
}

SEC(sub_806B340)
s32 object_emit_effect_d82_and_remove_when_runtime_ready(
    struct RuntimeObject* object)
{
    s32 result = sub_8086D80(object);
    if (result == 0) {
        sub_80DF024(0xD82, object->positionX / 0x100,
                    object->positionY / 0x100,
                    object->positionZBase / 0x100, object);
        sub_807C298(object);
        sound_effect_stop(0x58);
        return 0;
    }
    return result;
}

SEC(sub_806B3D0)
void object_move_left_by_behavior_velocity_until_exit(
    struct RuntimeObject* object)
{
    s32 position;
    object->currentPositionX -= object->behaviorState;
    position = object->currentPositionX;
    if (position < 0)
        position += 0xFF;
    if ((position >> 8) <= -0x40) {
        sound_effect_stop(0x58);
        sub_807C298(object);
    }
}

SEC(sub_806B424)
void object_emit_effect_db2_until_value80_clears(
    struct RuntimeObject* object)
{
    object->timer--;
    if (object->timer <= 0) {
        sub_80DF024(0xDB2, object->positionX / 0x100,
                    object->positionY / 0x100,
                    object->positionZBase / 0x100, object);
        object->timer = 10;
    }
    if (object->value80 == 0) {
        sub_8082E1C(object, 5, 0, 0);
        object->update = sub_806AA18;
    }
}

SEC(sub_806B540)
void object_start_valueA4_animation_and_sound_88(struct RuntimeObject* object)
{
    sub_8082E1C(object, object->valueA4, 0, 0);
    sound_effect_play(0x88, SOUND_VOLUME_UNCHANGED);
    object->update = sub_806B5A8;
}

SEC(sub_806BAB8)
void object_emit_effect_1c52_until_value80_clears(
    struct RuntimeObject* object)
{
    object->timer--;
    if (object->timer <= 0) {
        object->timer = 10;
        sub_80DF024(0x1C52, object->positionX / 0x100,
                    object->positionY / 0x100,
                    object->positionZBase / 0x100, object);
    }
    if (object->value80 == 0) {
        sound_effect_stop(0x6C);
        if (object->valueA8 == 0)
            sub_8082E1C(object, 6, 0, 0);
        else
            sub_8082E1C(object, 14, 0, 0);
        object->timer = 0;
        object->update = sub_806BB48;
    }
}

SEC(sub_806BF0C)
void object_emit_effect_1c5b_until_stop(struct RuntimeObject* object)
{
    RuntimeObjectCallback next;
    object->timer--;
    if (object->timer <= 0) {
        object->timer = 10;
        sub_80DF024(0x1C5B, object->positionX / 0x100,
                    object->positionY / 0x100,
                    object->positionZBase / 0x100, object);
    }
    next = (RuntimeObjectCallback)object->value80;
    if (next == NULL) {
        sub_8082E1C(object, 0, 0, 0);
        object->update = next;
    }
}

SEC(sub_806C020)
s32 object_continue_owner_motion_when_runtime_ready(struct RuntimeObject* object)
{
    s32 result = sub_8086D80(object);
    if (result == 0) {
        object->update = sub_806B824;
        return 0;
    }
    return result;
}

SEC(sub_806C1C8)
void object_stop_on_visual_complete(struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 0, 0, 0);
        object->update = NULL;
    }
}
SEC(sub_806C1C8)
const u16 sub_806C1C8_padding = 0;

SEC(sub_806C2B0)
void object_emit_effect_1bfe_on_visual_complete(struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 3, 0, 0);
        sound_effect_play(0x10C, SOUND_VOLUME_UNCHANGED);
        sub_80DF024(0x1BFE, object->positionX / 0x100,
                    object->positionY / 0x100,
                    object->positionZBase / 0x100, object);
        object->update = sub_806B644;
    }
}

SEC(sub_806C76C)
s32 object_emit_effect_1df8_and_remove_when_runtime_ready(
    struct RuntimeObject* object)
{
    s32 result = sub_8086D80(object);
    if (result == 0) {
        sub_80DF024(0x1DF8, object->positionX / 0x100,
                    object->positionY / 0x100,
                    object->positionZBase / 0x100, object);
        sub_807C298(object);
        return 0;
    }
    return result;
}

SEC(sub_806CAC0)
void object_start_animation_21_after_countdown(struct RuntimeObject* object)
{
    object->timer--;
    if (object->timer <= 0) {
        sub_8082E1C(object, 0x15, 0, 0);
        object->update = sub_806C454;
    }
}

SEC(sub_806CB6C)
void object_start_variant_animation_7_or_13(struct RuntimeObject* object)
{
    if (object->valueA8 == 0)
        sub_8082E1C(object, 7, 0, 0);
    else
        sub_8082E1C(object, 13, 0, 0);
    object->update = sub_806C9A4;
}

SEC(sub_806D290)
void object_emit_effect_212b_until_sequence_advances(
    struct RuntimeObject* object)
{
    object->timer--;
    if (object->timer <= 0) {
        sub_80DF024(0x212B, object->positionX / 0x100,
                    object->positionY / 0x100,
                    object->positionZBase / 0x100, object);
        object->timer = 10;
    }
    if (object->value80 == 0) {
        object->valueA0--;
        if (object->valueA0 > 0)
            sub_806CFBC(object);
        else {
            object->timer = 45;
            object->update = sub_806D35C;
        }
    }
}

SEC(sub_806D30C)
void object_start_animation_4_after_value80_clears(
    struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        sound_effect_stop(0x81);
        sub_8082E1C(object, 4, 0, 0);
        object->timer = 4;
        object->update = sub_806D480;
    }
}

SEC(sub_806D3C4)
void object_start_animation_4_then_linked_transition(
    struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        sound_effect_stop(0x81);
        sub_8082E1C(object, 4, 0, 0);
        object->timer = 4;
        object->update = sub_806CCB8;
    }
}

SEC(sub_806D770)
void object_sync_shared_effect_and_pair_variants(struct RuntimeObject* object)
{
    GLOBAL_EFFECT_OBJECT->currentPositionX = object->currentPositionX;
    GLOBAL_EFFECT_OBJECT->currentPositionY = object->currentPositionY;
    GLOBAL_EFFECT_OBJECT->verticalPosition = object->verticalPosition;
    object->unknown75 =
        ((struct RuntimeObject*)object->positionOwner)->unknown75 - 1;
    object->linkedObject->unknown75 =
        ((struct RuntimeObject*)object->positionOwner)->unknown75 + 5;
    if (object->value80 == 0) {
        object->unknown75 =
            ((struct RuntimeObject*)object->positionOwner)->unknown75;
        object->linkedObject->unknown75 =
            ((struct RuntimeObject*)object->positionOwner)->unknown75 + 1;
        object->update = sub_806D7D0;
    }
}

SEC(sub_806E664)
s32 object_resume_motion_and_switch_sounds_when_ready(
    struct RuntimeObject* object)
{
    s32 result = sub_8086D80(object);
    if (result == 0) {
        object->update = sub_806E1B8;
        sound_effect_stop(0x6C);
        sound_effect_play(0x40, SOUND_VOLUME_UNCHANGED);
        return 0;
    }
    return result;
}

SEC(sub_806E778)
void object_stop_linked_updates_when_value80_clears(
    struct RuntimeObject* object)
{
    s32 value = object->value80;

    if (value == 0) {
        object->update = 0;
        object->linkedObject->update = 0;
    }
}
SEC(sub_806E778)
const u16 sub_806E778_padding = 0;

SEC(sub_806E7CC)
void object_start_linked_motion_countdown_when_value80_clears(
    struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        object->timer = 30;
        object->update = sub_806D61C;
    }
}

SEC(sub_806E804)
s32 object_select_owner_variant_and_continue(struct RuntimeObject* object)
{
    u8* owner = *(u8**)((u8*)object->positionOwner + 0x28);
    if (*(s16*)(owner + 0xEC) == -1)
        object->valueA0 = 0;
    else
        object->valueA0 = 1;
    object->update = sub_806DAF0;
    return 1;
}

SEC(sub_806E91C)
void object_finish_linked_animation_with_effect_when_value80_clears(
    struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        sub_8082E1C(object, 13, 0, 0);
        sub_8082E1C(object->linkedObject, 13, 0, 0);
        sound_effect_stop(0x6C);
        sound_effect_play(0x8C, SOUND_VOLUME_UNCHANGED);
        sub_80DF024(0x1FA6, object->positionX / 0x100,
                    object->positionY / 0x100,
                    object->positionZBase / 0x100, object);
        object->update = sub_806DBD4;
    }
}

SEC(sub_806EA54)
void object_start_animation_9_and_effect_1e8a_when_value80_clears(
    struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        sub_8082E1C(object, 9, 0, 0);
        sub_80DF024(0x1E8A, object->positionX / 0x100,
                    object->positionY / 0x100,
                    object->positionZBase / 0x100, object);
        object->update = sub_806EAA8;
    }
}
