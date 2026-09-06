#include "global.h"
#include "audio/sound_effects.h"
#include "object/runtime_object.h"
#include "object/functions.h"

#define SEC(name) __attribute__((section(".text.object_late_visual_transitions." #name)))
#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define UPPER_SEC(name) __attribute__((section(".text.upper." STRINGIFY(name))))
#define object_on_visual_complete_delay_12 sub_810FEF4

void sub_8082E1C(struct RuntimeObject*, s32, s32, s32);
void sub_80883A0(struct RuntimeObject*, s32);
s32 sub_8086C64(void);
void sub_808843C(struct RuntimeObject*, s32, s32, s32, s32);
void sub_80880C4(struct RuntimeObject*, s32);
u8 sub_8087CE4();
void sub_807FB64(struct RuntimeObjectVisual*);
void sub_807C298(struct RuntimeObject*);
void sub_807F4FC(struct RuntimeObject*);
void sub_8086858(struct RuntimeObject*, s32);
void sub_80DF024(s32, s32, s32, s32, struct RuntimeObject*);
void sub_810DD7C(struct RuntimeObject*, struct RuntimeObject*, s32);
u8 sub_80883F0(struct RuntimeObject*);
void sub_810F824(struct RuntimeObject*);
void sub_810FD54(struct RuntimeObject*);
void sub_810FD94(struct RuntimeObject*);
void sub_810FCE0(struct RuntimeObject*);
void sub_810FF18(struct RuntimeObject*);
void sub_810FC34(struct RuntimeObject*);
void sub_810FC70(struct RuntimeObject*);
void sub_810FBC4(struct RuntimeObject*);
void sub_810FE44(struct RuntimeObject*);
void sub_810FE94(struct RuntimeObject*);
void sub_810FB20(struct RuntimeObject*);
void sub_810FFB0(struct RuntimeObject*);
void sub_8110134(struct RuntimeObject*);
void sub_8110178(struct RuntimeObject*);
void sub_810F764(struct RuntimeObject*);
void sub_81101BC(struct RuntimeObject*);
void sub_8110A30(struct RuntimeObject*);
void sub_811108C(struct RuntimeObject*);
void sub_8111174(struct RuntimeObject*);
void sub_81111C0(struct RuntimeObject*);
void sub_8110CB0(struct RuntimeObject*);
void sub_81112C4(struct RuntimeObject*);
void sub_8111754(struct RuntimeObject*);
void sub_8112450(struct RuntimeObject*);
void sub_8112498(struct RuntimeObject*);
void sub_811254C(struct RuntimeObject*);
s32 sub_8087124(struct RuntimeObject*);
void sub_81125CC(struct RuntimeObject*);
void sub_8112D78(struct RuntimeObject*);
void sub_8114404(struct RuntimeObject*);

void object_on_visual_complete_delay_12(struct RuntimeObject*);
void sub_81109D0(struct RuntimeObject*);
void sub_8110A94(struct RuntimeObject*);
void sub_81127B8(struct RuntimeObject*);
void sub_81135C0(struct RuntimeObject*);
void sub_8132594(struct RuntimeObject*);

struct ObjectPositionSource {
    u8 unknown00[0xD8];
    s32 positionX;
    s32 positionY;
    s32 positionZ;
};

struct ObjectPositionOwner {
    u8 unknown00[0x28];
    struct ObjectPositionSource* positionSource;
};


SEC(sub_810FD10) void sub_810FD10(struct RuntimeObject* object)
{
    struct RuntimeObject* linked = object->linkedObject;

    if (linked->visual->flags & 8) {
        sub_8082E1C(linked, 0, 0, 0);
        sub_80883A0(object, 0xC);
        sound_effect_play(0x10F, SOUND_VOLUME_UNCHANGED);
        object->update = sub_810F824;
    }
}

SEC(sub_810F6D4)
void object_start_owner_position_effect_and_continue(
    struct RuntimeObject* object)
{
    struct RuntimeObject* owner;
    struct RuntimeObjectState* state;

    if (object->visual->flags & 8) {
        owner = object->positionOwner;
        state = owner->state;
        sub_808843C(object, state->valueD8 / 256 + 0x22,
                    state->valueDC / 256, state->floorHeight / 256, 0x100);
        sub_80880C4(object, object->valueA0);
        sub_8082E1C(object, 5, 0, 0);
        object->visual->parameter20 = object->valueA4;
        sound_effect_play(0x112, SOUND_VOLUME_UNCHANGED);
        object->update = sub_810FD54;
    }
}

SEC(sub_810F5E4)
void object_start_owner_position_effect_variant_and_continue(
    struct RuntimeObject* object)
{
    struct RuntimeObject* owner;
    struct RuntimeObjectState* state;

    if (object->visual->flags & 8) {
        owner = object->positionOwner;
        state = owner->state;
        object->unknown75 = owner->unknown75 - 1;
        if (object->behaviorState != 0) {
            sub_808843C(object, state->valueD8 / 256 + 0x2A,
                        state->valueDC / 256, state->floorHeight / 4096,
                        0x100);
            object->update = sub_810FD94;
        } else {
            sub_808843C(object, state->valueD8 / 256 + 0x22,
                        state->valueDC / 256, state->floorHeight / 256,
                        0x100);
            object->update = object_finish_owner_position_effect_when_ready;
        }
        sub_80880C4(object, object->valueA0);
        sub_8082E1C(object, 5, 0, 0);
        object->visual->parameter20 = object->valueA4;
        sound_effect_play(0x112, SOUND_VOLUME_UNCHANGED);
    }
}

SEC(sub_810F824)
void object_finish_paired_owner_effect(struct RuntimeObject* object)
{
    struct RuntimeObject* owner = object->positionOwner;
    struct RuntimeObject* linked;
    s32 effect;

    if (!(owner->flags76 & 0x80) && owner->verticalPosition == 0)
        sub_810DD7C(object, owner, 0xFF);

    if (sub_80883F0(object) == 0) {
        linked = object->linkedObject;
        effect = object->state->variant == 0x3C ? 0x2165 : 0x216E;
        sub_80DF024(effect, linked->positionX / 256,
                    linked->positionY / 256, linked->positionZBase / 256,
                    linked);
        sub_807C298(linked);
        sound_effect_stop(0x10F);
        sub_808843C(object, object->state->valueD8 / 256,
                    object->state->valueDC / 256,
                    object->state->floorHeight / 256, 0x100);
        sub_80880C4(object, 0x300);
        sound_effect_play(0x11B, SOUND_VOLUME_UNCHANGED);
        object->update = sub_810FCE0;
    }
}

SEC(sub_810F904)
void object_start_owner_position_effect_with_auxiliary(
    struct RuntimeObject* object)
{
    struct RuntimeObject* owner;
    struct RuntimeObjectState* state;

    if (object->visual->flags & 8) {
        owner = object->positionOwner;
        state = owner->state;
        object->unknown75 = owner->unknown75 - 1;
        if (object->behaviorState != 0) {
            sub_808843C(object, state->valueD8 / 256 + 0x2A,
                        state->valueDC / 256, state->floorHeight / 256,
                        0x100);
            object->update = sub_810FC70;
        } else {
            sub_808843C(object, state->valueD8 / 256 + 0x22,
                        state->valueDC / 256, state->floorHeight / 256,
                        0x100);
            object->update = sub_810FC34;
        }
        sub_80880C4(object, object->valueA0);
        sub_8082E1C(object, 5, 0, 0);
        object->visual->parameter20 = object->valueA4;
        sound_effect_play(0x112, SOUND_VOLUME_UNCHANGED);
        sub_807F4FC(object);
        object->tertiaryUpdate = sub_810FBC4;
    }
}

SEC(sub_810F9FC)
void object_start_owner_position_effect_to_visual_reset(
    struct RuntimeObject* object)
{
    struct RuntimeObject* owner;
    struct RuntimeObjectState* state;

    if (object->visual->flags & 8) {
        owner = object->positionOwner;
        state = owner->state;
        sub_808843C(object, state->valueD8 / 256 + 0x22,
                    state->valueDC / 256, state->floorHeight / 256, 0x100);
        sub_80880C4(object, object->valueA0);
        sub_8082E1C(object, 5, 0, 0);
        object->visual->parameter20 = object->valueA4;
        sound_effect_play(0x112, SOUND_VOLUME_UNCHANGED);
        object->update = object_reset_owner_position_visual_when_ready;
    }
}

SEC(sub_810FC34)
void object_reset_owner_position_visual_when_ready(
    struct RuntimeObject* object)
{
    volatile u8* flags;
    s32 value;
    s32 mask;

    if (sub_8087CE4() == 0) {
        flags = &object->visual->flags;
        value = *flags;
        mask = -7;
        value &= mask;
        value |= 2;
        *flags = value;
        sub_80883A0(object, 0x28);
        sound_effect_stop(0x112);
        object->update = sub_810FE44;
    }
}

SEC(sub_810FA8C)
void object_start_fixed_position_effect_with_auxiliary(
    struct RuntimeObject* object)
{
    struct RuntimeObjectState* state;

    if (object->visual->flags & 8) {
        state = ((struct RuntimeObject*)object->positionOwner)->state;
        sub_808843C(object, -0x20, state->valueDC / 256,
                    state->floorHeight / 256, 0x100);
        sub_80880C4(object, 0x300);
        sub_8082E1C(object, 0xC, 0, 0);
        object->unknown75 =
            ((struct RuntimeObject*)object->positionOwner)->unknown75 - 1;
        sub_8086858(object, 0x1830);
        object->tertiaryUpdate = (RuntimeObjectCallback)0x0810FBBD;
        sound_effect_play(0x86, SOUND_VOLUME_UNCHANGED);
        object->update = sub_810FB20;
    }
}

SEC(sub_810FC70)
void object_finish_owner_position_effect_with_delayed_spawn(
    struct RuntimeObject* object)
{
    volatile u8* flags;
    s32 value;
    s32 mask;

    if (sub_8087CE4() == 0) {
        sub_8082E1C(object, 6, 0, 0);
        flags = &object->visual->flags;
        value = *flags;
        mask = -7;
        value &= mask;
        value |= 2;
        *flags = value;
        sound_effect_stop(0x112);
        sub_80DF024(0x215C, object->positionX / 256,
                    object->positionY / 256, object->positionZBase / 256,
                    object);
        object->update = sub_810FE94;
    }
}

SEC(sub_810FEC8)
void object_start_animation_2_then_owner_offset_effect(
    struct RuntimeObject* object)
{
    volatile u8* flags;
    s32 value;
    s32 mask;

    sub_8082E1C(object, 2, 0, 0);
    flags = &object->visual->flags;
    value = *flags;
    mask = -7;
    value &= mask;
    value |= 2;
    *flags = value;
    object->update = sub_810FFB0;
}

SEC(sub_810FFB0)
void object_start_far_owner_position_effect(struct RuntimeObject* object)
{
    struct RuntimeObject* owner;
    struct RuntimeObjectState* state;

    if (object->visual->flags & 8) {
        owner = object->positionOwner;
        state = owner->state;
        sub_808843C(object, state->valueD8 / 256 + 0x44,
                    state->valueDC / 256, state->floorHeight / 256, 0x100);
        sub_80880C4(object, 0x280);
        sub_8082E1C(object, 3, 0, 0);
        sound_effect_play(0x11B, SOUND_VOLUME_UNCHANGED);
        object->update = sub_8110134;
    }
}

SEC(sub_8110034)
void object_countdown_then_start_paired_owner_effect(
    struct RuntimeObject* object)
{
    volatile u8* flags;
    s32 value;
    s32 mask;

    if (object->timer != 0) {
        object->timer--;
    } else {
        sub_8082E1C(object, 0x10, 0, 0);
        flags = &object->visual->flags;
        value = *flags;
        mask = -7;
        value &= mask;
        value |= 2;
        *flags = value;
        object->update = sub_810F764;
    }
}

SEC(sub_81100B0)
void object_start_far_owner_position_effect_variant(
    struct RuntimeObject* object)
{
    struct RuntimeObject* owner;
    struct RuntimeObjectState* state;

    if (object->visual->flags & 8) {
        owner = object->positionOwner;
        state = owner->state;
        sub_808843C(object, state->valueD8 / 256 + 0x44,
                    state->valueDC / 256, state->floorHeight / 256, 0x100);
        sub_80880C4(object, 0x280);
        sub_8082E1C(object, 3, 0, 0);
        sound_effect_play(0x11B, SOUND_VOLUME_UNCHANGED);
        object->update = sub_8110178;
    }
}

SEC(sub_8110134)
void object_return_to_auxiliary_owner_effect_when_ready(
    struct RuntimeObject* object)
{
    volatile u8* flags;
    s32 value;
    s32 mask;

    if (sub_8087CE4() == 0) {
        sub_8082E1C(object, 4, 0, 0);
        flags = &object->visual->flags;
        value = *flags;
        mask = -7;
        value &= mask;
        value |= 2;
        *flags = value;
        sound_effect_stop(0x11B);
        object->update = object_start_owner_position_effect_with_auxiliary;
    }
}

SEC(sub_8110178)
void object_return_to_variant_owner_effect_when_ready(
    struct RuntimeObject* object)
{
    volatile u8* flags;
    s32 value;
    s32 mask;

    if (sub_8087CE4() == 0) {
        sub_8082E1C(object, 4, 0, 0);
        flags = &object->visual->flags;
        value = *flags;
        mask = -7;
        value &= mask;
        value |= 2;
        *flags = value;
        sound_effect_stop(0x11B);
        object->update = object_start_owner_position_effect_variant_and_continue;
    }
}

SEC(sub_8110948)
void object_stop_when_visual_complete(struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        sub_8082E1C(object, -1, -1, 0);
        object->update = 0;
    }
}

SEC(sub_81109F4)
void object_prepare_vector_setup_from_owner_state(struct RuntimeObject* object)
{
    volatile u8* flags;
    s32 value;
    s32 mask;

    sub_8082E1C(object, 2, 0, 0);
    flags = &object->visual->flags;
    value = *flags;
    mask = -7;
    value &= mask;
    value |= 2;
    *flags = value;
    object->state->value113 = 0;
    object->update = sub_81101BC;
}

SEC(sub_811104C)
void object_start_owner_variant_animation_11_or_12(
    struct RuntimeObject* object)
{
    struct RuntimeObject* owner = object->positionOwner;
    s32 variant;
    s32 animation;
    volatile u8* flags;
    s32 value;
    s32 mask;

    variant = owner->state->variant;
    variant = -variant;
    animation = 0x11;
    if (variant != 1)
        animation = 0x12;
    sub_8082E1C(object, animation, 0, 0);
    flags = &object->visual->flags;
    value = *flags;
    mask = -7;
    value &= mask;
    value |= 2;
    *flags = value;
    object->update = object_continue_owner_variant_animation_10_or_11;
}

SEC(sub_8111174)
void object_continue_owner_variant_animation_10_or_11(
    struct RuntimeObject* object)
{
    struct RuntimeObject* owner;
    s32 variant;
    s32 animation;
    volatile u8* flags;
    s32 value;
    s32 mask;

    if (object->visual->flags & 8) {
        owner = object->positionOwner;
        variant = -owner->state->variant;
        animation = 0xA;
        if (variant != 1)
            animation = 0xB;
        sub_8082E1C(object, animation, 0, 0);
        flags = &object->visual->flags;
        value = *flags;
        mask = -7;
        value &= mask;
        value |= 2;
        *flags = value;
        object->update = sub_811108C;
    }
}

SEC(sub_81111C0)
void object_finish_owner_variant_animation_4_or_7(
    struct RuntimeObject* object)
{
    struct RuntimeObject* owner;
    s32 variant;
    s32 animation;
    volatile u8* flags;
    s32 value;
    s32 mask;

    if (object->visual->flags & 8) {
        owner = object->positionOwner;
        variant = -owner->state->variant;
        animation = 4;
        if (variant != 1)
            animation = 7;
        sub_8082E1C(object, animation, 0, 0);
        flags = &object->visual->flags;
        value = *flags;
        mask = -7;
        value &= mask;
        value |= 2;
        *flags = value;
        object->update = sub_8110CB0;
        sound_effect_stop(0x89);
    }
}

SEC(sub_8111234)
void object_on_visual_complete_spawn_effect_2669(
    struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        object->secondaryTimer = 0x17;
        object->stateValueB0 = 0;
        sub_808843C(object, 0x60 - object->secondaryTimer / 2,
                    0x6C, 0, 0x100);
        sub_80880C4(object, 0x300);
        sub_8082E1C(object, 0xA, 0, 0);
        sub_80DF024(0x2669, object->positionX / 256,
                    object->positionY / 256, object->positionZBase / 256,
                    object);
        object->update = sub_81112C4;
    }
}

SEC(sub_81116C0)
void object_on_visual_complete_countdown_effect_2700(
    struct RuntimeObject* object)
{
    volatile u8* flags;
    s32 value;
    s32 mask;

    if (object->visual->flags & 8) {
        object->valueA8--;
        if (object->valueA8 != 0) {
            if (object->timer == 0) {
                sub_80DF024(0x2700, object->positionX / 256,
                            object->positionY / 256,
                            object->positionZBase / 256, object);
                object->timer = 999;
            }
            object->timer--;
        } else {
            sub_8082E1C(object, 5, 0, 0);
            flags = &object->visual->flags;
            value = *flags;
            mask = -7;
            value &= mask;
            value |= 2;
            *flags = value;
            object->update = sub_8111754;
        }
    }
}

SEC(sub_8112030)
void object_on_visual_complete_start_animation_4_timer_32(
    struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 4, 0, 0);
        object->timer = 0x20;
        object->update = sub_8112450;
    }
}

SEC(sub_811213C)
void object_when_timer_active_start_animation_13(
    struct RuntimeObject* object)
{
    volatile u8* flags;
    s32 value;
    s32 mask;

    if (object->timer != 0) {
        sub_8082E1C(object, 0xD, 0, 0);
        flags = &object->visual->flags;
        value = *flags;
        mask = -7;
        value &= mask;
        value |= 2;
        *flags = value;
        object->update = object_on_visual_complete_increment_timer_then_continue;
    }
}

SEC(sub_81122D0)
void object_on_visual_complete_start_animation_13(
    struct RuntimeObject* object)
{
    volatile u8* flags;
    s32 value;
    s32 mask;

    if (object->visual->flags & 8) {
        sub_8082E1C(object, 0xD, 0, 0);
        flags = &object->visual->flags;
        value = *flags;
        mask = -7;
        value &= mask;
        value |= 2;
        *flags = value;
        object->update = object_on_visual_complete_animation_14_variant_a;
    }
}

SEC(sub_811230C)
void object_start_state_variant_animation_1(struct RuntimeObject* object)
{
    s32 variant;

    variant = -object->state->variant;
    if (variant != 1) {
        sub_8082E1C(object, 1, 0x2057, 0);
    } else {
        sub_8082E1C(object, 1, 0x2028, 0);
    }
    object->update = (RuntimeObjectCallback)0x081125C9;
}

SEC(sub_8112394)
s32 object_continue_when_motion_helper_clear(struct RuntimeObject* object)
{
    s32 result = sub_8087124(object);

    if (result == 0) {
        object->update = sub_81125CC;
        return 0;
    }
    return result;
}

SEC(sub_8112984)
void object_stop_animation_and_sound_11b_when_ready_variant_b(
    struct RuntimeObject* object)
{
    u8 result = sub_8087CE4(object);

    if (result == 0) {
        sub_8082E1C(object, -1, -1, 0);
        object->update = 0;
        sound_effect_stop(0x11B);
    }
}

SEC(sub_81127FC)
void object_complete_profile_position_animation_2(
    struct RuntimeObject* object)
{
    volatile u8* flags;
    s32 value;
    s32 mask;

    if (sub_8087CE4(object) == 0) {
        sub_8082E1C(object, 3, 0, 0);
        flags = &object->visual->flags;
        value = *flags;
        mask = -7;
        value &= mask;
        value |= 2;
        *flags = value;
        object->update = object_on_profile_position_complete_start_effect_countdown;
        sound_effect_stop(0x11B);
    }
}

SEC(sub_81129B4)
void object_on_profile_position_complete_start_effect_countdown(
    struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 4, 0, 0);
        sub_80DF024(0x2700, object->positionX / 256,
                    object->positionY / 256,
                    object->positionZBase / 256, object);
        object->timer = 0;
        object->valueA8 = 4;
        object->update = object_on_visual_complete_countdown_effect_2700;
        sound_effect_play(0x116, SOUND_VOLUME_UNCHANGED);
    }
}

SEC(sub_8113458)
void object_after_visual_complete_delay_2_start_animation_23(
    struct RuntimeObject* object)
{
    volatile u8* flags;
    s32 value;
    s32 mask;

    if (object->visual->flags & 8) {
        if (object->timer != 0) {
            object->timer--;
        } else {
            sub_8082E1C(object, 0x17, 0, 0);
            flags = &object->visual->flags;
            value = *flags;
            mask = -7;
            value &= mask;
            value |= 2;
            *flags = value;
            object->update = sub_8112D78;
        }
    }
}

SEC(sub_8113E44)
void object_on_visual_complete_start_animation_1_timer_40(
    struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 1, 0, 0);
        object->timer = 0x28;
        object->update = sub_8114404;
    }
}

SEC(sub_8112578)
void object_start_profile_position_animation_2(struct RuntimeObject* object)
{
    sub_808843C(object, object->behaviorState, object->valueA0, 0, 0x100);
    sub_80880C4(object, 0x300);
    sub_8082E1C(object, 2, 0, 0);
    object->update = object_complete_profile_position_animation_2;
    sound_effect_play(0x11B, SOUND_VOLUME_UNCHANGED);
}





SEC(sub_810FD54)
void object_finish_owner_position_effect_when_ready(
    struct RuntimeObject* object)
{
    volatile u8* flags;
    s32 value;
    s32 mask;

    if (sub_8087CE4() == 0) {
        sub_8082E1C(object, 0xF, 0, 0);
        flags = &object->visual->flags;
        value = *flags;
        mask = -7;
        value &= mask;
        value |= 2;
        *flags = value;
        sound_effect_stop(0x112);
        object->update = object_on_visual_complete_delay_12;
    }
}

SEC(sub_810FD94)
void object_finish_owner_position_effect_with_spawn(
    struct RuntimeObject* object)
{
    volatile u8* flags;
    s32 value;
    s32 mask;

    if (sub_8087CE4() == 0) {
        sub_8082E1C(object, 6, 0, 0);
        flags = &object->visual->flags;
        value = *flags;
        mask = -7;
        value &= mask;
        value |= 2;
        *flags = value;
        sound_effect_stop(0x112);
        sub_80DF024(0x215C, object->positionX / 256,
                    object->positionY / 256, object->positionZBase / 256,
                    object);
        object->update = sub_810FF18;
    }
}

SEC(sub_811090C) s32 sub_811090C(struct RuntimeObject* object)
{
    s32 result = sub_8086C64();
    struct RuntimeObject* linked;

    if (result == 0) {
        linked = object->linkedObject;
        if (linked != 0) {
            do {
                linked->valueA8 = 1;
                linked = linked->linkedObject;
            } while (linked != 0);
        }
        object->update = sub_81109D0;
        sound_effect_stop(0x10F);
        result = 0;
    }
    return result;
}

SEC(sub_81124D0) void sub_81124D0(struct RuntimeObject* object)
{
    sub_808843C(object, 0x8A, 0x6C, 0, 0x100);
    sub_80880C4(object, 0x380);
    sub_8082E1C(object, 0xA, 0, 0);
    object->update = sub_81127B8;
    sound_effect_play(0x11B, SOUND_VOLUME_UNCHANGED);
}

SEC(sub_811448C) void sub_811448C(struct RuntimeObject* object)
{
    u8 result = sub_8087CE4();

    if (result == 0) {
        u8* runtime = *(u8**)0x03000FD8;
        runtime[0xC] |= 0x80;
        sub_8082E1C(object, -1, -1, 0);
        object->visual->parameter20 = 0x10;
        object->update = 0;
    }
}

SEC(sub_8110A30) void sub_8110A30(struct RuntimeObject* object)
{
    struct ObjectPositionOwner* owner;
    struct ObjectPositionSource* source;
    s32 position;

    if (object->visual->flags & 8) {
        sub_80883A0(object, 0x20);
        owner = object->positionOwner;
        source = owner->positionSource;
        position = source->positionX + 0x2000;
        object->currentPositionX = position;
        object->positionX = position;
        position = source->positionY;
        object->currentPositionY = position;
        object->positionY = position;
        position = source->positionZ + 0x800;
        object->verticalPosition = position;
        object->positionZBase = position;
        sub_807FB64(object->visual);
        sound_effect_stop(0x119);
        object->update = sub_8110A94;
    }
}

SEC(sub_811458C) void sub_811458C(struct RuntimeObject* object)
{
    sub_8082E1C(object->linkedObject->linkedObject, 4, 0, 0);
    object->timer = 0x20;
    object->followup = sub_81135C0;
    object->update = (RuntimeObjectCallback)0x081141F5;
    sound_effect_play(0x120, SOUND_VOLUME_UNCHANGED);
}

UPPER_SEC(object_when_global_gate_clear_start_duration_10)
void object_when_global_gate_clear_start_duration_10(
    struct RuntimeObject* object)
{
    if ((sub_8087CE4() << 0x18) == 0) {
        sub_80883A0(object, 0x0A);
        object->update = sub_8132594;
    }
}
