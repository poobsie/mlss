#include "field/global_object_transitions.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(symbol) \
    __attribute__((section(".text.misc_helpers_02." STRINGIFY(symbol))))
#define SMALL_SEC(symbol) \
    __attribute__((section(".text.small_functions_01." STRINGIFY(symbol))))
#define MISC3_SEC(symbol) \
    __attribute__((section(".text.misc_helpers_03." STRINGIFY(symbol))))

#define FIELD_OBJECT_RUNTIME (*(struct FieldObjectRuntime**)0x03000FD8)
#define FIELD_INDEXED_OBJECT_RUNTIME \
    (*(struct FieldIndexedObjectRuntime**)0x03000FD8)

void sub_8072550(struct RuntimeObject* object);
void sub_80725D0(struct RuntimeObject* object);
void sub_8082E1C(
    struct RuntimeObject* object, s32 animation, s32 command, s32 argument);

MISC3_SEC(field_find_object_with_largest_value_span)
s32 field_find_object_with_largest_value_span(void* context, s32 threshold)
{
    s32 selectedIndex = -1;
    s16 index = 0;
    struct FieldRuntimeObjectOwner** owners =
        FIELD_INDEXED_OBJECT_RUNTIME->objectOwners58;

    do {
        struct FieldRuntimeObjectOwner* owner = owners[index];

        if (owner != NULL && (owner->object.flags76 & 6) == 4) {
            s32 span = owner->valueF8 - owner->valueF6;

            if (span > threshold) {
                threshold = span;
                selectedIndex = index;
            }
        }
        index++;
    } while (index <= 5);
    return selectedIndex;
}

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

SMALL_SEC(field_update_indexed_object_vector)
s32 field_update_indexed_object_vector(
    void* context, void* state, const s32* arguments)
{
    s32 operation;
    struct FieldRuntimeObjectOwner* owner =
        FIELD_INDEXED_OBJECT_RUNTIME->objectOwners58[arguments[1]];

    operation = *arguments++;
    switch (operation) {
    case 0:
        owner->vectorD8[0] = arguments[1] << 8;
        owner->vectorD8[1] = arguments[2] << 8;
        owner->vectorD8[2] = arguments[3] << 8;
        break;
    case 1:
        owner->vectorD8[0] += arguments[1] << 8;
        owner->vectorD8[1] += arguments[3] << 8;
        owner->vectorD8[2] += arguments[2] << 8;
        break;
    }
    return 1;
}

SMALL_SEC(field_configure_indexed_object_flag_20)
s32 field_configure_indexed_object_flag_20(
    void* context, void* state, const s32* arguments)
{
    struct FieldRuntimeObjectOwner* owner =
        FIELD_INDEXED_OBJECT_RUNTIME->objectOwners58[arguments[1]];
    s32 flag = 0;
    u8* flags110;
    s32 flags;
    s32 clearMask;

    if (arguments[0] == 0)
        flag = 1;
    flags110 = &owner->flags110;
    flag <<= 5;
    flags = *flags110;
    clearMask = 0x21;
    clearMask = -clearMask;
    clearMask &= flags;
    clearMask |= flag;
    *flags110 = clearMask;
    return 1;
}

SMALL_SEC(field_start_selected_object_vector_motion)
s32 field_start_selected_object_vector_motion(
    void* context, void* state, const s32* arguments)
{
    struct FieldIndexedObjectRuntime* runtime = FIELD_INDEXED_OBJECT_RUNTIME;
    struct FieldRuntimeObjectOwner* active = runtime->activeObjectOwner7C;

    if (active != 0) {
        s32 selector = arguments[0];
        struct FieldRuntimeObjectOwner* owner;

        if (selector < 0)
            owner = active;
        else
            owner = runtime->objectOwners58[selector];
        if (owner->object.update != 0)
            runtime_object_begin_owner_vector_motion(&owner->object);
    }
    return 1;
}

SMALL_SEC(field_start_selected_object_vector_motion)
const u16 field_start_selected_object_vector_motion_padding = 0;
