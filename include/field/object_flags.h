#ifndef GUARD_FIELD_OBJECT_FLAGS_H
#define GUARD_FIELD_OBJECT_FLAGS_H

#include "global.h"

struct FieldObjectStatus {
    u8 unknown000[0x11E];
    u16 flags11E;
};

#define field_clear_flags_11e_high_nibble sub_8108CBC

#endif
