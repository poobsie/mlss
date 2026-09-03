#include "battle/functions.h"
#include "battle/object.h"

void battle_sprite_motion_configure_mode_4(
    struct BattleSpriteMotionOwner* object, s32 value)
    __attribute__((section(".text.text_late_helpers.sub_8158A98")));
void battle_sprite_motion_configure_mode_4(
    struct BattleSpriteMotionOwner* object, s32 value) {
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
    struct BattleSpriteMotionOwner* object, s32 value) {
    struct BattleSprite* sprite;
    u16 zero = 0;

    object->value18 = 0x64;
    object->value20 = -value;
    object->value38 = zero;
    sprite = battle_sprite_owner_get_sprite((struct BattleSpriteOwner*)object);
    sprite->value0C = zero;
    object->mode24 = 3;
}
