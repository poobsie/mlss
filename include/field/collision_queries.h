#ifndef GUARD_FIELD_COLLISION_QUERIES_H
#define GUARD_FIELD_COLLISION_QUERIES_H

#include "global.h"

struct FieldCollisionQuery;

struct FieldCollisionQueryBounds {
    s16 minimumX;
    s16 maximumX;
    s16 maximumY;
    s16 minimumY;
    s16 extent08;
    s16 extent0A;
    s8 objectSelector;
};

struct FieldCollisionObjectPosition {
    s8 selector00;
    u8 unknown01[0x0B];
    s32 x;
    s32 y;
    s32 z;
    s32 height;
};

#define field_collision_query_owner_enabled sub_80FBE5C
#define field_collision_point_within_bounds sub_80FBDE0
#define field_collision_test_owner_unbounded sub_80FC148

u8 field_collision_query_owner_enabled(
    void* unused, const struct FieldCollisionQuery* query);
u8 field_collision_point_within_bounds(
    const struct FieldCollisionQueryBounds* bounds,
    const struct FieldCollisionObjectPosition* object,
    s16 maximumZ, s16 minimumZ);
u8 field_collision_test_owner_unbounded(
    void* unused, const struct FieldCollisionQuery* query);

#endif
