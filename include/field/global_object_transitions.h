#ifndef GUARD_FIELD_GLOBAL_OBJECT_TRANSITIONS_H
#define GUARD_FIELD_GLOBAL_OBJECT_TRANSITIONS_H

#include "object/runtime_object.h"

struct FieldRuntimeObjectOwner {
    u8 unknown00[8];
    struct RuntimeObject object;
    u8 unknownD0[8];
    s32 vectorD8[3];
};

struct FieldObjectRuntime {
    u8 unknown00[0x58];
    struct FieldRuntimeObjectOwner* firstObjectOwner;
    u8 unknown5C[0x14];
    struct FieldRuntimeObjectOwner* primaryActionOwner;
    struct FieldRuntimeObjectOwner* secondaryActionOwner;
};

struct FieldIndexedObjectRuntime {
    u8 unknown00[0x58];
    struct FieldRuntimeObjectOwner* objectOwners58[1];
};

#define field_start_first_object_animation_47_then_continue_a sub_8072500
#define field_start_first_object_animation_47_then_continue_b sub_8072528
#define field_apply_indexed_object_visual_transform sub_80F7FA4
#define field_copy_indexed_object_vector sub_80F7FC8

void field_start_first_object_animation_47_then_continue_a(
    struct RuntimeObject* object);
void field_start_first_object_animation_47_then_continue_b(
    struct RuntimeObject* object);
s32 field_apply_indexed_object_visual_transform(
    void* context, void* state, const s32* arguments);
s32 field_copy_indexed_object_vector(
    void* context, void* state, const s32* arguments);

#endif
