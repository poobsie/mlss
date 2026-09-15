#include "audio/sound_effects.h"
#include "object/functions.h"
#include "object/runtime_object.h"

#define SEC(symbol) \
    __attribute__((section(".text.owner_motion_transitions." #symbol)))

void sub_807F4FC(struct RuntimeObject* object);
void sub_8082E1C(
    struct RuntimeObject* object, s32 animation, s32 command, s32 argument);
void sub_8085B38(struct RuntimeObject* object);
void sub_8066F60(struct RuntimeObject* object);
void sub_80DBC3C(struct RuntimeObject* object);
void sub_80DBBCC(struct RuntimeObject* object);

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
