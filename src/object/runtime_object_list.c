#include "field/actor.h"
#include "object/runtime_object_list.h"

#define SEC(name) \
    __attribute__((section(".text.runtime_object_list." #name)))

s32 sub_810DD7C(struct RuntimeObject* object, void* owner, s32 command);
s32 sub_8086C64(struct RuntimeObject* object);
s32 sub_8087124(struct RuntimeObject* object);

SEC(sub_807F4C4)
void runtime_object_prepend_with_shared_callback(
    struct RuntimeObject* object, RuntimeObjectCallback callback)
{
    struct FieldRuntime* runtime;
    volatile u8* flags;
    s32 flagValue;
    s32 mask;

    if (object->listNext != 0)
        return;

    runtime = gFieldRuntime;
    object->listNext = runtime->runtimeObjectListHead;
    runtime->runtimeObjectListHead = object;
    object->auxiliaryUpdate = (RuntimeObjectCallback)sub_810DD7C;
    object->secondaryUpdate = callback;
    object->tertiaryUpdate = callback;
    object->quaternaryUpdate = callback;
    /* Preserve the byte load before materializing the signed clear mask. */
    flags = &object->flags77;
    flagValue = *flags;
    mask = -8;
    flagValue &= mask;
    *flags = flagValue;
}

SEC(sub_807F4FC)
void runtime_object_prepend_to_active_list(struct RuntimeObject* object)
{
    struct FieldRuntime* runtime;
    volatile u8* flags;
    s32 flagValue;
    s32 mask;

    if (object->listNext != 0)
        return;

    runtime = gFieldRuntime;
    object->listNext = runtime->runtimeObjectListHead;
    runtime->runtimeObjectListHead = object;
    object->auxiliaryUpdate = (RuntimeObjectCallback)sub_810DD7C;
    object->secondaryUpdate = (RuntimeObjectCallback)sub_8086C64;
    object->tertiaryUpdate = (RuntimeObjectCallback)sub_8087124;
    /* Preserve the byte load before materializing the signed clear mask. */
    flags = &object->flags77;
    flagValue = *flags;
    mask = -8;
    flagValue &= mask;
    *flags = flagValue;
}
