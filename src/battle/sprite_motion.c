#include "battle/sprite_motion.h"
#include "battle/functions.h"

#define SEC(name) __attribute__((section(".text.text_upper_structural." #name)))

SEC(sub_815FAE4)
void sub_815FAE4(struct BattleSpriteMotion* object, s32 yOffset)
{
    s32 delta;
    s32 y;
    object->positionX += object->velocityX;
    delta = object->velocityY;
    y = object->positionY;
    y += delta;
    y += yOffset;
    object->positionY = y;
}

void battle_sprite_motion_apply_velocity(
    struct BattleSpriteMotion*, s32) __attribute__((alias("sub_815FAE4")));

void battle_sprite_motion_configure_mode_4(
    struct BattleSpriteMotionOwner* object, s32 value)
    __attribute__((section(".text.text_late_helpers.sub_8158A98")));
void battle_sprite_motion_configure_mode_4(
    struct BattleSpriteMotionOwner* object, s32 value)
{
    struct BattleSprite* sprite;
    u16 zero = 0;

    object->value18 = 0xC8;
    object->value20 = -value;
    object->value38 = zero;
    sprite = battle_sprite_owner_get_sprite((struct BattleSpriteOwner*)object);
    sprite->value0C = zero;
    object->mode24 = 4;
}

void battle_sprite_motion_configure_mode_3(
    struct BattleSpriteMotionOwner* object, s32 value)
    __attribute__((section(".text.text_late_helpers.sub_815F2C4")));
void battle_sprite_motion_configure_mode_3(
    struct BattleSpriteMotionOwner* object, s32 value)
{
    struct BattleSprite* sprite;
    u16 zero = 0;

    object->value18 = 0x64;
    object->value20 = -value;
    object->value38 = zero;
    sprite = battle_sprite_owner_get_sprite((struct BattleSpriteOwner*)object);
    sprite->value0C = zero;
    object->mode24 = 3;
}
