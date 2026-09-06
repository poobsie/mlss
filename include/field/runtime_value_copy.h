#ifndef GUARD_FIELD_RUNTIME_VALUE_COPY_H
#define GUARD_FIELD_RUNTIME_VALUE_COPY_H

#include "global.h"

struct FieldLinkedValue {
    u8 unknown00[0x0A];
    u8 value0A;
};

struct FieldLinkedValueOwner {
    u8 unknown00[0x6C];
    struct FieldLinkedValue* linked6C;
};

#define field_copy_linked_value_to_runtime sub_8106994
void field_copy_linked_value_to_runtime(struct FieldLinkedValueOwner* owner);

#endif
