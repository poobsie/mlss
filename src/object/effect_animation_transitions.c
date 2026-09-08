#include "object/functions.h"
#include "object/runtime_object.h"
#include "audio/sound_effects.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(symbol) \
    __attribute__((section(".text.effect_animation_transitions." STRINGIFY(symbol))))

void sub_80DF024(s32 effect, s32 x, s32 y, s32 z,
                 struct RuntimeObject* object);
s32 sub_810DD7C(struct RuntimeObject* object, void* owner, s32 command);
s32 sub_8086D80(struct RuntimeObject* object,
                struct RuntimeObject* comparedObject);
void sub_807F47C(struct RuntimeObject* object);
void sub_807C298(struct RuntimeObject* object);
void sub_809F194(struct RuntimeObject* object);
void sub_8082E1C(struct RuntimeObject* object, s32 animation,
                 s32 command, s32 argument);
void sub_80873B8(struct RuntimeObject* object, s32 kind, s32 duration);
void sub_809E5E4(struct RuntimeObject* object);

SEC(object_when_value80_clear_start_owner_variant_animation_and_followup)
void object_when_value80_clear_start_owner_variant_animation_and_followup(
    struct RuntimeObject* object)
{
    struct RuntimeObject* owner;

    if (object->value80 == 0) {
        owner = object->positionOwner;
        object->timer = object->valueA0;
        sub_80873B8(object, 15 - owner->state->variant, 0);
        object->followup =
            object_select_animation_20_or_21_from_owner_variant_and_continue;
        sound_effect_play(0x62, SOUND_VOLUME_UNCHANGED);
    }
}

SEC(object_select_animation_20_or_21_from_owner_variant_and_continue)
void object_select_animation_20_or_21_from_owner_variant_and_continue(
    struct RuntimeObject* object)
{
    struct RuntimeObject* owner;

    owner = object->positionOwner;
    if (owner->state->variant == RUNTIME_OBJECT_VARIANT_FIRST)
        sub_8082E1C(object, 0x14, 0, 0);
    if (owner->state->variant == RUNTIME_OBJECT_VARIANT_SECOND)
        sub_8082E1C(object, 0x15, 0, 0);
    object->update = sub_809E5E4;
}

SEC(object_when_pair_query_clear_emit_effect_2661_and_continue)
s32 object_when_pair_query_clear_emit_effect_2661_and_continue(
    struct RuntimeObject* object, struct RuntimeObject* comparedObject)
{
    s32 result;

    result = sub_8086D80(object, comparedObject);
    if (result == 0) {
        sub_80DF024(0x2661, object->currentPositionX / 0x100,
                    object->currentPositionY / 0x100,
                    object->verticalPosition / 0x100, object);
        sub_807F47C(object);
        object->positionOwner = (u8*)object->state + 8;
        object->update = sub_809F194;
    }
    return result;
}

SEC(object_notify_owner_emit_effect_2651_and_destroy)
s32 object_notify_owner_emit_effect_2651_and_destroy(
    struct RuntimeObject* object, void* owner, s32 command)
{
    s32 result;

    result = sub_810DD7C(object, owner, command);
    sub_80DF024(0x2651, object->currentPositionX / 0x100,
                object->currentPositionY / 0x100,
                object->verticalPosition / 0x100, object);
    sub_807C298(object);
    return result;
}

SEC(object_emit_effect_2adb_then_notify_owner)
s32 object_emit_effect_2adb_then_notify_owner(
    struct RuntimeObject* object, void* owner, s32 command)
{
    sub_80DF024(0x2ADB, object->currentPositionX / 0x100,
                object->currentPositionY / 0x100,
                object->verticalPosition / 0x100, owner);
    return sub_810DD7C(object, owner, command);
}

__attribute__((section(".text.visual_sound_callbacks.sub_80DEDEC")))
void sub_80DEDEC(struct RuntimeObject* object) {
    struct RuntimeObjectVisual* visual;
    s32 mask = -7;
    if (8 & object->visual->flags) {
        sub_8082E1C(object, 11, 0, 0);
        visual = object->visual;
        visual->flags = (mask & visual->flags) | 2;
        sound_effect_play(0x128, SOUND_VOLUME_UNCHANGED);
        object->update = sub_80DEE34;
    }
}
