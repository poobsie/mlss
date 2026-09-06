#ifndef GUARD_BATTLE_COORDINATE_STATE_H
#define GUARD_BATTLE_COORDINATE_STATE_H

#include "global.h"

struct Sprite;

struct BattleCoordinateProjector {
    u8 unknown00[6];
    s16 spriteResourceId;
    u8 unknown08[4];
    struct Sprite* output;
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
#define battle_coordinate_projector_create_sprite sub_81612F8
#define battle_destroy_coordinate_projector sub_8161330

void battle_write_relative_coordinates(
    struct BattleCoordinateProjector* projector,
    const struct BattleCoordinateOrigin* origin);
void battle_update_coordinate_projector_motion(
    struct BattleCoordinateProjector* projector);
void battle_coordinate_projector_create_sprite(
    struct BattleCoordinateProjector* projector, s32 variant);
void battle_destroy_coordinate_projector(
    struct BattleCoordinateProjector* projector, u32 flags);
#endif
