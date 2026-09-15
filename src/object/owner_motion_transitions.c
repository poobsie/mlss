#include "audio/sound_effects.h"
#include "object/functions.h"
#include "object/runtime_leaf_callbacks.h"
#include "object/runtime_object.h"

#define SEC(symbol) \
    __attribute__((section(".text.owner_motion_transitions." #symbol)))

void sub_807F4FC(struct RuntimeObject* object);
void sub_807F47C(struct RuntimeObject* object);
void sub_8082E1C(
    struct RuntimeObject* object, s32 animation, s32 command, s32 argument);
void sub_8085B38(struct RuntimeObject* object);
void sub_8066F60(struct RuntimeObject* object);
void sub_8066FFC(struct RuntimeObject* object);
void sub_806A204(struct RuntimeObject* object);
void sub_806A24C(struct RuntimeObject* object);
void sub_80DAE7C(struct RuntimeObject* object);
void sub_80DBC84(struct RuntimeObject* object);
void sub_80DBC3C(struct RuntimeObject* object);
void sub_80DBBCC(struct RuntimeObject* object);
s32 sub_8199F30(void);

#define object_on_visual_complete_begin_owner_offset_motion sub_8066EE0
SEC(sub_8066EE0)
void object_on_visual_complete_begin_owner_offset_motion(
    struct RuntimeObject* object)
{
    s32* targetStart;
    s32* target;
    struct RuntimeObject* owner;
    struct RuntimeObjectState* state;
    volatile u8* flags;

    if (object->visual->flags & OBJECT_VISUAL_COMPLETE) {
        /* Keep the alias explicit so agbcc emits a store followed by increment. */
        targetStart = &object->value84;
        target = targetStart;
        owner = object->positionOwner;
        state = owner->state;
        *target = state->valueD8 + 0x3800;
        target++;
        *target = state->valueDC;
        object->value8C = object->positionZBase;
        flags = &object->flags79;
        *flags |= 0x20;
        object->unknown7C = 0x200;
        object->unknown7A = 0;
        sub_8085B38(object);
        sub_8082E1C(object, 3, 0, 0);
        object->update = sub_8066F60;
        sound_effect_play(0x11C, SOUND_VOLUME_UNCHANGED);
    }
}

SEC(sub_8066F60)
void sub_8066F60(struct RuntimeObject* object)
{
    struct RuntimeObject* owner;
    struct RuntimeObjectState* state;
    s32* targetStart;
    s32* target;
    volatile u8* flags;
    s32 gateValue;

    gateValue = object->value80;
    if (gateValue != 0)
        return;

    sound_effect_stop(0x11C);
    sub_8082E1C(object, 4, 0, 0);
    targetStart = &object->value84;
    target = targetStart;
    owner = object->positionOwner;
    state = owner->state;
    *target = state->valueD8 + 0x1600;
    target++;
    *target = state->valueDC;
    object->value8C = object->positionZBase;
    flags = &object->flags79;
    *flags |= 0x20;
    object->unknown7C = 0x200;
    object->unknown7A = gateValue;
    sub_8085B38(object);
    sub_807F4FC(object);
    object->auxiliaryUpdate = (RuntimeObjectCallback)sub_8067830;
    object->tertiaryUpdate = (RuntimeObjectCallback)sub_8067838;
    object->timer = (sub_8199F30() & 3) + 1;
    object->update = sub_8066FFC;
}

SEC(sub_8069558)
void sub_8069558(struct RuntimeObject* object)
{
    s32 value;

    if (object->visual->flags & OBJECT_VISUAL_COMPLETE) {
        s32* targetStart;
        s32* target;
        struct ObjectPositionOwner* owner;
        struct ObjectPositionSource* source;
        volatile u8* flags;

        sub_8082E1C(object, 4, 0, 0);
        /* Keep the alias explicit so agbcc emits a store followed by increment. */
        targetStart = &object->value84;
        target = targetStart;
        owner = object->positionOwner;
        source = owner->positionSource;
        *target = source->positionX + 0x3000;
        target++;
        *target = source->positionY;
        object->value8C = object->positionZBase;
        flags = &object->flags79;
        *flags |= 0x20;
        object->unknown7C = 0x180;
        object->unknown7A = 0;
        sub_8085B38(object);
        value = --object->behaviorState;
        if (value > 0)
            object->update = sub_806A24C;
        else
            object->update = sub_806A204;
    }
}

SEC(sub_80DAC80)
void sub_80DAC80(struct RuntimeObject* object)
{
    struct ObjectPositionOwner* owner;
    struct ObjectPositionSource* source;
    s32* targetStart;
    s32* target;
    u16* timerStorage;
    u16 remaining;
    s32 gateValue;
    volatile u8* flags;

    gateValue = object->value80;
    if (gateValue != 0)
        return;

    /* Decrement the signed timer through unsigned wrapping storage. */
    timerStorage = (u16*)&object->timer;
    remaining = *timerStorage - 1;
    *timerStorage = *timerStorage - 1;
    if ((s32)((u32)remaining << 16) < 0) {
        /* Keep the alias explicit so agbcc emits a store followed by increment. */
        targetStart = &object->value84;
        target = targetStart;
        owner = object->positionOwner;
        source = owner->positionSource;
        *target = source->positionX + 0x2800;
        target++;
        *target = source->positionY;
        object->value8C = object->state->floorHeight;
        flags = &object->flags79;
        *flags |= 0x20;
        object->unknown7C = 0x400;
        object->unknown7A = gateValue;
        sub_8085B38(object);
        sub_8082E1C(object, 2, 0, 0);
        object->update = sub_80DAE7C;
    }
}

SEC(sub_80DB95C)
void sub_80DB95C(struct RuntimeObject* object)
{
    struct RuntimeObjectState* state;
    volatile u8* flags;
    s32* targetStart;
    s32* target;
    s32** activeTarget;
    u16* timerStorage;
    u16 remaining;
    s32 gateValue;

    gateValue = object->value80;
    if (gateValue != 0)
        return;

    /* Decrement the signed timer through unsigned wrapping storage. */
    timerStorage = (u16*)&object->timer;
    remaining = *timerStorage - 1;
    *timerStorage = *timerStorage - 1;
    if ((s32)((u32)remaining << 16) <= 0) {
        sub_807F47C(object);
        targetStart = &object->value84;
        target = targetStart;
        state = object->state;
        *target = state->valueD8;
        target++;
        *target = state->valueDC;
        /* Retain the cursor alias through the final target write. */
        activeTarget = &target;
        target++;
        **activeTarget = state->floorHeight;
        flags = &object->flags79;
        *flags |= 0x20;
        object->unknown7C = 0x600;
        object->unknown7A = gateValue;
        sub_8085B38(object);
        sub_8082E1C(object, 5, 0, 0);
        object->update = sub_80DBC84;
    }
}

SEC(sub_80DBB1C)
void sub_80DBB1C(struct RuntimeObject* object)
{
    struct ObjectPositionOwner* owner;
    struct ObjectPositionSource* state;
    s32* stateX;
    s32* stateY;
    s32* stateZ;
    s32 adjustedPosition;
    s32 gateValue;
    s32 position;
    u16 remaining;
    u8 flags;

    gateValue = object->value80;
    if (gateValue != 0)
        return;

    remaining = object->timer - 1;
    object->timer = object->timer - 1;
    if ((s32)((u32)remaining << 16) < 0) {
        sub_807F4FC(object);
        object->secondaryUpdate = object_save_update_and_run_setup;

        owner = (struct ObjectPositionOwner*)object->positionOwner;
        state = owner->positionSource;
        stateX = &state->positionX;
        adjustedPosition = (s32)((u32)*stateX
            + ((u32)object->valueA0 << 8));
        position = adjustedPosition;
        object->positionX = position;
        object->currentPositionX = position;
        stateY = &state->positionY;
        position = *stateY;
        object->positionY = position;
        object->currentPositionY = position;
        stateZ = &state->positionZ;
        position = *stateZ;
        object->positionZBase = position;
        object->verticalPosition = position;

        object->value84 = *stateX + 0x400;
        object->value88 = *stateY;
        object->value8C = *stateZ;
        flags = object->flags79;
        flags |= 0x20;
        object->flags79 = flags;
        object->unknown7C = (u16)((u32)object->valueA4 << 8);
        object->unknown7A = gateValue;
        sub_8085B38(object);
        sub_8082E1C(object, 4, 0, 0);
        object->update = sub_80DBBCC;
    }
}
