#ifndef GUARD_BATTLE_RESOURCE_DESTRUCTORS_H
#define GUARD_BATTLE_RESOURCE_DESTRUCTORS_H

#include "global.h"

#define battle_destroy_runtime_resource_owner sub_8150F60
#define battle_destroy_coordinate_resource_pair sub_8161924

struct BattleRuntimeResourceOwner;
struct BattleCoordinateResourcePair;

void battle_destroy_runtime_resource_owner(
    struct BattleRuntimeResourceOwner* owner, s32 flags);
void battle_destroy_coordinate_resource_pair(
    struct BattleCoordinateResourcePair* owner, s32 flags);

#endif
