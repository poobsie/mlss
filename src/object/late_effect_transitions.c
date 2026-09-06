#include "object/functions.h"
#include "object/runtime_object.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(symbol) \
    __attribute__((section(".text.late_effect_transitions." STRINGIFY(symbol))))

s32 sub_8086D80(struct RuntimeObject* object);
void sub_807F47C(struct RuntimeObject* object);

SEC(object_when_motion_complete_begin_downward_exit)
s32 object_when_motion_complete_begin_downward_exit(
    struct RuntimeObject* object)
{
    s32 result;

    result = sub_8086D80(object);
    if (result == 0) {
        object->update = object_integrate_downward_exit_until_offscreen;
        object->secondaryTimer /= 2;
        object->stateValueB0 = 0;
        object->verticalVelocity = 0;
        sub_807F47C(object);
    }
    return 0;
}

SEC(object_clear_behavior_on_visual_complete_variant_b)
void object_clear_behavior_on_visual_complete_variant_b(
    struct RuntimeObject* object)
{
    if (object->visual->flags & 8)
        sub_8087540(object);
}
SEC(object_clear_behavior_on_visual_complete_variant_b)
const u16 sub_809A6CC_padding = 0;
