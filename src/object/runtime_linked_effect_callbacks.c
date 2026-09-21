#include "audio/sound_effects.h"
#include "object/runtime_leaf_callbacks.h"
#include "runtime_leaf_internal.h"

#define SEC(name) \
    __attribute__((section(".text.runtime_leaf_callbacks." #name)))

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
