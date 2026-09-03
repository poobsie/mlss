#include "field/collision_map.h"

#define COLLISION_MAP_SEC(symbol) \
    __attribute__((section(".text.field.collision_map." #symbol)))

COLLISION_MAP_SEC(get_coldef_ptr_by_idx)
struct FieldCollisionDefinition* field_collision_map_get_definition(
    struct FieldCollisionMap* map, u8 index)
{
    return &map->definitions[index];
}
