#include "field/object_flags.h"

#define SEC(symbol) __attribute__((section(".text.middle." #symbol)))

SEC(sub_8108C38) void field_consume_flag_80(struct FieldObjectStatus* object)
{
    if (object->flags11E & 0x80) {
        object->flags11E &= ~0x80;
        object->value11C = 0x100;
    }
}

SEC(sub_8108C64) void field_consume_flag_20(struct FieldObjectStatus* object)
{
    if (object->flags11E & 0x20) {
        object->flags11E &= ~0x20;
        object->value10C = 0x100;
    }
}

SEC(sub_8108C90) void field_consume_flag_08(struct FieldObjectStatus* object)
{
    if (object->flags11E & 0x08) {
        object->flags11E &= ~0x08;
        object->value10A = 0x100;
    }
}

SEC(sub_8108CBC) void field_clear_flags_11e_high_nibble(
    struct FieldObjectStatus* object)
{
    object->flags11E &= 0x0FFF;
}
