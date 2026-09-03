#include "field/collision_record.h"

struct __attribute__((packed)) CollisionRecordIndex {
    u8 index : 3;
};

struct __attribute__((packed)) CollisionRecordActiveFlag {
    u8 low : 6;
    u8 active : 1;
};

void sub_8020D40(void* resource);

void field_collision_record_release_resource(struct FieldCollisionRecord* record)
    __attribute__((section(".text.early_code_helpers.sub_804FAF8")));
void field_collision_record_release_resource(struct FieldCollisionRecord* record) {
    sub_8020D40(record->resource);
    ((struct CollisionRecordActiveFlag*)&record->flags)->active = 0;
}

__attribute__((section(".text.early_code_helpers.sub_804FAF8")))
const u16 field_collision_record_release_padding = 0;

void field_collision_record_preserve_bounds(struct FieldCollisionRecord* record)
    __attribute__((section(".text.early_code_helpers.sub_804FB14")));
void field_collision_record_preserve_bounds(struct FieldCollisionRecord* record) {
    record->previousLeft = record->currentLeft;
    record->previousTop = record->currentTop;
    record->previousRight = record->currentRight;
    record->previousBottom = record->currentBottom;
}

__attribute__((section(".text.early_code_helpers.sub_804FB14")))
const u16 field_collision_record_preserve_padding = 0;

struct FieldCollisionRecord* field_collision_record_set_index(
    struct FieldCollisionRecord* record, u32 index)
    __attribute__((section(".text.early_code_helpers.sub_804FB28")));
struct FieldCollisionRecord* field_collision_record_set_index(
    struct FieldCollisionRecord* record, u32 index) {
    ((struct CollisionRecordIndex*)&record->flags)->index = index;
    return record;
}

__attribute__((section(".text.early_code_helpers.sub_804FB28")))
const u16 field_collision_record_set_index_padding = 0;
