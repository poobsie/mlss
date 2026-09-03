#include "object/functions.h"
#include "object/runtime_object.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SECTION(name) \
    __attribute__((section(".text.text_late_helpers." STRINGIFY(name))))
#define VALUE_AT(object, type, offset) (*(type*)((u8*)(object) + (offset)))

void sub_8082E1C(struct RuntimeObject* object, u32 command, u32 arg2, u32 arg3);
void sub_808750C(struct RuntimeObject* object);
void sub_8133C7C(struct RuntimeObject* object);

SECTION(object_on_visual_complete_command_0_and_continue)
void object_on_visual_complete_command_0_and_continue(struct RuntimeObject* object) {
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 0, 0, 0);
        object->update = sub_808750C;
    }
}

SECTION(object_on_visual_complete_command_0_and_stop)
void object_on_visual_complete_command_0_and_stop(struct RuntimeObject* object) {
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 0, 0, 0);
        object->update = 0;
    }
}

__attribute__((section(".text.text_late_helpers.sub_8132D78")))
const u16 object_command_0_and_stop_padding = 0;

SECTION(object_on_visual_complete_command_13_and_continue)
void object_on_visual_complete_command_13_and_continue(struct RuntimeObject* object) {
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 13, 0, 0);
        object->update = sub_808750C;
    }
}

SECTION(object_when_value80_clear_command_10)
void object_when_value80_clear_command_10(struct RuntimeObject* object) {
    if (VALUE_AT(object, u32, 0x80) == 0) {
        sub_8082E1C(object, 10, 0, 0);
        object->update = sub_8133C7C;
    }
}
