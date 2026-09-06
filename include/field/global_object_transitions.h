#ifndef GUARD_FIELD_GLOBAL_OBJECT_TRANSITIONS_H
#define GUARD_FIELD_GLOBAL_OBJECT_TRANSITIONS_H

#include "object/runtime_object.h"

struct FieldRuntimeObjectOwner {
    u8 unknown00[8];
    struct RuntimeObject object;
    u8 unknownD0[8];
    s32 vectorD8[3];
    u8 unknownE4[0x2C];
    u8 flags110;
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
    struct FieldRuntimeObjectOwner* objectOwners58[9];
    struct FieldRuntimeObjectOwner* activeObjectOwner7C;
};

#define field_start_first_object_animation_47_then_continue_a sub_8072500
#define field_start_first_object_animation_47_then_continue_b sub_8072528
#define field_apply_indexed_object_visual_transform sub_80F7FA4
#define field_copy_indexed_object_vector sub_80F7FC8
#define field_update_indexed_object_vector sub_80F8008
#define field_configure_indexed_object_flag_20 sub_80F80C4
#define field_start_selected_object_vector_motion sub_80F8198

void field_start_first_object_animation_47_then_continue_a(
    struct RuntimeObject* object);
void field_start_first_object_animation_47_then_continue_b(
    struct RuntimeObject* object);
s32 field_apply_indexed_object_visual_transform(
    void* context, void* state, const s32* arguments);
s32 field_copy_indexed_object_vector(
    void* context, void* state, const s32* arguments);
s32 field_update_indexed_object_vector(
    void* context, void* state, const s32* arguments);
s32 field_configure_indexed_object_flag_20(
    void* context, void* state, const s32* arguments);
s32 field_start_selected_object_vector_motion(
    void* context, void* state, const s32* arguments);

#endif
