#include "object/functions.h"
#include "object/runtime_object.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(symbol) \
    __attribute__((section(".text.misc_helpers_03." STRINGIFY(symbol))))

SEC(object_integrate_vertical_step_to_height_40)
void object_integrate_vertical_step_to_height_40(struct RuntimeObject* object)
{
    s32 value;

    object->verticalPosition += object->value8C;
    object->value8C -= 0x80;
    value = object->verticalPosition;
    if (value < 0)
        value += 0xFF;
    if ((value >> 8) <= 0x28) {
        object->verticalPosition = 0x2800;
        object->update = 0;
    }
}
SEC(object_integrate_vertical_step_to_height_40)
const u16 object_integrate_vertical_step_to_height_40_padding = 0;
