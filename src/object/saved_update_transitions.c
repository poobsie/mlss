#include "object/functions.h"
#include "object/runtime_object.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(name) \
    __attribute__((section(".text.misc_helpers_02." STRINGIFY(name))))

struct RuntimeObjectCallbackDescriptor {
    u8 unknown00[4];
    RuntimeObjectCallback callback;
};

s32 sub_8082B00(void);
void sub_807C298(struct RuntimeObject* object);
void sub_8082E1C(
    struct RuntimeObject* object, s32 animation, s32 command, s32 argument);
s32 sub_8086C64(struct RuntimeObject* object);
void sub_80DBC60(struct RuntimeObject* object);

SEC(object_save_update_and_run_setup)
s32 object_save_update_and_run_setup(struct RuntimeObject* object)
{
    s32 result;

    object->auxiliaryState = (s32)object->update;
    result = sub_8086C64(object);
    if (result == 0)
        object->update = sub_80DBC60;
    return result;
}

SEC(object_restore_update_when_visual_value21_clear)
void object_restore_update_when_visual_value21_clear(
    struct RuntimeObject* object)
{
    if (object->visual->value21 == 0) {
        sub_8082E1C(object, 2, 0, 0);
        object->update = (RuntimeObjectCallback)object->auxiliaryState;
    }
}

SEC(object_release_when_state_visual_value21_clear)
void object_release_when_state_visual_value21_clear(
    struct RuntimeObject* object)
{
    if (object->state->visual10->value21 == 0)
        sub_807C298(object);
}
SEC(object_release_when_state_visual_value21_clear)
const u16 object_release_when_state_visual_value21_clear_padding = 0;

SEC(object_when_field_ready_invoke_descriptor_callback)
void object_when_field_ready_invoke_descriptor_callback(
    struct RuntimeObject* object)
{
    struct RuntimeObjectCallbackDescriptor* descriptor;

    if (sub_8082B00() == 0) {
        descriptor = (struct RuntimeObjectCallbackDescriptor*)object->descriptor;
        descriptor->callback(object);
    }
}
