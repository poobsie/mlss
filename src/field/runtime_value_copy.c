#include "field/runtime_value_copy.h"

#define SEC(symbol) __attribute__((section(".text.field_runtime_value_copy." #symbol)))
#define FIELD_VALUE_RUNTIME (*(struct FieldValueRuntime**)0x03000FD8)

struct FieldValueRuntime {
    u8 unknown000[0x2F9];
    u8 linkedValue2F9;
};

void sub_810CA30(void);

SEC(sub_8106994)
void field_copy_linked_value_to_runtime(struct FieldLinkedValueOwner* owner)
{
    FIELD_VALUE_RUNTIME->linkedValue2F9 = owner->linked6C->value0A;
    sub_810CA30();
}
