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
    s32 verticalAcceleration;
    s32 positionX;
    s32 positionY;
    u8 unknown1C[8];
    s32 velocityX;
    s32 velocityY;
    const void* descriptor;
    void* heightContext;
};

struct BattleCoordinateOrigin {
    s32 x;
    s32 y;
};

#define battle_write_relative_coordinates sub_816127C
#define battle_update_coordinate_projector_motion sub_8161180

void battle_write_relative_coordinates(
    struct BattleCoordinateProjector* projector,
    const struct BattleCoordinateOrigin* origin);
void battle_update_coordinate_projector_motion(
    struct BattleCoordinateProjector* projector);
#endif
