#include "object/runtime_object.h"

#define SEC(symbol) __attribute__((section(".text.object_motion." #symbol)))

void sub_8088164(struct RuntimeObject* object, s32 value);

SEC(sub_808842C)
void runtime_object_start_timed_motion(struct RuntimeObject* object, s32 value, s32 duration)
{
    object->motionDuration92 = duration;
    sub_8088164(object, value);
}
