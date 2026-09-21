#include "audio/sound_effects.h"
#include "object/runtime_leaf_callbacks.h"
#include "runtime_leaf_internal.h"

#define SEC(name) \
    __attribute__((section(".text.runtime_leaf_callbacks." #name)))

SEC(sub_8065CC4)
void object_advance_visual_timer_with_sound_d5(struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        object->timer--;
        if (object->timer > 0) {
            sound_effect_play(0xD5, SOUND_VOLUME_UNCHANGED);
        } else {
            sub_8082E1C(object, 0xB, 0, 0);
            sub_807F4FC(object);
            object->update = sub_8065D78;
        }
    }
}

SEC(sub_8065DD4)
void object_branch_animation_on_visual_timer(struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        object->timer--;
        if (object->timer > 0) {
            sub_8082E1C(object, 0x10, 0, 0);
            object->behaviorState = 4;
            object->update = sub_8065E68;
        } else {
            sub_8082E1C(object, 0x11, 0, 0);
            object->update = sub_8065E4C;
        }
    }
}

SEC(sub_8065EA0)
void object_finish_animation_15_on_countdown(struct RuntimeObject* object)
{
    object->timer--;
    if (object->timer <= 0) {
        sub_807F47C(object);
        sub_8082E1C(object, 0xF, 0, 0);
        object->update = sub_808750C;
    }
}

SEC(sub_8066540)
void object_store_motion_target(
    struct RuntimeObject* object, s32 x, s32 y, s32 z)
{
    object->value84 = x;
    object->value88 = y;
    object->value8C = z;
}

SEC(sub_8066550)
void object_copy_position_to_link_and_finish_when_value80_clears(
    struct RuntimeObject* object)
{
    object_store_motion_target(object->linkedObject, object->currentPositionX,
                               object->currentPositionY,
                               object->verticalPosition);
    if (object->value80 == 0) {
        sub_807C298(object->linkedObject);
        sub_807C298(object);
    }
}

SEC(sub_8066604)
void object_start_variant_animation_and_sound_when_value80_clears(
    struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        if (object->valueA0 == 0)
            sound_effect_stop(0x129);
        else
            sound_effect_stop(0x12A);
        if (object->behaviorState == 0)
            sub_8082E1C(object, 5, 0, 0);
        else
            sub_8082E1C(object, 9, 0, 0);
        object->update = sub_8066780;
        if (object->valueA0 == 0)
            sound_effect_play(0x123, SOUND_VOLUME_UNCHANGED);
        else
            sound_effect_play(0x124, SOUND_VOLUME_UNCHANGED);
    }
}
SEC(sub_8066604)
const u16 sub_8066604_padding = 0;

SEC(sub_806670C)
void object_prepare_saved_motion_on_visual_complete(
    struct RuntimeObject* object)
{
    u8* flags;

    if (object->visual->flags & 8) {
        sub_8082E1C(object, 0xD, 0, 0);
        object->value84 = object->secondaryTimer << 8;
        object->value88 = (s16)object->stateValueB0 << 8;
        object->value8C = object->positionZBase;
        flags = &object->motionFlags;
        *flags |= 0x20;
        object->motionSpeed = 0x14C;
        object->motionDurationOverride = 0;
        sub_8085B38(object);
        object->update = sub_8066864;
    }
}

SEC(sub_80667C4)
void object_prepare_repeat_variant_on_ready(struct RuntimeObject* object)
{
    if (sub_8082B00(object) == 0) {
        sub_8082E1C(object, 2, 0, 0);
        object->secondaryTimer = object->positionX / 0x100;
        object->stateValueB0 = object->positionY / 0x100;
        if (object->valueA0 != 0)
            object->behaviorState = (object->behaviorState + 1) & 1;
        object->update = sub_8065F0C;
    }
}

SEC(sub_8066C90)
void object_start_animation_9_with_short_timer(struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 9, 0, 0);
        object->timer = 2;
        object->update = sub_8066CEC;
    }
}

SEC(sub_8066CEC)
void object_advance_repeating_animation_count(struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        object->timer--;
        if (object->timer <= 0) {
            object->valueA0++;
            object->valueA4--;
            if (object->valueA4 > 0) {
                sub_8082E1C(object, 7, 0, 0);
                object->update = sub_806688C;
            } else {
                sub_8082E1C(object, 0xA, 0, 0);
                object->update = sub_8066D78;
            }
        }
    }
}

SEC(sub_8066DA4)
void object_prepare_fixed_motion_on_visual_complete(
    struct RuntimeObject* object)
{
    u8* flags;

    if (object->visual->flags & 8) {
        object->value84 = 0x7800;
        object->value88 = 0x6800;
        object->value8C = object->positionZBase;
        flags = &object->motionFlags;
        *flags |= 0x20;
        object->motionSpeed = 0x180;
        object->motionDurationOverride = 0;
        sub_8085B38(object);
        sub_8082E1C(object, 3, 0, 0);
        object->update = sub_8066E0C;
    }
}

SEC(sub_8066E5C)
void object_start_animation_6_and_random_repeat_count(
    struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        object->timer--;
        if (object->timer <= 0) {
            sub_8082E1C(object, 6, 0, 0);
            object->valueA0 = object->behaviorState;
            object->valueA4 = (sub_8199F30() & 1) + 3;
            object->update = sub_8066EB4;
        }
    }
}
