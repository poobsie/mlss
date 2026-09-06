#include "global.h"
#include "field/collision_queries.h"

#define SEC(name) __attribute__((section(".text.field_collision_queries." #name)))

struct FieldCollisionQuery {
    void* owner;
    u8 unknown04[7];
    u8 flags0B;
    struct FieldCollisionQueryBounds bounds;
};

struct FieldCollisionQueryOwner {
    u8 unknown00[0x1D6];
    u8 flags1D6;
};

SEC(sub_80FBDE0)
u8 field_collision_point_within_bounds(
    const struct FieldCollisionQueryBounds* bounds,
    const struct FieldCollisionObjectPosition* object,
    s16 maximumZ, s16 minimumZ)
{
    s16 x = object->x / 0x100;
    s16 y = object->y / 0x100;
    s16 z = (object->z + object->height) / 0x100;

    if (x >= bounds->minimumX && x <= bounds->maximumX &&
        y >= bounds->minimumY && y <= bounds->maximumY &&
        z >= minimumZ && z <= maximumZ)
        return 1;
    return 0;
}

SEC(sub_80FBE5C)
u8 field_collision_query_owner_enabled(
    void* unused, const struct FieldCollisionQuery* query)
{
    const struct FieldCollisionQueryOwner* owner = query->owner;

    if (owner->flags1D6 & 1)
        return 1;
    return 0;
}
SEC(sub_80FBE5C) const u16 sub_80FBE5C_padding = 0;

SEC(sub_80FC148)
u8 field_collision_test_owner_unbounded(
    void* unused, const struct FieldCollisionQuery* query)
{
    const u8* cursor = (const u8*)query;
    void* owner = *(void**)cursor;

    cursor += 0x0C;
    return sub_80FBDE0(
        (const struct FieldCollisionQueryBounds*)cursor, owner, 0x7FFF, 0);
}
