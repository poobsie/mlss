#include "audio/sound_effects.h"
#include "object/runtime_leaf_callbacks.h"
#include "runtime_leaf_internal.h"

#define SEC(name) \
    __attribute__((section(".text.runtime_leaf_callbacks." #name)))

SEC(sub_8067830)
s32 object_constant_negative_one_callback(struct RuntimeObject* object)
{
    (void)object;
    return -1;
}
SEC(sub_8067830)
const u16 sub_8067830_padding = 0;

SEC(sub_8067838)
s32 object_begin_countdown_motion_when_ready(struct RuntimeObject* object)
{
    s32 result;

    result = sub_8087124(object);
    if (result != 0)
        return result;
    sub_8082E1C(object, 1, 0, 0);
    object->value80 = 0;
    object->value84 = 0x14;
    object->update = sub_80679FC;
    return 0;
}

SEC(sub_8067F94)
void object_advance_alternating_visual_countdown(struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        if (object->timer == 0)
            goto finish;
        sub_8082E1C(object, 6, 0, 0);
    }
    object->secondaryTimer--;
    if (object->secondaryTimer <= 0) {
        object->timer--;
        if (object->timer > 0) {
            sub_8082E1C(object, 7, 0, 0);
            object->update = sub_8067E4C;
        } else {
finish:
            sub_8082E1C(object, 9, 0, 0);
            object->update = sub_808750C;
        }
    }
}

SEC(sub_806800C)
s32 object_emit_effect_10c6_when_ready(struct RuntimeObject* object)
{
    s32 result;

    result = sub_80871A8(object);
    if (result == 0) {
        object->update = sub_806819C;
        sub_80DF024(0x10C6, object->positionX / 0x100,
                    object->positionY / 0x100,
                    object->positionZBase / 0x100, object);
        return 0;
    }
    return result;
}

SEC(sub_8068124)
void object_move_left_by_value84_until_screen_exit(struct RuntimeObject* object)
{
    object->currentPositionX -= object->value84;
    if (object->currentPositionX / 0x100 < -0x20)
        sub_807C298(object);
}

SEC(sub_8068168)
s32 object_initialize_behavior_and_resume_motion(struct RuntimeObject* object)
{
    if (object->behaviorState == 0) {
        object->behaviorState = 2;
        object->valueA0 = 1;
    }
    object->update = sub_8067DC8;
    return 1;
}

SEC(sub_80681EC)
void object_emit_effect_10be_and_finish(struct RuntimeObject* object)
{
    sub_80DF024(0x10BE, object->positionX / 0x100,
                object->positionY / 0x100, object->positionZBase / 0x100,
                object);
    sub_807C298(object);
}

SEC(sub_806822C)
void object_finish_secondary_countdown_with_animation_7(
    struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        object->secondaryTimer--;
        if (object->secondaryTimer <= 0) {
            sub_8082E1C(object, 7, 0, 0);
            object->update = sub_8067E4C;
        }
    }
}

SEC(sub_8068818)
void object_lower_x_until_motion_target(struct RuntimeObject* object)
{
    if (object->timer == 0) {
        object->currentPositionX -= 0x200;
        if (object->value84 >= object->currentPositionX)
            object->timer = 1;
    }
}

SEC(sub_8068844)
void object_prepare_linked_motion_when_chain_clears(
    struct RuntimeObject* object)
{
    u8* flags;

    if (object->linkedObject->linkedObject == NULL) {
        sub_8082E1C(object, 9, 0, 0);
        object->linkedObject->currentPositionX = 0x10000;
        object->value84 = object->secondaryTimer << 8;
        object->value88 = (s16)object->stateValueB0 << 8;
        object->value8C = object->positionZBase;
        flags = &object->motionFlags;
        *flags |= 0x20;
        object->motionSpeed = 0x166;
        object->motionDurationOverride = 0;
        sub_8085B38(object);
        object->update = sub_80689AC;
    }
}

SEC(sub_80688B8)
void object_finish_variant_countdown_on_visual_complete(
    struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        object->timer--;
        if (object->timer <= 0) {
            if (object->valueA8 == 0)
                sub_8082E1C(object, 4, 0, 0);
            else
                sub_8082E1C(object, 7, 0, 0);
            object->update = sub_806856C;
        }
    }
}

SEC(sub_80684B0)
void object_advance_variant_timer_then_reposition_link(
    struct RuntimeObject* object)
{
    s32 variant;
    s32 elapsed = (u16)object->timer + 1;

    object->timer = elapsed;
    if (object->valueA8 == 0) {
        if ((s16)elapsed == 0x1E)
            sound_effect_play(0x63, SOUND_VOLUME_UNCHANGED);
    } else if ((s16)elapsed == 0xA) {
        sound_effect_play(0x63, SOUND_VOLUME_UNCHANGED);
    }

    if (object->visual->flags & 8) {
        /* The two branches retain the original call sites and timing. */
        if (object->valueA8 == 0)
            sound_effect_stop(0x11B);
        else
            sound_effect_stop(0x11B);

        variant = object->valueA8;
        if (variant == 0) {
            sub_8082E1C(object, 3, 0, 0);
            object->timer = variant;
        } else {
            sub_8082E1C(object, 6, 0, 0);
            object->timer = 3;
        }
        object->linkedObject->currentPositionX = object->positionX + 0x2200;
        object->linkedObject->currentPositionY = object->positionY;
        object->update = object_finish_variant_countdown_on_visual_complete;
    }
}

SEC(sub_8068A50)
void object_finish_variant_timer_on_visual_complete(
    struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        object->timer--;
        if (object->timer <= 0) {
            if (object->valueA8 == 0)
                sub_8082E1C(object, 0xD, 0, 0);
            else
                sub_8082E1C(object, 0x10, 0, 0);
            object->update = object_advance_variant_timer_then_reposition_link;
            object->timer = 0;
        }
    }
}

SEC(sub_8068B68)
void object_move_left_with_periodic_effect_until_screen_exit(
    struct RuntimeObject* object)
{
    object->timer++;
    if (object->timer > 0x10) {
        sub_80DF024(0x1C81, object->positionX / 0x100,
                    object->positionY / 0x100,
                    object->positionZBase / 0x100, object);
        object->timer = 0;
    }
    object->currentPositionX -= object->valueA0;
    if (object->currentPositionX / 0x100 <= -0x30) {
        sub_807F47C(object);
        object->currentPositionX = 0x10000;
        object->currentPositionY = *(s32*)((u8*)object->state + 0xDC);
        object->update = sub_8068BF0;
    }
}

SEC(sub_8068BF0)
void object_move_left_with_effect_until_owner_target(
    struct RuntimeObject* object)
{
    object->timer++;
    if (object->timer > 0x10) {
        sub_80DF024(0x1C81, object->positionX / 0x100,
                    object->positionY / 0x100,
                    object->positionZBase / 0x100, object);
        object->timer = 0;
    }
    object->currentPositionX -= object->valueA0;
    if (object->currentPositionX <=
        *(s32*)((u8*)object->state + 0xD8)) {
        sound_effect_stop(0x11A);
        sub_8082E1C(object, 0xC, 0, 0);
        object->update = sub_8068C70;
    }
}

SEC(sub_8068C98)
void object_start_variant_return_when_value80_clears(
    struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        if (object->valueA8 == 0) {
            sound_effect_stop(0x81);
            sub_8082E1C(object, 4, 0, 0);
            object->timer = object->behaviorState;
            sound_effect_play(0x88, SOUND_VOLUME_UNCHANGED);
        } else {
            sound_effect_stop(0x81);
            sub_8082E1C(object, 7, 0, 0);
            object->timer = object->behaviorState;
            sound_effect_play(0x88, SOUND_VOLUME_UNCHANGED);
        }
        object->update = sub_8068D74;
    }
}

SEC(sub_8068D74)
void object_finish_variant_return_timer(struct RuntimeObject* object)
{
    object->timer--;
    if (object->timer <= 0) {
        if (object->valueA8 == 0)
            sub_8082E1C(object, 5, 0, 0);
        else
            sub_8082E1C(object, 8, 0, 0);
        object->update = sub_8068DEC;
    }
}

SEC(sub_8068E7C)
s32 object_resume_after_auxiliary_motion(struct RuntimeObject* object)
{
    s32 result;

    result = sub_8086C64(object);
    if (result == 0) {
        object->update = sub_8068EF4;
        return 0;
    }
    return result;
}

#define GLOBAL_EFFECT_OBJECT (*(struct RuntimeObject**)0x03000E3C)

SEC(sub_8068E98)
void object_move_left_until_owner_target_and_emit_effect(
    struct RuntimeObject* object)
{
    s32 target;

    object->currentPositionX -= object->valueA0;
    target = *(s32*)(*(u8**)((u8*)object->positionOwner + 0x28) + 0xD8)
             + 0x1600;
    if (target >= object->currentPositionX) {
        object->currentPositionX = target;
        sub_8082E1C(object, 0xA, 0, 0);
        GLOBAL_EFFECT_OBJECT = (struct RuntimeObject*)sub_8086858(object, 0x1608);
        sound_effect_play(0xAF, SOUND_VOLUME_UNCHANGED);
        object->update = sub_8068F10;
    }
}

SEC(sub_8069354)
s32 object_resume_sequence_when_runtime_ready(struct RuntimeObject* object)
{
    s32 result;

    result = sub_8086D80(object);
    if (result == 0) {
        if (object->secondaryTimer == 0)
            sound_effect_stop(0x81);
        else
            sound_effect_stop(0x81);
        object->value80 = 0;
        object->update = sub_80690F8;
        return 0;
    }
    return result;
}
