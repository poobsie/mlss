#include "object/runtime_object.h"

#define SEC(symbol) __attribute__((section(".text.object_phase_motion." #symbol)))

void sub_80874B4(struct RuntimeObject* object);
void sub_807F47C(struct RuntimeObject* object);
void sub_8082E1C(struct RuntimeObject* object, s32 animation, s32 command,
                 s32 argument);
void sub_80F75D8(s32 value);

SEC(sub_808750C)
void runtime_object_when_value80_clear_prepare_state_motion(
    struct RuntimeObject* object)
{
    if (object->value80 == 0)
        object->update = sub_80874B4;
}

SEC(sub_8087540)
void runtime_object_clear_behavior(struct RuntimeObject* object)
{
    struct RuntimeObjectState* state = object->state;

    if (state != 0 && object == (struct RuntimeObject*)((u8*)state + 8) &&
        object->visual != 0) {
        *(u16*)((u8*)state + 0x78) = 0;
        sub_8082E1C(object, -1, -1, 0);
    }
    sub_807F47C(object);
    object->cleanup = 0;
    object->auxiliaryState = 0;
    object->update = 0;
    object->descriptor = 0;
    object->positionOwner = 0;
    if ((object->flags76 & 6) == 2)
        sub_80F75D8(0x40000);
}

SEC(sub_80877C0)
u32 runtime_object_advance_vertical_to_limit(struct RuntimeObject* object)
{
    object->motionDuration92 += object->verticalAcceleration;
    object->verticalPosition = object->positionZBase + object->motionDuration92;
    if ((s32)object->value98 < object->verticalPosition)
        return 0;
    object->verticalPosition = object->value98;
    object->verticalAcceleration = 0;
    return 1;
}
SEC(sub_80877C0) const u16 sub_80877C0_padding = 0;
