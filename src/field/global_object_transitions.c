#include "field/global_object_transitions.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(symbol) \
    __attribute__((section(".text.misc_helpers_02." STRINGIFY(symbol))))
#define SMALL_SEC(symbol) \
    __attribute__((section(".text.small_functions_01." STRINGIFY(symbol))))

#define FIELD_OBJECT_RUNTIME (*(struct FieldObjectRuntime**)0x03000FD8)
#define FIELD_INDEXED_OBJECT_RUNTIME \
    (*(struct FieldIndexedObjectRuntime**)0x03000FD8)

void sub_8072550(struct RuntimeObject* object);
void sub_80725D0(struct RuntimeObject* object);
void sub_8082E1C(
    struct RuntimeObject* object, s32 animation, s32 command, s32 argument);

#define START_FIRST_OBJECT_ANIMATION_47(object, continuation)                \
    do {                                                                     \
        sub_8082E1C(&FIELD_OBJECT_RUNTIME->firstObjectOwner->object,          \
                    0x2F, 0, 0);                                             \
        (object)->update = (continuation);                                    \
    } while (0)

SEC(field_start_first_object_animation_47_then_continue_a)
void field_start_first_object_animation_47_then_continue_a(
    struct RuntimeObject* object)
{
    START_FIRST_OBJECT_ANIMATION_47(object, sub_8072550);
}

SEC(field_start_first_object_animation_47_then_continue_b)
void field_start_first_object_animation_47_then_continue_b(
    struct RuntimeObject* object)
{
    START_FIRST_OBJECT_ANIMATION_47(object, sub_80725D0);
}

SMALL_SEC(field_apply_indexed_object_visual_transform)
s32 field_apply_indexed_object_visual_transform(
    void* context, void* state, const s32* arguments)
{
    struct FieldRuntimeObjectOwner* owner =
        FIELD_INDEXED_OBJECT_RUNTIME->objectOwners58[arguments[0]];

    runtime_object_visual_apply_transform(owner->object.visual, arguments[1]);
    return 1;
}

SMALL_SEC(field_copy_indexed_object_vector)
s32 field_copy_indexed_object_vector(
    void* context, void* state, const s32* arguments)
{
    struct FieldIndexedObjectRuntime* runtime = FIELD_INDEXED_OBJECT_RUNTIME;
    struct FieldRuntimeObjectOwner* destination =
        runtime->objectOwners58[*arguments++];
    struct FieldRuntimeObjectOwner* source =
        runtime->objectOwners58[*arguments++];

    destination->vectorD8[0] = source->vectorD8[0];
    destination->vectorD8[1] = source->vectorD8[1];
    destination->vectorD8[2] = source->vectorD8[2];
    return *(const u8*)arguments;
}
