#ifndef GUARD_FIELD_COLLISION_MAP_H
#define GUARD_FIELD_COLLISION_MAP_H

#include "global.h"

struct FieldCollisionDefinition {
    u8 bytes[4];
};

struct FieldCollisionMap {
    u8 unknown00[0x26];
    u16 rowStride;
    u8 unknown28[0x0E];
    u16 values36[3];
    u16 values3C[5];
    u16 xLimit;
    u8 unknown48[4];
    u16 zLimit;
    u8 unknown4E[0x4E];
    u8* definitionIndices;
    struct FieldCollisionDefinition* definitions;
};

#define field_collision_map_get_definition get_coldef_ptr_by_idx
#define field_collision_map_get_definition_at get_coldef_ptr_by_xz
#define field_collision_map_copy_indexed_values_36_3c sub_805A0EC

void field_collision_map_copy_indexed_values_36_3c(
    struct FieldCollisionMap* map, u16 index, u16* value36, u16* value3C);
struct FieldCollisionDefinition* field_collision_map_get_definition(
    struct FieldCollisionMap* map, u8 index);
struct FieldCollisionDefinition* field_collision_map_get_definition_at(
    struct FieldCollisionMap* map, s16 x, s16 z);

#endif
