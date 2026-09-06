#include "object/runtime_object.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(name) \
    __attribute__((section(".text.misc_helpers_03." STRINGIFY(name))))

void sub_805FF30(struct RuntimeObject* object);
void sub_807C298(struct RuntimeObject* object);
void sub_807FC08(s32* x, s32* y, s32* z, s32 argument);
void sub_8082E1C(
    struct RuntimeObject* object, s32 animation, s32 command, s32 argument);

SEC(sub_805FD40)
void object_finish_when_state_value_ba_clear(struct RuntimeObject* object)
{
    if (object->state->valueBA == 0)
        sub_807C298(object);
}
SEC(sub_805FD40)
const u16 object_finish_when_state_value_ba_clear_padding = 0;

SEC(sub_805FD5C)
void object_accelerate_left_to_behavior_position(struct RuntimeObject* object)
{
    if ((s16)object->stateValueB0 != 0)
        object->secondaryTimer += 0x10;
    else
        object->secondaryTimer += 0x13;

    object->currentPositionX -= object->secondaryTimer;
    if (object->currentPositionX < object->behaviorState) {
        object->verticalVelocity = 0;
        object->currentPositionX = object->behaviorState;
        sub_8082E1C(object, 8, 0, 0);
        object->update = sub_805FF30;
    }
}

SEC(sub_805FE74)
void object_update_offset_motion_then_finish_outside_transformed_bounds(
    struct RuntimeObject* object)
{
    s32 transformedX;
    s32 transformedY;
    s32 transformedZ;
    s32 position;

    object->currentPositionX = object->positionX - object->secondaryTimer;
    object->verticalPosition = object->positionZBase - object->verticalVelocity;
    object->verticalVelocity += 0x20;
    position = object->currentPositionX;
    if (position < 0)
        position += 0xFF;
    transformedX = position >> 8;
    position = object->currentPositionY;
    if (position < 0)
        position += 0xFF;
    transformedY = position >> 8;
    position = object->verticalPosition;
    if (position < 0)
        position += 0xFF;
    transformedZ = position >> 8;
    sub_807FC08(&transformedX, &transformedY, &transformedZ, 0);
    if (transformedY > 0x110)
        sub_807C298(object);
    else if (transformedX < -0x10)
        sub_807C298(object);
}

SEC(sub_805FEF4)
void object_when_value80_clear_snap_to_behavior_position(
    struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        struct RuntimeObjectVisual* visual = object->visual;
        u8 flags = visual->flags11;

        flags |= 0x40;
        visual->flags11 = flags;
        object->verticalVelocity = 0;
        object->currentPositionX = object->behaviorState;
        sub_8082E1C(object, 8, 0, 0);
        object->update = sub_805FF30;
    }
}
