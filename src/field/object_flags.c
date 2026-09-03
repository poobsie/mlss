#include "field/object_flags.h"

#define SEC(symbol) __attribute__((section(".text.middle." #symbol)))

SEC(sub_8108CBC) void field_clear_flags_11e_high_nibble(
    struct FieldObjectStatus* object)
{
    object->flags11E &= 0x0FFF;
}
