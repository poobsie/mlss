#ifndef GUARD_BATTLE_NUMBER_DISPLAY_H
#define GUARD_BATTLE_NUMBER_DISPLAY_H

#include "battle/object.h"

union BattleNumberDisplaySpriteSlot {
    struct BattleSprite* sprite;
    u16 lowHandle;
};

union BattleNumberDisplayValueState {
    struct {
        s16 current;
        u16 padding;
    } half;
    u32 packed;
};

struct BattleNumberDisplay {
    union BattleNumberDisplaySpriteSlot hundreds;
    union BattleNumberDisplaySpriteSlot tens;
    union BattleNumberDisplaySpriteSlot ones;
    s32 positionX;
    s32 positionY;
    void* digitWorkspace;
    union BattleNumberDisplayValueState value;
    s32 displayedValue;
    u32 adjustmentDirection;
    u32 adjustmentTimer;
};

#define battle_number_display_initialize sub_8158220
#define battle_number_display_adjust_value sub_81582CC

struct BattleNumberDisplay* battle_number_display_initialize(
    struct BattleNumberDisplay* display);
void battle_number_display_adjust_value(
    struct BattleNumberDisplay* display, s16 adjustment);

#endif
