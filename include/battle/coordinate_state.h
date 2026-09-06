#ifndef GUARD_BATTLE_COORDINATE_STATE_H
#define GUARD_BATTLE_COORDINATE_STATE_H

#include "global.h"

struct BattleCoordinatePair {
    s16 x;
    s16 y;
};

struct BattleCoordinateProjector {
    u8 unknown00[0x0C];
    struct BattleCoordinatePair* output;
    u8 unknown10[4];
    s32 positionX;
    s32 positionY;
};

struct BattleCoordinateOrigin {
    s32 x;
    s32 y;
};

#define battle_write_relative_coordinates sub_816127C

void battle_write_relative_coordinates(
    struct BattleCoordinateProjector* projector,
    const struct BattleCoordinateOrigin* origin);
#endif
