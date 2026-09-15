#include "audio/sound_effects.h"
#include "object/runtime_object.h"

#define SEC(name) \
    __attribute__((section(".text.object_owner_state_motion." #name)))

void sub_807F47C(struct RuntimeObject* object);
void sub_8082E1C(struct RuntimeObject* object, s32 animation, s32 command,
                 s32 argument);
void sub_80DB27C(struct RuntimeObject* object);
void sub_80DB694(struct RuntimeObject* object);

SEC(sub_80DB1E4)
void sub_80DB1E4(struct RuntimeObject* object)
{
    struct ObjectPositionOwner* owner;
    struct ObjectPositionSource* state;
    s32* targetX;
    s32* targetY;
    s32* targetZSlot;
    s32* floorSlot;
    s32 targetZ;

    targetX = &object->value84;
    owner = (struct ObjectPositionOwner*)object->positionOwner;
    state = owner->positionSource;
    *targetX = state->positionX + 0x3400;
    targetY = &object->value88;
    *targetY = state->positionY;
    targetZSlot = &object->value8C;
    targetZ = state->positionZ;
    *targetZSlot = targetZ;
    floorSlot = (s32*)&object->value98;
    *floorSlot = targetZ;
    object->verticalAcceleration = sub_808552C(
        (s16*)((u8*)floorSlot + 0x16),
        (u16*)((u8*)targetZSlot + 0x24), &object->verticalVelocity,
        *targetX - object->positionX, *targetY - object->positionY,
        targetZ - object->positionZBase,
        0x400, 0x400, 0xFD, 0);
    sound_effect_play(0x8D, SOUND_VOLUME_UNCHANGED);
    sub_8082E1C(object, 2, 0, 0);
    object->update = sub_80DB27C;
}

SEC(sub_80DB5F0)
void object_start_owner_state_motion_animation_2(struct RuntimeObject* object)
{
    struct RuntimeObjectState* state;
    s32* targetX;
    s32* targetY;
    s32* targetZSlot;
    s32* floorSlot;
    s32 targetZ;
    u16* timerStorage;
    u16 timer;

    /* This callback decrements the shared signed timer as wrapping storage. */
    timerStorage = (u16*)&object->timer;
    timer = *timerStorage - 1;
    /* The reload preserves the original store scheduling and is equivalent. */
    *timerStorage = *timerStorage - 1;
    if ((s32)((u32)timer << 16) < 0) {
        sub_807F47C(object);
        targetX = &object->value84;
        state = object->state;
        *targetX = state->valueD8;
        targetY = &object->value88;
        *targetY = state->valueDC;
        targetZSlot = &object->value8C;
        targetZ = state->floorHeight;
        *targetZSlot = targetZ;
        floorSlot = (s32*)&object->value98;
        *floorSlot = targetZ;
        /* Preserve the original adjacent-output pointer lifetimes. */
        object->verticalAcceleration = sub_808552C(
            (s16*)((u8*)floorSlot + 0x16),
            (u16*)((u8*)targetZSlot + 0x24), &object->verticalVelocity,
            *targetX - object->positionX, *targetY - object->positionY,
            targetZ - object->positionZBase,
            0x400, 0x400, 0xFD, 0);
        sound_effect_play(0x8D, SOUND_VOLUME_UNCHANGED);
        sub_8082E1C(object, 2, 0, 0);
        object->update = sub_80DB694;
    }
}
