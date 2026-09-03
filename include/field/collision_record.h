#ifndef GUARD_FIELD_COLLISION_RECORD_H
#define GUARD_FIELD_COLLISION_RECORD_H

#include "global.h"

struct FieldCollisionRecord {
    u8 flags;
    u8 unknown01[7];
    s32 currentLeft;
    s32 currentTop;
    s32 currentRight;
    s32 currentBottom;
    s32 previousLeft;
    s32 previousTop;
    s32 previousRight;
    s32 previousBottom;
    u8 unknown28[0x1C];
    void* resource;
    u8 unknown48[4];
};

#define field_collision_record_release_resource sub_804FAF8
#define field_collision_record_preserve_bounds sub_804FB14
#define field_collision_record_set_index sub_804FB28

void field_collision_record_release_resource(struct FieldCollisionRecord* record);
void field_collision_record_preserve_bounds(struct FieldCollisionRecord* record);
struct FieldCollisionRecord* field_collision_record_set_index(
    struct FieldCollisionRecord* record, u32 index);

#endif
