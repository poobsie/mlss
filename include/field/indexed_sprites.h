#ifndef GUARD_FIELD_INDEXED_SPRITES_H
#define GUARD_FIELD_INDEXED_SPRITES_H

#include "common.h"

struct FieldIndexedSpriteEntry {
    struct Sprite* sprite;
    u8 unknown04[0x3C];
};

struct FieldIndexedSpriteOwner {
    u8 unknown00[0x158];
    struct FieldIndexedSpriteEntry* entries;
};

#define field_set_indexed_sprite_position sub_81218E4
void field_set_indexed_sprite_position(
    struct FieldIndexedSpriteOwner* owner, u8 index, s32 x, s32 y);

#define field_update_indexed_sprite sub_8121910
void field_update_indexed_sprite(
    struct FieldIndexedSpriteOwner* owner, u8 index, s32 packedPosition);

#endif
