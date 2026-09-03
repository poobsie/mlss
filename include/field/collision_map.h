#ifndef GUARD_FIELD_COLLISION_MAP_H
#define GUARD_FIELD_COLLISION_MAP_H

#include "global.h"

struct FieldCollisionDefinition {
    u8 bytes[4];
};

struct FieldCollisionMap {
    u8 unknown00[0xA0];
    struct FieldCollisionDefinition* definitions;
};

#define field_collision_map_get_definition get_coldef_ptr_by_idx

struct FieldCollisionDefinition* field_collision_map_get_definition(
    struct FieldCollisionMap* map, u8 index);

#endif
