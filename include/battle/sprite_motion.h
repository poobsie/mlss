#ifndef GUARD_BATTLE_SPRITE_MOTION_H
#define GUARD_BATTLE_SPRITE_MOTION_H

#include "battle/object.h"

struct BattleSpriteMotionConfig {
    s16 x;
    s16 y;
    u8 spriteKind;
    u8 animation;
    u8 unknown06;
    u8 unknown07;
    u8 unknown08;
    u8 unknown09;
    u8 palette;
    u8 renderFlags;
    u8 priority;
};

struct BattleSpriteMotion {
    struct BattleSprite* sprite;
    s32 positionX;
    s32 positionY;
    s32 previousX;
    s32 previousY;
    s16 velocityX;
    u8 unknown16[2];
    s16 velocityY;
    u8 unknown1A[0x0A];
    u8 state;
    u8 unknown25[0x0B];
    const void* descriptor;
    union BattleSpriteMotionSlot34 {
        struct {
            u16 value;
            u16 auxiliary;
        } values;
        struct BattleSpriteMotion* child;
        void* ownedResource;
    } slot34;
    s32 savedX;
    union BattleSpriteMotionSlot3C {
        s32 savedY;
        struct BattleSpriteMotion* child;
    } slot3C;
    void* ownedResource40;
    void* ownedResource44;
};

void battle_sprite_motion_apply_velocity(
    struct BattleSpriteMotion* object, s32 yOffset);
void* battle_initialize_sprite_motion_variant_a(
    struct BattleSpriteMotion*, const struct BattleSpriteMotionConfig*, u16);
void* battle_initialize_sprite_motion_variant_b(
    struct BattleSpriteMotion*, const struct BattleSpriteMotionConfig*, u16);
void* battle_initialize_sprite_motion_with_position_snapshot_variant_a(
    struct BattleSpriteMotion*, const struct BattleSpriteMotionConfig*, u16);
void* battle_initialize_sprite_motion_with_position_snapshot_variant_b(
    struct BattleSpriteMotion*, const struct BattleSpriteMotionConfig*, u16);
void battle_prepare_sprite_motion_state_4(struct BattleSpriteMotion* object);
void battle_prepare_sprite_motion_state_2(struct BattleSpriteMotion* object);

#endif
