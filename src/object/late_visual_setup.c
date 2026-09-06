#include "object/runtime_object.h"

#define SEC(symbol) __attribute__((section(".text.object_late_visual_setup." #symbol)))
#define object_start_secondary_visual_and_continue sub_809CA6C

void sub_8082E1C(struct RuntimeObject*, s32, s32, s32);
void sub_809C660(struct RuntimeObject*);

SEC(sub_809CA6C)
void object_start_secondary_visual_and_continue(struct RuntimeObject* object)
{
    volatile u8* flags;
    s32 value;
    s32 mask;

    sub_8082E1C(object, 2, -1, 0);
    flags = &object->visual->flags;
    value = *flags;
    mask = -7;
    value &= mask;
    value |= 2;
    *flags = value;
    object->update = sub_809C660;
}
