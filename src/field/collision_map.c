#include "field/collision_map.h"

#define COLLISION_MAP_SEC(symbol) \
    __attribute__((section(".text.field.collision_map." #symbol)))

COLLISION_MAP_SEC(sub_805A0EC)
void field_collision_map_copy_indexed_values_36_3c(
    struct FieldCollisionMap* map, u16 index, u16* value36, u16* value3C)
{
    *value36 = map->values36[index];
    *value3C = map->values3C[index];
}

COLLISION_MAP_SEC(sub_805A0EC)
const u16 field_collision_map_copy_values_padding = 0;

COLLISION_MAP_SEC(get_coldef_ptr_by_idx)
struct FieldCollisionDefinition* field_collision_map_get_definition(
    struct FieldCollisionMap* map, u8 index)
{
    return &map->definitions[index];
}

COLLISION_MAP_SEC(get_coldef_ptr_by_xz)
struct FieldCollisionDefinition* field_collision_map_get_definition_at(
    struct FieldCollisionMap* map, s16 x, s16 z)
{
    u16 index;

    if (x < 0 || x >= map->xLimit || z < 0 || z >= map->zLimit) {
        return (struct FieldCollisionDefinition*)0x083A75D8;
    }
    index = x + map->rowStride * z;
    return field_collision_map_get_definition(
        map, map->definitionIndices[index]);
}
