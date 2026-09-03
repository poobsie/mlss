#ifndef GUARD_FIELD_ENTRY_TOGGLE_H
#define GUARD_FIELD_ENTRY_TOGGLE_H

#include "global.h"

struct FieldEntryMatchOwner {
    u8 unknown00[0x14];
    void* matchSource14;
};

struct FieldEntryToggleTarget {
    u8 unknown00[0xA0];
    u16 flagsA0;
};

#define field_toggle_target_flag_a0_02_if_entry_matches sub_80FAEC4

void field_toggle_target_flag_a0_02_if_entry_matches(
    struct FieldEntryMatchOwner* owner,
    struct FieldEntryToggleTarget* target,
    u8 entry);

#endif
