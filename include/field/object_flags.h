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
    /* The third byte of this control word is also updated as flags. */
    union FieldObjectStatusControl {
        s32 value;
        struct {
            u8 unknown120[2];
            u8 flags122;
            u8 unknown123;
        } bytes;
    } control120;
    u8 unknown124[2];
    s16 value126;
    u8 value128;
    u8 unknown129;
    u8 value12A;
    u8 unknown12B;
    u8 value12C;
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
#define field_try_claim_status_flag_4000 sub_8108D8C
#define field_try_claim_status_flag_2000 sub_8108DE4
#define field_try_claim_status_flag_1000 sub_8108E3C

s32 field_try_claim_status_flag_4000(
    struct FieldObjectStatus* object, s32 threshold);
s32 field_try_claim_status_flag_2000(
    struct FieldObjectStatus* object, s32 threshold);
s32 field_try_claim_status_flag_1000(
    struct FieldObjectStatus* object, s32 threshold);

#endif
