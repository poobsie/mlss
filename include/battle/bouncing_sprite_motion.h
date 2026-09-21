#ifndef GUARD_BATTLE_BOUNCING_SPRITE_MOTION_H
#define GUARD_BATTLE_BOUNCING_SPRITE_MOTION_H

#include "battle/object.h"

struct BattleBouncingSpriteEntry {
    struct BattleSprite* sprite;
    s32 positionX;
    s32 positionY;
    s32 unknown0C;
    s32 velocityY;
    s32 offsetX;
    s32 offsetY;
};

struct BattleBouncingSpriteMotion {
    struct BattleBouncingSpriteEntry entries[1];
    s32 initialPositionX;
    s32 unknown20;
    s32 unknown24;
    s32 unknown28;
    s32 completionDelay;
    s32 state;
};

struct BattleSpriteVariantContainer {
    void* unknown00;
    const void* descriptor;
    struct BattleBouncingSpriteMotion* firstVariant;
    struct BattleBouncingSpriteMotion* secondVariant;
    u32 value10;
    u32 value14;
};

#define battle_initialize_bouncing_sprite_variant_a sub_8161698
#define battle_initialize_bouncing_sprite_variant_b sub_8161AAC
#define battle_update_bouncing_sprite_variant_a sub_8161780
#define battle_update_bouncing_sprite_variant_b sub_8161B94

struct BattleBouncingSpriteMotion* battle_initialize_bouncing_sprite_variant_a(
    struct BattleBouncingSpriteMotion* object);
struct BattleBouncingSpriteMotion* battle_initialize_bouncing_sprite_variant_b(
    struct BattleBouncingSpriteMotion* object);
s32 battle_update_bouncing_sprite_variant_a(
    struct BattleBouncingSpriteMotion* object);
s32 battle_update_bouncing_sprite_variant_b(
    struct BattleBouncingSpriteMotion* object);

void* battle_initialize_sprite_variant_container(
    struct BattleSpriteVariantContainer* object);
void battle_destroy_sprite_variant_container(
    struct BattleSpriteVariantContainer* object, s32 flags);

#endif
