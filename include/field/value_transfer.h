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

#define field_commit_runtime_value_transfer sub_807F6D0
#define field_prepare_runtime_value_transfer sub_807F6EC
#define field_trigger_primary_actor_object sub_80D2D34

void field_commit_runtime_value_transfer(void);
void field_prepare_runtime_value_transfer(s32 mode);
void field_trigger_primary_actor_object(void);

#endif
