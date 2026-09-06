#include "audio/sound_effects.h"
#include "field/global_object_transitions.h"
#include "object/paired_object_callbacks.h"

#define SEC(symbol) \
    __attribute__((section(".text.paired_object_callbacks." #symbol)))
#define FIELD_OBJECT_RUNTIME (*(struct FieldObjectRuntime**)0x03000FD8)
u8 sub_8087CE4(struct RuntimeObject* object);
void sub_8082E1C(
    struct RuntimeObject* object, s32 animation, s32 command, s32 argument);
void sub_80884AC(struct RuntimeObject* object);
void sub_807C298(struct RuntimeObject* object);
void sub_807FB64(struct RuntimeObjectVisual* visual);
void sub_807FA14(struct RuntimeObject* object);
struct RuntimeObject* sub_807C0D0(
    struct RuntimeObject* object, s32 command, s32 argument);
struct RuntimeObject* sub_807BF34(
    struct RuntimeObjectState* state, s32 command, s32 argument,
    s32 displayOffset, s32 x, s32 y, s32 z);

void sub_80963E4(struct RuntimeObject* object);
void sub_80967A4(struct RuntimeObject* object);
void sub_8096F08(struct RuntimeObject* object);
void sub_8096F60(struct RuntimeObject* object);
void sub_8096FCC(struct RuntimeObject* object);
void sub_8097024(struct RuntimeObject* object);
void sub_809706C(struct RuntimeObject* object);
void sub_80974F8(struct RuntimeObject* object);
void sub_8097648(struct RuntimeObject* object);
void sub_80976D0(struct RuntimeObject* object);
void sub_8097978(struct RuntimeObject* object);
void sub_8097C38(struct RuntimeObject* object);
void sub_8097D50(struct RuntimeObject* object);
void sub_8097DB4(struct RuntimeObject* object);
void sub_8097F10(struct RuntimeObject* object);
void sub_8098198(struct RuntimeObject* object);
void sub_80982DC(struct RuntimeObject* object);
void sub_8098364(struct RuntimeObject* object);
void sub_8098540(struct RuntimeObject* object);
void sub_8098710(struct RuntimeObject* object);
void sub_8098790(struct RuntimeObject* object);
void sub_80987F4(struct RuntimeObject* object);
void sub_8098934(struct RuntimeObject* object);

#define PRIMARY_ACTION_OBJECT \
    (&FIELD_OBJECT_RUNTIME->primaryActionOwner->object)
#define SECONDARY_ACTION_OBJECT \
    (&FIELD_OBJECT_RUNTIME->secondaryActionOwner->object)

SEC(sub_8096364)
void object_finish_motion_copy_owner_position_then_count_down(
    struct RuntimeObject* object)
{
    struct RuntimeObject* primary = PRIMARY_ACTION_OBJECT;
    struct RuntimeObject* owner = object->positionOwner;
    s8* flags;
    s32 command;

    if (sub_8087CE4(object) == 0) {
        if ((object->flags76 & 6) == 2) {
            command = 0x2052;
            if (object == primary)
                command -= 0x2F;
            sub_8082E1C(object, 4, command, 0);
            flags = (s8*)&object->visual->flags;
            *flags = (*flags & -7) | 2;
        }
        object->currentPositionX = owner->currentPositionX;
        object->currentPositionY = owner->currentPositionY;
        object->verticalPosition = owner->verticalPosition;
        object->timer = 0x18;
        sound_effect_play(0xAE, SOUND_VOLUME_UNCHANGED);
        object->update = object_count_down_then_spawn_command_208c;
    }
}

SEC(sub_8096D8C)
void object_start_pair_animation_1_and_spawn_command_208d(
    struct RuntimeObject* object)
{
    struct RuntimeObject* primary = PRIMARY_ACTION_OBJECT;
    struct RuntimeObject* spawned;
    s8* flags;
    s32 command;

    if ((object->flags76 & 6) == 2) {
        command = 0x2051;
        if (object == primary)
            command -= 0x2F;
        sub_8082E1C(object, 1, command, 0);
        flags = (s8*)&object->visual->flags;
        *flags = (*flags & -7) | 2;
    }
    spawned = sub_807C0D0(object, 0, 0);
    sub_8082E1C(spawned, 1, 0x208D, 0);
    spawned->unknown78 = (spawned->unknown78 & 0x1F) | 0x20;
    object->update = sub_80967A4;
}

SEC(sub_8096E08)
void object_update_motion_until_z_base_then_start_animation_6(
    struct RuntimeObject* object)
{
    s8* flags;

    sub_8087CE4(object);
    if (object->positionZBase >= object->verticalPosition) {
        sub_8082E1C(object, 6, -1, 0);
        flags = (s8*)&object->visual->flags;
        *flags = (*flags & -7) | 2;
        object->update = sub_8096F08;
    }
}

SEC(sub_8096E44)
void object_stop_when_motion_poll_clears(struct RuntimeObject* object)
{
    u8 result;

    result = sub_8087CE4(object);
    if (result == 0) {
        sub_8082E1C(object, -1, -1, 0);
        object->update = 0;
    }
}
SEC(sub_8096E44)
const u16 object_stop_when_motion_poll_clears_padding = 0;

SEC(sub_8096E6C)
void object_count_down_then_spawn_command_208c(struct RuntimeObject* object)
{
    if (object->timer > 0) {
        object->timer--;
    } else {
        sub_807C0D0(object, 0x208C, 0);
        object->linkedObject->unknown75 = object->unknown75 - 1;
        sub_8082E1C(object->linkedObject, 0, 0, 0);
        object->update = sub_80963E4;
    }
}

SEC(sub_8096EBC)
void object_finish_position_owner_visual_then_release(
    struct RuntimeObject* object)
{
    struct RuntimeObject* owner;
    s8* flags;
    u8 mode;

    owner = object->positionOwner;
    if (owner->visual->flags & 8) {
        mode = owner->flags76 & 6;
        if (mode == 2 || mode == 4) {
            sub_8082E1C(owner, -1, -1, 0);
            flags = (s8*)&owner->visual->flags;
            *flags &= -7;
        }
        sub_807C298(object);
    }
}
SEC(sub_8096EBC)
const u16 object_finish_position_owner_visual_then_release_padding = 0;

SEC(sub_8096F60)
void object_count_down_then_start_pair_animation_7(
    struct RuntimeObject* object)
{
    struct RuntimeObject* primary;
    struct RuntimeObject* secondary;
    s8* flags;

    primary = PRIMARY_ACTION_OBJECT;
    secondary = SECONDARY_ACTION_OBJECT;
    if (object->timer > 0) {
        object->timer--;
    } else {
        sub_8082E1C(primary, 7, 0x2039, 0);
        sub_8082E1C(secondary, 7, 0x2068, 0);
        flags = (s8*)&object->visual->flags;
        *flags = (*flags & -7) | 2;
        object->update = sub_8096FCC;
    }
}

SEC(sub_8096FCC)
void object_on_visual_complete_start_primary_animation_8(
    struct RuntimeObject* object)
{
    struct RuntimeObject* primary;
    s8* flags;

    primary = PRIMARY_ACTION_OBJECT;
    if (object->visual->flags & 8) {
        sound_effect_play(6, SOUND_VOLUME_UNCHANGED);
        sub_8082E1C(primary, 8, 0x2039, 0);
        flags = (s8*)&primary->visual->flags;
        *flags = (*flags & -7) | 2;
        object->update = sub_8097024;
    }
}

SEC(sub_8097024)
void object_start_secondary_animation_8(struct RuntimeObject* object)
{
    struct RuntimeObject* secondary;
    s8* flags;

    secondary = SECONDARY_ACTION_OBJECT;
    sound_effect_play(0x18, SOUND_VOLUME_UNCHANGED);
    sub_8082E1C(secondary, 8, 0x2068, 0);
    flags = (s8*)&secondary->visual->flags;
    *flags = (*flags & -7) | 2;
    object->update = sub_809706C;
}

SEC(sub_809706C)
void object_on_visual_complete_stop_pair_animations(
    struct RuntimeObject* object)
{
    struct RuntimeObject* primary;
    struct RuntimeObject* secondary;

    primary = PRIMARY_ACTION_OBJECT;
    secondary = SECONDARY_ACTION_OBJECT;
    if (object->visual->flags & 8) {
        sub_8082E1C(primary, -1, -1, 0);
        sub_8082E1C(secondary, -1, -1, 0);
        object->update = 0;
    }
}

SEC(sub_8097648)
void object_on_visual_complete_spawn_secondary_command_2089(
    struct RuntimeObject* object)
{
    struct RuntimeObject* secondary = SECONDARY_ACTION_OBJECT;
    struct RuntimeObject* spawned;

    if (object->visual->flags & 8) {
        spawned = sub_807BF34(
            secondary->state, 0x2089, 0, -0x40, -1, 0, 1);
        sub_8082E1C(spawned, 0, 0, 0);
        spawned->unknown78 &= 0x1F;
        object->linkedObject = spawned;
        sub_807FA14(spawned);
        if ((spawned->flags76 & 6) == 2 ||
            (spawned->flags76 & 6) == 4)
            spawned->update = sub_8097C38;
        sub_8097DB4(object);
    }
}

#define DEFINE_PAIR_COMPLETION_SYNC(symbol, name, active, counterpart, next) \
    SEC(symbol)                                                            \
    void name(struct RuntimeObject* object)                                \
    {                                                                      \
        struct RuntimeObject* primary = PRIMARY_ACTION_OBJECT;             \
        struct RuntimeObject* secondary = SECONDARY_ACTION_OBJECT;         \
                                                                           \
        sub_80884AC(object);                                               \
        if (object->flags79 & 0x20) {                                      \
            if (object == primary && secondary->update == active)          \
                secondary->update = counterpart;                           \
            if (object == secondary && primary->update == active)          \
                primary->update = counterpart;                             \
            object->update = next;                                         \
        }                                                                  \
    }

DEFINE_PAIR_COMPLETION_SYNC(
    sub_8097D50, object_finish_pair_motion_then_sync_counterpart_a,
    sub_80976D0, sub_8097978, sub_80974F8)

SEC(sub_8097E28)
void object_finish_pair_visual_then_prepare_counterpart_a(
    struct RuntimeObject* object)
{
    struct RuntimeObject* primary;
    struct RuntimeObject* secondary;

    primary = PRIMARY_ACTION_OBJECT;
    secondary = SECONDARY_ACTION_OBJECT;
    sub_8087CE4(object);
    if (object->flags79 & 0x20) {
        sub_807FB64(object->visual);
        if (object == primary && !(secondary->visual->flags & 0x20)) {
            if (secondary->linkedObject != 0)
                sub_8097DB4(secondary);
            else
                sub_80974F8(secondary);
        }
        if (object == secondary && !(primary->visual->flags & 0x20)) {
            if (primary->linkedObject != 0)
                sub_8097DB4(primary);
            else
                sub_80974F8(primary);
        }
        object->update = sub_8097F10;
    }
}

#define DEFINE_PAIR_CLEAR_ANIMATION(symbol, name, next)               \
    SEC(symbol)                                                       \
    void name(struct RuntimeObject* object)                           \
    {                                                                \
        struct RuntimeObject* primary = PRIMARY_ACTION_OBJECT;        \
        struct RuntimeObject* secondary = SECONDARY_ACTION_OBJECT;    \
                                                                     \
        sub_8087CE4(object);                                          \
        if (object->flags79 & 0x20) {                                 \
            if (object == primary)                                   \
                sub_8082E1C(object, 0, 0, 0);                         \
            if (object == secondary)                                 \
                sub_8082E1C(object, 0, 0, 0);                         \
            object->update = next;                                   \
        }                                                            \
    }

DEFINE_PAIR_CLEAR_ANIMATION(
    sub_8097EB4, object_finish_pair_motion_then_clear_animation_a,
    sub_8097648)

DEFINE_PAIR_COMPLETION_SYNC(
    sub_8098790, object_finish_pair_motion_then_sync_counterpart_b,
    sub_8098364, sub_8098540, sub_8098198)

SEC(sub_8098860)
void object_finish_pair_visual_then_prepare_counterpart_b(
    struct RuntimeObject* object)
{
    struct RuntimeObject* primary;
    struct RuntimeObject* secondary;

    primary = PRIMARY_ACTION_OBJECT;
    secondary = SECONDARY_ACTION_OBJECT;
    sub_8087CE4(object);
    if (object->flags79 & 0x20) {
        if (object == primary && secondary->update != 0) {
            if (secondary->linkedObject != 0)
                sub_80987F4(secondary);
            else
                sub_8098198(secondary);
        }
        if (object == secondary && primary->update != 0) {
            if (primary->linkedObject != 0)
                sub_80987F4(primary);
            else
                sub_8098198(primary);
        }
        object->update = sub_8098934;
    }
}

DEFINE_PAIR_CLEAR_ANIMATION(
    sub_80988D8, object_finish_pair_motion_then_clear_animation_b,
    sub_80982DC)
