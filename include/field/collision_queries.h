#ifndef GUARD_FIELD_COLLISION_QUERIES_H
#define GUARD_FIELD_COLLISION_QUERIES_H

#include "global.h"

struct FieldCollisionQuery;

#define field_collision_query_owner_enabled sub_80FBE5C
#define field_collision_test_owner_unbounded sub_80FC148

u8 field_collision_query_owner_enabled(
    void* unused, const struct FieldCollisionQuery* query);
u8 field_collision_test_owner_unbounded(
    void* unused, const struct FieldCollisionQuery* query);

#endif
