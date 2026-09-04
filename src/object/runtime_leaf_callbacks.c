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
void sub_806819C(struct RuntimeObject* object);
void sub_808750C(struct RuntimeObject* object);
void nullsub_15(void);
s32 sub_8082B00(struct RuntimeObject* object);
s32 sub_80871A8(struct RuntimeObject* object);
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
