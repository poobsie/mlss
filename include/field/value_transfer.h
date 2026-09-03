#ifndef GUARD_FIELD_VALUE_TRANSFER_H
#define GUARD_FIELD_VALUE_TRANSFER_H

#include "global.h"

struct FieldValueTransfer {
    u8 unknown00[0x34];
    u16 value34;
    u8 unknown36[0x0E];
    u16 value44;
};

void field_move_value_34_to_44(struct FieldValueTransfer* state);
void sub_8116610(struct FieldValueTransfer* state);

#endif
