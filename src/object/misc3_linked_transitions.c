#include "object/functions.h"
#include "object/runtime_object.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(symbol) \
    __attribute__((section(".text.misc_helpers_03." STRINGIFY(symbol))))

void sub_8066334(struct RuntimeObject* object);
void sub_8066540(struct RuntimeObject* object, s32 x, s32 y, s32 z);
void sub_8068A28(struct RuntimeObject* object);
void sub_807940C(struct RuntimeObject* object);
void sub_8079BA8(struct RuntimeObject* object);
void sub_8082E1C(
    struct RuntimeObject* object, s32 animation, s32 command, s32 argument);
void sub_808750C(struct RuntimeObject* object);

SEC(object_when_value80_clear_start_linked_object_motion)
void object_when_value80_clear_start_linked_object_motion(
    struct RuntimeObject* object)
{
    s32 value;
    struct RuntimeObject* linked;

    value = object->value80;
    if (value == 0) {
        sub_8082E1C(object, 0, 0, 0);
        linked = object->linkedObject;
        linked->currentPositionX = object->positionX + 0x2200;
        linked->currentPositionY = object->positionY;
        linked->update = sub_8068A28;
        object->update = (RuntimeObjectCallback)value;
    }
}

SEC(object_update_linked_position_then_wait_for_value80)
void object_update_linked_position_then_wait_for_value80(
    struct RuntimeObject* object)
{
    sub_8066540(object->linkedObject, object->currentPositionX,
                object->currentPositionY, object->verticalPosition);
    if (object->value80 == 0) {
        object->timer = 0x1E;
        object->update = sub_8066334;
    }
}

SEC(object_on_visual_complete_stop_owner_then_animation_7)
void object_on_visual_complete_stop_owner_then_animation_7(
    struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        ((struct RuntimeObject*)object->positionOwner)->update = 0;
        sub_8082E1C(object, 7, 0, 0);
        object->update = sub_808750C;
    }
}

SEC(object_on_visual_complete_animation_7_then_stop_owner)
void object_on_visual_complete_animation_7_then_stop_owner(
    struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 7, 0, 0);
        object->update = sub_808750C;
        ((struct RuntimeObject*)object->positionOwner)->update = 0;
    }
}

SEC(object_when_linked_present_start_animation_17_and_linked_update)
void object_when_linked_present_start_animation_17_and_linked_update(
    struct RuntimeObject* object)
{
    struct RuntimeObject* linked;

    if (object->linkedObject == 0) {
        object->update = (RuntimeObjectCallback)object->linkedObject;
        return;
    }
    sub_8082E1C(object, 0x11, 0, 0);
    object->update = sub_8079BA8;
    linked = object->linkedObject;
    linked->valueA0 = object->behaviorState;
    linked->update = sub_807940C;
}
