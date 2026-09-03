#ifndef GUARD_FIELD_GLOBAL_OBJECT_TRANSITIONS_H
#define GUARD_FIELD_GLOBAL_OBJECT_TRANSITIONS_H

#include "object/runtime_object.h"

struct FieldRuntimeObjectOwner {
    u8 unknown00[8];
    struct RuntimeObject object;
};

struct FieldObjectRuntime {
    u8 unknown00[0x58];
    struct FieldRuntimeObjectOwner* firstObjectOwner;
};

#define field_start_first_object_animation_47_then_continue_a sub_8072500
#define field_start_first_object_animation_47_then_continue_b sub_8072528

void field_start_first_object_animation_47_then_continue_a(
    struct RuntimeObject* object);
void field_start_first_object_animation_47_then_continue_b(
    struct RuntimeObject* object);

#endif
