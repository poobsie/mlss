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

struct BattleFixedOrigin;

#define battle_initialize_sprite_motion_zeroed_a sub_8158464
#define battle_sync_sprite_motion_to_origin_a sub_8158738
#define battle_initialize_sprite_motion_idle_a sub_81589A8
#define battle_initialize_sprite_motion_idle_with_sprite sub_81589F0
#define battle_initialize_sprite_motion_state_2_a sub_8158A64
#define battle_setup_sprite_motion_size_a sub_8158B90
#define battle_sync_sprite_motion_to_origin_b sub_815EF80
#define battle_wrap_sprite_motion_x sub_815F08C
#define battle_initialize_sprite_motion_idle_b sub_815F1F0
#define battle_initialize_sprite_motion_state_2_b sub_815F290
#define battle_initialize_sprite_motion_zeroed_b sub_815F354
#define battle_setup_sprite_motion_size_b sub_815F3CC

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
    u8 unknown25;
    u8 variant26;
    u8 unknown27[9];
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
void battle_destroy_sprite_motion_resource_34_variant_c(
    struct BattleSpriteMotion*, void*);
void battle_destroy_sprite_motion_resource_40_variant_c(
    struct BattleSpriteMotion*, void*);
void battle_destroy_sprite_motion_resources_3c_and_40(
    struct BattleSpriteMotion*, void*);
void battle_sync_attached_sprite_position_variant_a(
    struct BattleSpriteMotion*, void*);
void battle_sync_attached_sprite_position_variant_b(
    struct BattleSpriteMotion*, void*);
void* battle_initialize_sprite_motion_zeroed_a(
    struct BattleSpriteMotion*, const struct BattleSpriteMotionConfig*, u16);
void* battle_initialize_sprite_motion_zeroed_b(
    struct BattleSpriteMotion*, const struct BattleSpriteMotionConfig*, u16);
void* battle_initialize_sprite_motion_state_2_a(
    struct BattleSpriteMotion*, const struct BattleSpriteMotionConfig*, u16);
void* battle_initialize_sprite_motion_state_2_b(
    struct BattleSpriteMotion*, const struct BattleSpriteMotionConfig*, u16);
void* battle_initialize_sprite_motion_idle_a(
    struct BattleSpriteMotion*, const struct BattleSpriteMotionConfig*, u16);
void* battle_initialize_sprite_motion_idle_b(
    struct BattleSpriteMotion*, const struct BattleSpriteMotionConfig*, u16);
void* battle_initialize_sprite_motion_idle_with_sprite(
    struct BattleSpriteMotion*, const struct BattleSpriteMotionConfig*, u16);
void battle_sync_sprite_motion_to_origin_a(
    struct BattleSpriteMotion*, const struct BattleFixedOrigin*);
void battle_sync_sprite_motion_to_origin_b(
    struct BattleSpriteMotion*, const struct BattleFixedOrigin*);
void battle_setup_sprite_motion_size_a(struct BattleSpriteMotion*);
void battle_setup_sprite_motion_size_b(struct BattleSpriteMotion*);
s32 battle_wrap_sprite_motion_x(
    struct BattleSpriteMotion*, void*, void*, const s32* originX);

#endif
