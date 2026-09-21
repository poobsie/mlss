#include "audio/sound_effects.h"
#include "object/runtime_leaf_callbacks.h"
#include "runtime_leaf_internal.h"

#define SEC(name) \
    __attribute__((section(".text.runtime_leaf_callbacks." #name)))

SEC(sub_80703B0)
void object_start_animation_41_or_42_when_value80_clears(
    struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        if (object->valueA8 != 0)
            sub_8082E1C(object, 0x29, 0, 0);
        else
            sub_8082E1C(object, 0x2A, 0, 0);
        object->update = sub_8070B70;
    }
}

SEC(sub_80704F0)
void object_clear_animation_and_stop_when_value80_clears(
    struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        sub_8082E1C(object, 0, 0, 0);
        object->update = NULL;
    }
}

SEC(sub_80706B0)
void object_finish_animation_21_after_visual_countdown(
    struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        object->timer--;
        if (object->timer <= 0) {
            sub_8082E1C(object, 0x15, 0, 0);
            object->update = NULL;
        }
    }
}
SEC(sub_80706B0)
const u16 sub_80706B0_padding = 0;

SEC(sub_8070B70)
void object_emit_effect_201c_on_visual_complete(struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 0x2B, 0, 0);
        sub_80DF024(0x201C, object->positionX / 0x100,
                    object->positionY / 0x100,
                    object->positionZBase / 0x100, object);
        object->update = sub_8070EDC;
    }
}

SEC(sub_8070BC8)
void object_begin_animation_35_fixed_motion(struct RuntimeObject* object)
{
    u8 flags;
    sub_8082E1C(object, 0x23, 0, 0);
    object->value84 = 0x11800;
    *(s32*)((u8*)object + 0x88) = object->positionY;
    object->value8C = object->positionZBase;
    object->motionSpeed = 0x199;
    flags = object->motionFlags;
    flags |= 0x20;
    object->motionFlags = flags;
    object->motionDurationOverride = 0;
    sub_8085B38(object);
    object->update = sub_8070F04;
    sound_effect_play(0x11C, SOUND_VOLUME_UNCHANGED);
}

SEC(sub_8070C2C)
void object_start_animation_28_when_value80_clears(
    struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        sound_effect_stop(0x11C);
        sub_8082E1C(object, 0x1C, 0, 0);
        object->update = sub_8070F64;
    }
}

SEC(sub_8070C8C)
void object_begin_animation_21_fixed_motion(struct RuntimeObject* object)
{
    u8 flags;
    sub_8082E1C(object, 0x15, 0, 0);
    object->value84 = 0x7800;
    *(s32*)((u8*)object + 0x88) = 0x6800;
    object->value8C = object->positionZBase;
    object->motionSpeed = 0x100;
    flags = object->motionFlags;
    flags |= 0x20;
    object->motionFlags = flags;
    object->motionDurationOverride = 0;
    sub_8085B38(object);
    object->update = sub_8070F98;
    sound_effect_play(0x11C, SOUND_VOLUME_UNCHANGED);
}

SEC(sub_8070F04)
void object_begin_animation_36_when_value80_clears(
    struct RuntimeObject* object)
{
    u8 flags;
    if (object->value80 == 0) {
        sub_8082E1C(object, 0x24, 0, 0);
        object->value84 = 0xA800;
        *(s32*)((u8*)object + 0x88) = 0x6800;
        object->value8C = object->positionZBase;
        object->motionSpeed = 0x199;
        flags = object->motionFlags;
        flags |= 0x20;
        object->motionFlags = flags;
        object->motionDurationOverride = 0;
        sub_8085B38(object);
        object->update = sub_807116C;
    }
}

SEC(sub_8071054)
void object_finish_linked_owner_sequence_when_value80_clears(
    struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        sound_effect_stop(0xA7);
        sub_807F47C(object);
        sub_807B7A8(object->state);
        sub_807FE40(object->state);
    }
}
SEC(sub_8071054)
const u16 sub_8071054_padding = 0;

SEC(sub_8071080)
void object_emit_effect_209e_and_begin_command_40e7(
    struct RuntimeObject* object)
{
    sub_80DF024(0x209E, object->positionX / 0x100,
                object->positionY / 0x100,
                object->positionZBase / 0x100, object);
    sub_8082E1C(object, 2, 0x40E7, 0);
    object->behaviorState = 0x300;
    object->valueA0 = 0x33;
    object->update = sub_806F84C;
}

SEC(sub_8071204)
s32 object_finish_sound_d2_and_begin_animation_1_when_ready(
    struct RuntimeObject* object)
{
    s32 result = sub_8087124(object);
    if (result == 0) {
        sound_effect_stop(0xD2);
        sub_8082E1C(object, 1, 0, 0);
        object->value84 = 60;
        object->update = sub_807127C;
        ((struct RuntimeObject*)object->positionOwner)->update = sub_808750C;
        return 0;
    }
    return result;
}

SEC(sub_807127C)
void object_finish_animation_7_after_countdown(struct RuntimeObject* object)
{
    object->timer--;
    if (object->timer <= 0) {
        sub_8082E1C(object, 7, 0, 0);
        object->update = sub_808750C;
    }
}
SEC(sub_807127C)
const u32 sub_807127C_padding = 0x4770;

SEC(sub_80742FC)
s32 object_resume_with_sound_ad_when_ready(struct RuntimeObject* object)
{
    s32 result = sub_8086D80(object);
    if (result == 0) {
        object->update = sub_8072944;
        sound_effect_play(0xAD, SOUND_VOLUME_UNCHANGED);
        return 0;
    }
    return result;
}

SEC(sub_807438C)
void object_remove_after_value84_countdown(struct RuntimeObject* object)
{
    object->value84--;
    if (object->value84 <= 0) {
        object->update = NULL;
        sub_807C298(object);
    }
}

SEC(sub_80744B4)
void object_start_animation_6_effect_22e2(struct RuntimeObject* object)
{
    sub_8082E1C(object, 6, 0, 0);
    sub_80DF024(0x22E2, object->positionX / 0x100,
                object->positionY / 0x100,
                object->positionZBase / 0x100, object);
    sound_effect_stop(0x116);
    object->update = sub_80746C4;
}

SEC(sub_8074508)
void object_wait_for_child_or_periodic_transition(struct RuntimeObject* object)
{
    if (object->linkedObject == NULL) {
        sound_effect_stop(0xD5);
        object->update = sub_80744B4;
    } else {
        object->timer--;
        if (object->timer <= 0) {
            sub_810CA8C(1);
            object->valueA0 = 1;
            object->timer = 180;
            object->update = sub_80746EC;
        }
    }
}

SEC(sub_80745E4)
void object_start_animation_2_and_effect_22c0(struct RuntimeObject* object)
{
    sub_8082E1C(object, 2, 0, 0);
    sub_80DF024(0x22C0, object->positionX / 0x100,
                object->positionY / 0x100,
                object->positionZBase / 0x100, object);
    object->update = sub_80731B4;
}

SEC(sub_807462C)
void object_stop_after_timer_countdown(struct RuntimeObject* object)
{
    object->timer--;
    if (object->timer <= 0)
        object->update = NULL;
}

SEC(sub_8074688)
void object_begin_timer_16_when_value80_clears(struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        object->timer = 16;
        object->update = sub_80728D0;
    }
}

SEC(sub_8075BB8)
s32 object_stop_sound_and_forward_owner_transition(
    struct RuntimeObject* object, void* owner)
{
    sound_effect_stop(0x8C);
    sub_810DD7C(object, owner, 0xFF);
    object->timer = 0;
    object->update = sub_80759E8;
    return 0;
}

SEC(sub_8075C10)
s32 object_finish_runtime_motion_and_resume(struct RuntimeObject* object)
{
    s32 result = sub_8087124(object);
    if (result == 0) {
        sub_807F47C(object);
        sub_8082E1C(object, 1, 0, 0);
        object->timer = 30;
        object->update = sub_80757C0;
        return 0;
    }
    return result;
}

SEC(sub_8075C8C)
void object_emit_effect_2479_on_visual_complete(struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 7, 0, 0);
        sound_effect_play(0x12B, SOUND_VOLUME_UNCHANGED);
        sub_80DF024(0x2479, object->positionX / 0x100,
                    object->positionY / 0x100,
                    object->positionZBase / 0x100, object);
        object->update = sub_80756A4;
    }
}

SEC(sub_8075D98)
void object_emit_effect_23de_when_link_clears(struct RuntimeObject* object)
{
    if (object->linkedObject == NULL) {
        sub_8082E1C(object, 0x10, 0, 0);
        object->update = sub_807536C;
        sub_80DF024(0x23DE, object->positionX / 0x100,
                    object->positionY / 0x100,
                    object->positionZBase / 0x100, object);
        sound_effect_play(0x46, SOUND_VOLUME_UNCHANGED);
    }
}

SEC(sub_8075E3C)
void object_emit_periodic_effect_23cc_until_value80_clears(
    struct RuntimeObject* object)
{
    object->timer--;
    if (object->timer <= 0) {
        sub_80DF024(0x23CC, object->positionX / 0x100,
                    object->positionY / 0x100,
                    object->positionZBase / 0x100, object);
        object->timer = 10;
    }
    if (object->value80 == 0)
        object->update = sub_8074EEC;
}

SEC(sub_8075E9C)
void object_emit_periodic_effect_23cc_until_alternate_resume(
    struct RuntimeObject* object)
{
    object->timer--;
    if (object->timer <= 0) {
        sub_80DF024(0x23CC, object->positionX / 0x100,
                    object->positionY / 0x100,
                    object->positionZBase / 0x100, object);
        object->timer = 10;
    }
    if (object->value80 == 0)
        object->update = sub_8074D1C;
}

SEC(sub_8075EFC)
s32 object_emit_effect_2423_and_finish_when_runtime_ready(
    struct RuntimeObject* object)
{
    s32 result = sub_8086D80(object);
    if (result == 0) {
        sub_80DF024(0x2423, object->positionX / 0x100,
                    object->positionY / 0x100,
                    object->positionZBase / 0x100, object);
        sub_807C298(object);
        sound_effect_stop(0x8C);
        return 0;
    }
    return result;
}

SEC(sub_8075F4C)
void object_clear_animation_and_stop_on_visual_complete(
    struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 0, 0, 0);
        object->update = NULL;
    }
}
SEC(sub_8075F4C)
const u16 sub_8075F4C_padding = 0;
