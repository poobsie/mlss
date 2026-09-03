#include "graphics/linked_visual.h"
#include "object/functions.h"
#include "object/runtime_object.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(symbol) \
    __attribute__((section(".text.misc_helpers_03." STRINGIFY(symbol))))

s32 sub_8087CE4(void);
void sub_80B325C(struct RuntimeObject* object);
void sub_80C0CC0(struct RuntimeObject* object);

SEC(object_poll_then_stop_and_resume_owner_on_flag20)
void object_poll_then_stop_and_resume_owner_on_flag20(
    struct RuntimeObject* object)
{
    struct RuntimeObject* owner;

    owner = (struct RuntimeObject*)object->positionOwner;
    sub_8087CE4();
    if (object->flags79 & 0x20) {
        object->update = 0;
        owner->update = sub_80C0CC0;
    }
}

SEC(object_poll_then_deactivate_visual_and_continue_on_flag20)
void object_poll_then_deactivate_visual_and_continue_on_flag20(
    struct RuntimeObject* object)
{
    sub_8087CE4();
    if (object->flags79 & 0x20) {
        graphics_deactivate_linked_visual(
            (struct GraphicsLinkedVisual*)object->visual);
        object->update = sub_80B325C;
    }
}
