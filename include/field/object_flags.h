#ifndef GUARD_FIELD_OBJECT_FLAGS_H
#define GUARD_FIELD_OBJECT_FLAGS_H

#include "global.h"
#include "object/runtime_object.h"

struct FieldObjectStatus {
    u8 unknown000[8];
    u8 object08[0xE4];
    s16 variantEC;
    u8 unknown0EE[0x1C];
    u16 value10A;
    u16 value10C;
    u8 unknown10E[0x0A];
    void* attachment118;
    u16 value11C;
    u16 flags11E;
    u8 unknown120[2];
    u8 flags122;
};

static inline struct RuntimeObject* field_object_status_runtime_object(
    struct FieldObjectStatus* object)
{
    return (struct RuntimeObject*)object->object08;
}

#define field_consume_flag_80 sub_8108C38
#define field_consume_flag_20 sub_8108C64
#define field_consume_flag_08 sub_8108C90
#define field_clear_flags_11e_high_nibble sub_8108CBC

#endif
