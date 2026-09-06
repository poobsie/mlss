#ifndef GUARD_FIELD_OBJECT_FLAGS_H
#define GUARD_FIELD_OBJECT_FLAGS_H

#include "global.h"

struct FieldObjectStatus {
    u8 unknown000[0x10A];
    u16 value10A;
    u16 value10C;
    u8 unknown10E[0x0E];
    u16 value11C;
    u16 flags11E;
};

#define field_consume_flag_80 sub_8108C38
#define field_consume_flag_20 sub_8108C64
#define field_consume_flag_08 sub_8108C90
#define field_clear_flags_11e_high_nibble sub_8108CBC

#endif
