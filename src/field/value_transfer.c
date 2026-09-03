#include "field/value_transfer.h"

#define SEC(name) __attribute__((section(".text.field_value_transfer." #name)))

SEC(sub_8116610) void sub_8116610(struct FieldValueTransfer* state)
{
    s32 value = state->value34;
    u16* destination = &state->value44;
    s32 zero = 0;

    *destination = value;
    state->value34 = zero;
}
SEC(sub_8116610) const u16 sub_8116610_padding = 0;

void field_move_value_34_to_44(struct FieldValueTransfer* state)
    __attribute__((alias("sub_8116610")));
