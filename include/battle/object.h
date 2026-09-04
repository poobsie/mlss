#ifndef GUARD_BATTLE_OBJECT_H
#define GUARD_BATTLE_OBJECT_H

#include "global.h"

struct BattleObjectDefinition;

struct BattleDefinitionObject {
    u8 unknown00[0x30];
    const struct BattleObjectDefinition* definition;
};

struct BattleSprite {
    u8 unknown00[4];
    u16 size04;
    u16 size06;
    u8 unknown08[4];
    u16 value0C;
    u8 unknown0E[4];
    u8 flags;
};

struct BattleEffectObject {
    u8 unknown00[0x0C];
    struct BattleSprite* sprite;
    u8 unknown10[8];
    s16 value18;
    u8 state1A;
};

struct BattleSpriteOwner {
    struct BattleSprite* sprite;
    const void* vtable;
};

struct BattleSingleSpriteOwner {
    struct BattleSprite* sprite;
};

struct BattleSpriteSlotOwner {
    void* unknown00;
    struct BattleSprite* sprite;
};

struct BattleSpriteTripleOwner {
    struct BattleSprite* sprites[3];
};

struct BattleSpriteMotionOwner {
    struct BattleSprite* sprite;
    const void* vtable;
    u8 unknown08[0x10];
    u16 value18;
    u8 unknown1A[6];
    u16 value20;
    u8 unknown22[2];
    u8 mode24;
    u8 unknown25[0x13];
    u16 value38;
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

struct BattleControlObject {
    u8 unknown000[0xF8];
    u8 flagsF8;
    u8 flagsF9;
    u8 unknown0FA[0x31];
    u8 value12B;
    u8 flags12C;
    u8 flags12D;
    u8 unknown12E[0x1CA];
    s16 motionValue2F8;
    u8 unknown2FA[2];
    s16 motionValue2FC;
};

struct BattleResourceControlObject {
    u8 unknown000[0xFC];
    u16 flagsFC;
    u8 unknown0FE[0x206];
    void* resource304;
};

struct BattleSceneRuntime {
    u8 unknown0000[0x1F28];
    u16 value1F28;
    s16 countdown1F2A;
};

#endif
