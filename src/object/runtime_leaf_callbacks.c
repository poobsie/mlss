#include "global.h"
#include "audio/sound_effects.h"
#include "memory/heap.h"
#include "object/runtime_leaf_callbacks.h"

#define SEC(name) \
    __attribute__((section(".text.runtime_leaf_callbacks." #name)))

void sub_807C298(struct RuntimeObject* object);
void sub_8082E1C(
    struct RuntimeObject* object, s32 animation, s32 command, s32 argument);
void sub_806822C(struct RuntimeObject* object);
void sub_806CAC0(struct RuntimeObject* object);
void sub_806DD48(struct RuntimeObject* object);
void sub_8063474(struct RuntimeObject* object);
void sub_8063B2C(struct RuntimeObject* object);
void sub_8064C00(struct RuntimeObject* object);
void sub_80651B0(struct RuntimeObject* object);
void sub_8065758(struct RuntimeObject* object);
void sub_8065DD4(struct RuntimeObject* object);
void sub_80635FC(struct RuntimeObject* object);
void sub_8063B80(struct RuntimeObject* object);
void sub_8063BA8(struct RuntimeObject* object);
void sub_8063C60(struct RuntimeObject* object);
void sub_8063CC8(struct RuntimeObject* object);
void sub_8064540(struct RuntimeObject* object);
void sub_8064E30(struct RuntimeObject* object);
void sub_8065E2C(struct RuntimeObject* object);
void sub_8065D78(struct RuntimeObject* object);
void sub_8065E4C(struct RuntimeObject* object);
void sub_8065E68(struct RuntimeObject* object);
void sub_8065F0C(struct RuntimeObject* object);
void sub_8066780(struct RuntimeObject* object);
void sub_8066864(struct RuntimeObject* object);
void sub_806688C(struct RuntimeObject* object);
void sub_8066D78(struct RuntimeObject* object);
void sub_8066E0C(struct RuntimeObject* object);
void sub_8066EB4(struct RuntimeObject* object);
void sub_80679FC(struct RuntimeObject* object);
void sub_8067DC8(struct RuntimeObject* object);
void sub_8067E4C(struct RuntimeObject* object);
void sub_80684B0(struct RuntimeObject* object);
void sub_806856C(struct RuntimeObject* object);
void sub_80689AC(struct RuntimeObject* object);
void sub_8068A50(struct RuntimeObject* object);
void sub_8068B68(struct RuntimeObject* object);
void sub_8068BF0(struct RuntimeObject* object);
void sub_8068C70(struct RuntimeObject* object);
void sub_8068D74(struct RuntimeObject* object);
void sub_8068DEC(struct RuntimeObject* object);
void sub_8068E60(struct RuntimeObject* object);
void sub_8068E98(struct RuntimeObject* object);
void sub_8068EF4(struct RuntimeObject* object);
void sub_8068F10(struct RuntimeObject* object);
void sub_8069014(struct RuntimeObject* object);
void sub_80690F8(struct RuntimeObject* object);
void sub_806819C(struct RuntimeObject* object);
void sub_808750C(struct RuntimeObject* object);
void nullsub_15(void);
s32 sub_8082B00(struct RuntimeObject* object);
s32 sub_80871A8(struct RuntimeObject* object);
s32 sub_8086C64();
s32 sub_8086D80(struct RuntimeObject* object);
s32 sub_8087124(struct RuntimeObject* object);
s32 sub_8086858(struct RuntimeObject* object, s32 effect);
s32 sub_8199F30(void);
void sub_807F47C(struct RuntimeObject* object);
void sub_807F4FC(struct RuntimeObject* object);
void sub_8085B38(struct RuntimeObject* object);
struct RuntimeObject* sub_807C0D0(
    struct RuntimeObject* object, s32 command, s32 argument);
void sub_80DF024(s32 effect, s32 x, s32 y, s32 z,
                 struct RuntimeObject* object);

#define SHARED_MOTION_HANDLE (*(void**)0x03000E18)
#define GLOBAL_EFFECT_OBJECT (*(struct RuntimeObject**)0x03000E3C)

void sub_80695E4(struct RuntimeObject* object);
void sub_8069558(struct RuntimeObject* object);
void sub_806A47C(struct RuntimeObject* object);
void sub_806A510(struct RuntimeObject* object);
void sub_806A77C(struct RuntimeObject* object);
void sub_806AFEC(struct RuntimeObject* object);
void sub_806B0EC(struct RuntimeObject* object);
void sub_806AA18(struct RuntimeObject* object);
void sub_806B528(struct RuntimeObject* object);
void sub_806B5A8(struct RuntimeObject* object);
void sub_806B824(struct RuntimeObject* object);
void sub_806BB48(struct RuntimeObject* object);
void sub_806BAB8(struct RuntimeObject* object);
void sub_806B644(struct RuntimeObject* object);
void sub_806C454(struct RuntimeObject* object);
void sub_806C9A4(struct RuntimeObject* object);
void sub_806CBA0(struct RuntimeObject* object);
void sub_806CCB8(struct RuntimeObject* object);
void sub_806CFBC(struct RuntimeObject* object);
void sub_806D35C(struct RuntimeObject* object);
void sub_806D480(struct RuntimeObject* object);
void sub_806D61C(struct RuntimeObject* object);
void sub_806D7D0(struct RuntimeObject* object);
void sub_806DAF0(struct RuntimeObject* object);
void sub_806DBD4(struct RuntimeObject* object);
void sub_806E1B8(struct RuntimeObject* object);
void sub_806E91C(struct RuntimeObject* object);
void sub_806EA54(struct RuntimeObject* object);
void sub_806EAA8(struct RuntimeObject* object);
void sub_806F84C(struct RuntimeObject* object);
void sub_806FC68(struct RuntimeObject* object);
void sub_8070534(struct RuntimeObject* object);
void sub_80706E8(struct RuntimeObject* object);
void sub_8070B70(struct RuntimeObject* object);
void sub_8070C2C(struct RuntimeObject* object);
void sub_8070CF0(struct RuntimeObject* object);
void sub_8070EDC(struct RuntimeObject* object);
void sub_8070F04(struct RuntimeObject* object);
void sub_8070F64(struct RuntimeObject* object);
void sub_8070F98(struct RuntimeObject* object);
void sub_807116C(struct RuntimeObject* object);
void sub_807127C(struct RuntimeObject* object);
void sub_807F47C(struct RuntimeObject* object);
void sub_807B7A8(void* object);
void sub_807FE40(void* object);
void sub_8072944(struct RuntimeObject* object);
void sub_80731B4(struct RuntimeObject* object);
void sub_80744B4(struct RuntimeObject* object);
void sub_80746EC(struct RuntimeObject* object);
void sub_80728D0(struct RuntimeObject* object);
void sub_8074688(struct RuntimeObject* object);
void sub_80759E8(struct RuntimeObject* object);
void sub_80757C0(struct RuntimeObject* object);
void sub_80756A4(struct RuntimeObject* object);
void sub_807536C(struct RuntimeObject* object);
void sub_8074EEC(struct RuntimeObject* object);
void sub_8074D1C(struct RuntimeObject* object);
void sub_80775A4(struct RuntimeObject* object);
void sub_80764D8(struct RuntimeObject* object);
void sub_8077610(struct RuntimeObject* object);
void sub_8076338(struct RuntimeObject* object);
void sub_8076414(struct RuntimeObject* object);
void sub_8076D90(struct RuntimeObject* object);
void sub_80776B4(struct RuntimeObject* object);
void sub_80761E8(struct RuntimeObject* object);
void sub_8076C14(struct RuntimeObject* object);
void sub_807777C(struct RuntimeObject* object);
void sub_8077924(struct RuntimeObject* object);
void sub_810DD7C(struct RuntimeObject* object, void* owner, s32 command);
void sub_80746C4(struct RuntimeObject* object);
void sub_810CA8C(s32 value);

/* Effect IDs and unnamed continuations stay numeric until their owners are known.
 * RuntimeObject fields at 0x7A and 0x7C are confirmed halfword storage, but their
 * behavioral meaning is still unknown. */

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
    *(s32*)object->unknown88 = y;
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
        *(s32*)object->unknown88 = (s16)object->stateValueB0 << 8;
        object->value8C = object->positionZBase;
        flags = &object->flags79;
        *flags |= 0x20;
        object->unknown7C = 0x14C;
        object->unknown7A = 0;
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
        *(s32*)object->unknown88 = 0x6800;
        object->value8C = object->positionZBase;
        flags = &object->flags79;
        *flags |= 0x20;
        object->unknown7C = 0x180;
        object->unknown7A = 0;
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
        *(s32*)object->unknown88 = (s16)object->stateValueB0 << 8;
        object->value8C = object->positionZBase;
        flags = &object->flags79;
        *flags |= 0x20;
        object->unknown7C = 0x166;
        object->unknown7A = 0;
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
            object->update = sub_80684B0;
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


SEC(sub_8063A24)
void object_start_animation_5_when_value80_clears(
    struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        sub_8082E1C(object, 5, 0, 0);
        object->update = sub_80635FC;
    }
}

SEC(sub_8063AD4)
void object_advance_countdown_visual_sequence(struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        object->timer--;
        if (object->timer <= 0) {
            sub_8082E1C(object, 0xB, 0, 0);
            sub_8086858(object, 0x1471);
            object->secondaryUpdate = sub_8063B80;
            sound_effect_play(0x83, SOUND_VOLUME_UNCHANGED);
            object->update = sub_8063BA8;
        }
    }
}

SEC(sub_8063B2C)
void object_start_animation_7_on_visual_complete(struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 7, 0, 0);
        object->update = sub_8063BF0;
    }
}

SEC(sub_8063C24)
void object_finish_countdown_with_animation_1(struct RuntimeObject* object)
{
    s8* flags;

    object->value84--;
    if (object->value84 <= 0) {
        sub_8082E1C(object, 1, 0, 0);
        flags = (s8*)&object->visual->flags;
        *flags = (*flags & -7) | 2;
        object->update = sub_8063C60;
    }
}

SEC(sub_8064424)
void object_emit_effect_1081_and_finish(struct RuntimeObject* object)
{
    sub_80DF024(0x1081, object->positionX / 0x100,
                object->positionY / 0x100, object->positionZBase / 0x100,
                object);
    sub_807C298(object);
}

SEC(sub_8064488)
void object_start_animation_2_variant_on_ready(struct RuntimeObject* object)
{
    s8* flags;

    if (sub_8082B00(object) == 0) {
        sub_8082E1C(object, 2, 0, 0);
        flags = (s8*)&object->visual->flags;
        *flags = (*flags & -7) | 2;
        if (object->behaviorState == 0) {
            object->update = sub_8064540;
        } else {
            sound_effect_play(0xAF, SOUND_VOLUME_UNCHANGED);
            object->update = sub_8064514;
        }
    }
}

SEC(sub_8064514)
void object_start_animation_3_then_complex_sequence(
    struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 3, 0, 0);
        object->update = sub_8063CC8;
    }
}

SEC(sub_80652D4)
void object_idle_when_link_clears(struct RuntimeObject* object)
{
    if (object->linkedObject == NULL) {
        sub_8082E1C(object, 0, 0, 0);
        object->update = sub_808750C;
    }
}

SEC(sub_8065384)
void object_emit_effect_eff_and_finish(struct RuntimeObject* object)
{
    sound_effect_play(0xAD, SOUND_VOLUME_UNCHANGED);
    sub_80DF024(0xEFF, object->positionX / 0x100,
                object->positionY / 0x100, object->positionZBase / 0x100,
                object);
    sub_807C298(object);
}

SEC(sub_80653F4)
void object_start_animation_2_then_effect_sequence(
    struct RuntimeObject* object)
{
    if (sub_8082B00(object) == 0) {
        sub_8082E1C(object, 2, 0, 0);
        object->update = sub_8064E30;
    }
}

SEC(sub_8063384)
void object_emit_effect_12cd_release_shared_motion_and_finish(
    struct RuntimeObject* object)
{
    sub_80DF024(0x12CD, object->positionX / 0x100,
                object->positionY / 0x100, object->positionZBase / 0x100,
                object);
    free_heap_8018DA8(SHARED_MOTION_HANDLE);
    sub_807C298(object);
}

SEC(sub_80633D0)
void object_emit_effect_12cd_stop_release_and_finish(
    struct RuntimeObject* object)
{
    sub_80DF024(0x12CD, object->positionX / 0x100,
                object->positionY / 0x100, object->positionZBase / 0x100,
                object);
    object->update = NULL;
    free_heap_8018DA8(SHARED_MOTION_HANDLE);
    sub_807C298(object);
}

SEC(sub_8063420)
void object_start_animation_2_and_effect_12a3_when_ready(
    struct RuntimeObject* object)
{
    if (sub_8082B00(object) == 0) {
        sub_8082E1C(object, 2, 0, 0);
        sub_80DF024(0x12A3, object->positionX / 0x100,
                    object->positionY / 0x100,
                    object->positionZBase / 0x100, object);
        object->update = sub_8063474;
    }
}

SEC(sub_80639C0)
void object_restore_saved_xy_and_start_animation_6(
    struct RuntimeObject* object)
{
    s32 x;
    s32 y;

    if (object->linkedObject == NULL) {
        x = object->value84;
        object->currentPositionX = x;
        object->positionX = x;
        /* unknown88 is the saved Y companion to value84 in this sequence. */
        y = *(s32*)object->unknown88;
        object->currentPositionY = y;
        object->positionY = y;
        sub_80DF024(0x1296, x / 0x100, y / 0x100 + 2,
                    object->positionZBase / 0x100, object);
        sub_8082E1C(object, 6, 0, 0);
        object->update = sub_8063B2C;
    }
}

SEC(sub_8063BF0)
void object_move_left_2_until_screen_exit(struct RuntimeObject* object)
{
    s32 oldPosition;
    s32 roundedPosition;

    oldPosition = object->currentPositionX;
    object->currentPositionX = oldPosition - 0x200;
    roundedPosition = object->currentPositionX;
    if (roundedPosition < 0)
        roundedPosition = oldPosition - 0x101;
    if ((roundedPosition >> 8) < -0x20) {
        object->currentPositionX = 0x10000;
        object->update = sub_808750C;
    }
}

SEC(sub_80643DC)
void object_move_left_and_down_slow_until_screen_exit(
    struct RuntimeObject* object)
{
    s32 oldX;
    s32 newX;
    s32 oldZ;
    s32 newZ;
    s32 roundedZ;

    oldX = object->currentPositionX;
    object->currentPositionX = oldX - 0x219;
    newX = object->currentPositionX;
    oldZ = object->verticalPosition;
    object->verticalPosition = oldZ - 0x100;
    newZ = object->verticalPosition;
    if (newX < 0)
        newX = oldX - 0x11A;
    if ((newX >> 8) > -0x20) {
        roundedZ = newZ;
        if (roundedZ < 0)
            roundedZ = oldZ - 1;
        if ((roundedZ >> 8) > 0)
            return;
    }
    sub_807C298(object);
}

SEC(sub_80644DC)
void object_count_to_15_then_stop_on_visual_complete(
    struct RuntimeObject* object)
{
    object->timer++;
    if (object->timer == 15)
        sound_effect_play(0xB5, SOUND_VOLUME_UNCHANGED);
    if (object->visual->flags & 8)
        object->update = NULL;
}
/* The reference uses zero fill, not a Thumb NOP, for this alignment slot. */
SEC(sub_80644DC)
const u16 sub_80644DC_padding = 0;

SEC(sub_8064B88)
void object_update_accelerating_arc_until_x_threshold(
    struct RuntimeObject* object)
{
    object->visual->value0C += 0x1000;
    /* behaviorState is used as horizontal velocity in this callback. */
    object->currentPositionX -= object->behaviorState;
    object->behaviorState -= 0x11;
    object->currentPositionY += object->valueA0;
    if (object->currentPositionX > 0x4000) {
        object->secondaryTimer =
            (object->value84 - object->positionX) / 0x100;
        /* unknown88 remains typed conservatively despite its saved-Y use. */
        object->stateValueB0 =
            (*(s32*)object->unknown88 - object->positionY) / 0x100;
        object->update = sub_8064C00;
    }
}

SEC(sub_8065310)
s32 object_start_animation_3_when_state_clears(struct RuntimeObject* object)
{
    s32 state;

    state = sub_80871A8(object);
    if (state == 0) {
        sub_8082E1C(object, 3, 0, 0);
        object->update = sub_80651B0;
    }
    return state;
}

SEC(sub_8065D10)
void object_start_animation_9_effect_112b_on_visual_complete(
    struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 9, 0, 0);
        sub_80DF024(0x112B, object->positionX / 0x100,
                    object->positionY / 0x100,
                    object->positionZBase / 0x100, object);
        sub_8065758(object);
        sound_effect_play(0x9C, SOUND_VOLUME_UNCHANGED);
        object->update = sub_8065DD4;
    }
}


SEC(sub_8068074)
void object_move_left_until_screen_exit(struct RuntimeObject* object)
{
    s32 oldPosition;
    s32 roundedPosition;

    oldPosition = object->currentPositionX;
    object->currentPositionX = oldPosition - 0x133;
    roundedPosition = object->currentPositionX;
    if (roundedPosition < 0)
        roundedPosition = oldPosition - 0x34;
    if ((roundedPosition >> 8) <= -0x20)
        sub_807C298(object);
}

SEC(sub_80680A0)
void object_start_animation_6_when_value80_clears(struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        sub_8082E1C(object, 6, 0, 0);
        object->secondaryTimer = (s16)object->behaviorState;
        object->update = sub_806822C;
    }
}

SEC(sub_806819C)
void object_move_left_and_down_until_screen_exit(struct RuntimeObject* object)
{
    s32 oldX;
    s32 newX;
    s32 oldZ;
    s32 newZ;
    s32 roundedZ;

    oldX = object->currentPositionX;
    object->currentPositionX = oldX - 0x133;
    newX = object->currentPositionX;
    oldZ = object->verticalPosition;
    object->verticalPosition = oldZ - 0x200;
    newZ = object->verticalPosition;
    if (newX < 0)
        newX = oldX - 0x34;
    if ((newX >> 8) > -0x20) {
        roundedZ = newZ;
        if (roundedZ < 0)
            roundedZ = oldZ - 0x101;
        if ((roundedZ >> 8) > 0)
            return;
    }
    sub_807C298(object);
}


SEC(sub_80687EC)
void object_move_left_fast_until_screen_exit(struct RuntimeObject* object)
{
    s32 oldPosition;
    s32 roundedPosition;

    oldPosition = object->currentPositionX;
    object->currentPositionX = oldPosition - 0x233;
    roundedPosition = object->currentPositionX;
    if (roundedPosition < 0)
        roundedPosition = oldPosition - 0x134;
    if ((roundedPosition >> 8) <= -0x20)
        sub_807C298(object);
}



SEC(sub_806C800)
void object_repeat_animation_until_behavior_count_expires(
    struct RuntimeObject* object)
{
    RuntimeObjectCallback next;

    if (object->visual->flags & 8) {
        sub_8082E1C(object, 0, 0, 0);
        object->behaviorState--;
        if (object->behaviorState <= 0) {
            next = NULL;
        } else {
            object->timer = (s16)object->valueA4;
            next = sub_806CAC0;
        }
        object->update = next;
    }
}


SEC(sub_806CB3C)
void object_finish_visual_and_stop_update(struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 0, 0, 0);
        object->visual->parameter20 = 0x10;
        object->update = NULL;
    }
}

/* The reference uses zero fill, not a Thumb NOP, for this alignment slot. */
SEC(sub_806CB3C)
const u16 sub_806CB3C_padding = 0;

SEC(sub_806E690)
s32 object_release_position_owner_and_continue(struct RuntimeObject* object)
{
    RuntimeObjectCallback callback;

    /* positionOwner is RuntimeObject-shaped for this callback chain. */
    callback = ((struct RuntimeObject*)object->positionOwner)->cleanup;
    if (callback != NULL)
        callback((struct RuntimeObject*)object->positionOwner);
    ((struct RuntimeObject*)object->positionOwner)->update =
        (RuntimeObjectCallback)nullsub_15;
    object->update = sub_806DD48;
    return 0;
}

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
        object->update = sub_8069558;
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
        *(s32*)object->unknown88 = (s32)*(s16*)((u8*)object + 0xB0) << 8;
        object->value8C = (s32)*(s16*)((u8*)object + 0xB2) << 8;
        flags = object->flags79;
        flags |= 0x20;
        object->flags79 = flags;
        object->unknown7C = 0x300;
        object->unknown7A = (s16)zero;
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
    object->unknown7C = 0x199;
    flags = object->flags79;
    flags |= 0x20;
    object->flags79 = flags;
    object->unknown7A = 0;
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
    object->unknown7C = 0x100;
    flags = object->flags79;
    flags |= 0x20;
    object->flags79 = flags;
    object->unknown7A = 0;
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
        object->unknown7C = 0x199;
        flags = object->flags79;
        flags |= 0x20;
        object->flags79 = flags;
        object->unknown7A = 0;
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

SEC(sub_8077140)
s32 object_forward_owner_emit_effect_25b9_and_finish(
    struct RuntimeObject* object, void* owner)
{
    sub_810DD7C(object, owner, 0xFF);
    sub_80DF024(0x25B9, object->positionX / 0x100,
                object->positionY / 0x100,
                object->positionZBase / 0x100, object);
    sub_807C298(object);
    return 0;
}

SEC(sub_8077188)
void object_emit_effect_25ab_and_finish_when_value80_clears(
    struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        sub_80DF024(0x25AB, object->positionX / 0x100,
                    object->positionY / 0x100,
                    object->positionZBase / 0x100, object);
        sound_effect_play(0x76, SOUND_VOLUME_UNCHANGED);
        sub_807C298(object);
    }
}

SEC(sub_80772F0)
void object_finish_linked_visual_and_emit_effect_2515(
    struct RuntimeObject* object)
{
    struct RuntimeObject* linked = object->linkedObject;
    if (linked->visual->flags & 8) {
        sub_807C298(linked);
        sub_8082E1C(object, 8, 0, 0);
        sub_80DF024(0x2515, object->positionX / 0x100,
                    object->positionY / 0x100,
                    object->positionZBase / 0x100, object);
        object->update = sub_80775A4;
    }
}

SEC(sub_8077350)
void object_prepare_linked_animation_on_visual_complete(
    struct RuntimeObject* object)
{
    struct RuntimeObject* linked = object->linkedObject;
    if (linked->visual->flags & 8) {
        sub_8082E1C(linked, 1, 0, 0);
        object->timer = 20;
        object->stateValueB0 = 0;
        object->secondaryTimer = 0;
        object->update = sub_80764D8;
    }
}

SEC(sub_8077390)
void object_emit_periodic_effect_24e9_until_valueA4_clears(
    struct RuntimeObject* object)
{
    object->valueA8--;
    if (object->valueA8 <= 0) {
        sub_80DF024(0x24E9, object->positionX / 0x100,
                    object->positionY / 0x100,
                    object->positionZBase / 0x100, object);
        object->valueA8 = 10;
    }
    if (object->valueA4 == 0)
        object->update = sub_8077610;
}

SEC(sub_80773EC)
void object_start_animation_4_and_effect_25f5_on_visual_complete(
    struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 4, 0, 0);
        sub_80DF024(0x25F5, object->positionX / 0x100,
                    object->positionY / 0x100,
                    object->positionZBase / 0x100, object);
        object->update = sub_8076338;
    }
}

SEC(sub_80774A4)
void object_start_random_animation_3_or_5(struct RuntimeObject* object)
{
    object->behaviorState = sub_8199F30() & 1;
    if (object->behaviorState == 0)
        sub_8082E1C(object, 3, 0, 0);
    else
        sub_8082E1C(object, 5, 0, 0);
    object->update = sub_8076D90;
}

SEC(sub_80774E4)
void object_start_animation_13_effect_2563_and_sound_4b(
    struct RuntimeObject* object)
{
    sub_8082E1C(object, 13, 0, 0);
    sub_80DF024(0x2563, object->positionX / 0x100,
                object->positionY / 0x100,
                object->positionZBase / 0x100, object);
    sound_effect_play(0x4B, SOUND_VOLUME_UNCHANGED);
    object->update = sub_80776B4;
}

SEC(sub_8077554)
void object_remove_linked_chain_and_stop(struct RuntimeObject* object)
{
    while (object->linkedObject != NULL)
        sub_807C298(object->linkedObject);
    object->update = NULL;
}

SEC(sub_80775A4)
void object_emit_effect_24e0_for_linked_chain_on_visual_complete(
    struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 0, 0, 0);
        while (object->linkedObject != NULL) {
            struct RuntimeObject* linked = object->linkedObject;
            sub_80DF024(0x24E0, linked->positionX / 0x100,
                        linked->positionY / 0x100,
                        linked->positionZBase / 0x100, object);
            sub_807C298(object->linkedObject);
        }
        object->update = NULL;
    }
}

SEC(sub_8077610)
void object_start_animation_6_and_effect_24fb_on_visual_complete(
    struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 6, 0, 0);
        sub_80DF024(0x24FB, object->positionX / 0x100,
                    object->positionY / 0x100,
                    object->positionZBase / 0x100, object);
        object->update = sub_8076414;
    }
}

SEC(sub_8077668)
void object_start_animation_2_and_effect_24ba(struct RuntimeObject* object)
{
    sub_8082E1C(object, 2, 0, 0);
    sub_80DF024(0x24BA, object->positionX / 0x100,
                object->positionY / 0x100,
                object->positionZBase / 0x100, object);
    object->update = sub_80761E8;
}

SEC(sub_80776B4)
void object_prepare_animation_14_sequence_on_visual_complete(
    struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 14, 0, 0);
        object->timer = object->behaviorState;
        object->behaviorState = 50;
        object->valueA0 = 20;
        object->valueA8 = 0;
        object->verticalVelocity = 3;
        object->update = sub_8076C14;
    }
}

SEC(sub_8077704)
void object_emit_effect_2983_after_visual_countdown(
    struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        object->timer--;
        if (object->timer <= 0) {
            sub_8082E1C(object, 11, 0, 0);
            sound_effect_play(0x89, SOUND_VOLUME_UNCHANGED);
            sub_80DF024(0x2983, object->positionX / 0x100,
                        object->positionY / 0x100,
                        object->positionZBase / 0x100, object);
            object->timer = 60;
            object->update = sub_807777C;
        }
    }
}

SEC(sub_80778D4)
void object_advance_dual_sound_and_animation_timers(
    struct RuntimeObject* object)
{
    object->secondaryTimer--;
    if (object->secondaryTimer <= 0) {
        sound_effect_play(0x54, SOUND_VOLUME_UNCHANGED);
        object->secondaryTimer = 10;
    }
    object->timer--;
    if (object->timer <= 0) {
        sub_8082E1C(object, 17, 0, 0);
        object->timer = 100;
        object->update = sub_8077924;
    }
}
