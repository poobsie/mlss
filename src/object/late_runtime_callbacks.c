#include "object/functions.h"
#include "object/runtime_object.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(symbol) \
    __attribute__((section(".text.late_runtime_callbacks." STRINGIFY(symbol))))

void sub_8087EFC(struct RuntimeObject* object);
void sub_810DD7C(struct RuntimeObject* owner,
                 struct RuntimeObject* object, s32 value);
void sub_807B7A8(struct RuntimeObjectState* state);
void sub_807FE40(struct RuntimeObjectState* state);

SEC(object_update_motion_then_notify_owner_on_flag_20)
void object_update_motion_then_notify_owner_on_flag_20(
    struct RuntimeObject* object)
{
    struct RuntimeObject* owner;

    owner = object->positionOwner;
    sub_8087EFC(object);
    if (object->flags79 & 0x20) {
        sub_810DD7C(owner, object, 0xFF);
        object->update = (RuntimeObjectCallback)0x0809B031;
    }
}

SEC(object_cleanup_state_when_unlinked)
void object_cleanup_state_when_unlinked(
    struct RuntimeObject* object)
{
    if (object->linkedObject == 0) {
        sub_807B7A8(object->state);
        sub_807FE40(object->state);
    }
}
