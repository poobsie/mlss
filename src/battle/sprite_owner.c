#include "global.h"
#include "battle/functions.h"
#include "battle/object.h"

void sprite_hide_8021F20(void* sprite);
void sprite_show_8020CBC(void* sprite);
void sub_8021308(void* sprite);
void sub_815FAE4(void* object, int y);
extern s32 sub_816504C(void* object);

struct BattleTileBufferOwner {
    u8 unknown00[0x30];
    void* tileBufferOwner;
};

s32 battle_refresh_owned_tile_buffer(struct BattleTileBufferOwner* object)
    __attribute__((section(".text.sub_81580E0")));
s32 battle_refresh_owned_tile_buffer(struct BattleTileBufferOwner* object) {
    if (sub_816504C(object->tileBufferOwner) != 0)
        return 1;
    return 0;
}
__attribute__((section(".text.sub_81580E0")))
const u16 battle_refresh_owned_tile_buffer_padding = 0;

struct BattleSprite* battle_sprite_owner_get_sprite(struct BattleSpriteOwner* object)
    __attribute__((section(".text.sub_815FA3C")));
struct BattleSprite* battle_sprite_owner_get_sprite(struct BattleSpriteOwner* object) {
    return object->sprite;
}

void battle_sprite_owner_hide_sprite(struct BattleSpriteOwner* object)
    __attribute__((section(".text.sub_815FA40")));
void battle_sprite_owner_hide_sprite(struct BattleSpriteOwner* object) {
    struct BattleSprite* sprite = object->sprite;
    if (sprite != 0) {
        sprite_hide_8021F20(sprite);
    }
}

void battle_sprite_owner_show_sprite(struct BattleSpriteOwner* object)
    __attribute__((section(".text.sub_815FA50")));
void battle_sprite_owner_show_sprite(struct BattleSpriteOwner* object) {
    struct BattleSprite* sprite = object->sprite;
    if (sprite != 0) {
        sprite_show_8020CBC(sprite);
    }
}

void battle_forward_sprite_y(void* object, int unused, int y)
    __attribute__((section(".text.sub_815F56C")));
void battle_forward_sprite_y(void* object, int unused, int y) {
    sub_815FAE4(object, y);
}

void battle_sprite_owner_release_sprite(struct BattleSpriteOwner* object)
    __attribute__((section(".text.sub_815FAFC")));
void battle_sprite_owner_release_sprite(struct BattleSpriteOwner* object) {
    struct BattleSprite* sprite = object->sprite;
    if (sprite != 0) {
        sub_8021308(sprite);
        object->sprite = 0;
    }
}
