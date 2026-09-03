#ifndef GUARD_BATTLE_OBJECT_H
#define GUARD_BATTLE_OBJECT_H

#include "global.h"

struct BattleObjectDefinition;

struct BattleDefinitionObject {
    u8 unknown00[0x30];
    const struct BattleObjectDefinition* definition;
};

struct BattleSprite {
    u8 unknown00[0x12];
    u8 flags;
};

struct BattleEffectObject {
    u8 unknown00[0x0C];
    struct BattleSprite* sprite;
    u8 unknown10[0x0A];
    u8 state1A;
};

struct BattleSpriteOwner {
    struct BattleSprite* sprite;
    const void* vtable;
};

struct BattleVtableObject {
    void* value00;
    const void* vtable;
};

struct BattleRuntimeValues {
    u8 unknown000[0x514];
    u16 value514;
    u8 unknown516[2];
    u16 enabled518;
    u8 unknown51A[0x12];
    u32 value52C;
};

struct BattleValueObject {
    u8 unknown00[0x14];
    u16 value14;
};

#endif
