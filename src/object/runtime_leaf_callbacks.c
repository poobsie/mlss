#include "global.h"
#include "object/runtime_leaf_callbacks.h"

#define SEC(name) \
    __attribute__((section(".text.runtime_leaf_callbacks." #name)))

void sub_807C298(struct RuntimeObject* object);
void sub_8082E1C(
    struct RuntimeObject* object, s32 animation, s32 command, s32 argument);
void sub_806822C(struct RuntimeObject* object);
void sub_806CAC0(struct RuntimeObject* object);
void sub_806DD48(struct RuntimeObject* object);
void nullsub_15(void);


SEC(sub_8068074)
void sub_8068074(struct RuntimeObject* object)
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
void sub_80680A0(struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        sub_8082E1C(object, 6, 0, 0);
        object->secondaryTimer = (s16)object->behaviorState;
        object->update = sub_806822C;
    }
}

SEC(sub_806819C)
void sub_806819C(struct RuntimeObject* object)
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
void sub_80687EC(struct RuntimeObject* object)
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
void sub_806C800(struct RuntimeObject* object)
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
void sub_806CB3C(struct RuntimeObject* object)
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
s32 sub_806E690(struct RuntimeObject* object)
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
