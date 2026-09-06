#include "field/indexed_sprites.h"

#define SEC(symbol) __attribute__((section(".text.field_indexed_sprites." #symbol)))

SEC(sub_81218E4)
void field_set_indexed_sprite_position(
    struct FieldIndexedSpriteOwner* owner, u8 index, s32 x, s32 y)
{
    sub_801E150(owner->entries[index].sprite, x, y, 0, 0);
}

SEC(sub_81218E4)
const u16 sub_81218E4_padding = 0;

SEC(sub_8121910)
void field_update_indexed_sprite(
    struct FieldIndexedSpriteOwner* owner, u8 index, s32 packedPosition)
{
    struct FieldIndexedSpriteEntry* entry = &owner->entries[index];
    struct Sprite* sprite = entry->sprite;

    if (sprite == NULL) {
        s32 frame = (packedPosition >> 12) - 1;
        s32 unset = -1;
        struct Sprite* created;

        created = sub_8020DD0(frame, packedPosition, 1, unset, unset, unset, unset);
        entry->sprite = created;
        sub_801E150(created, 0, unset, 0, (s32)sprite);
    } else {
        sub_80210A8(
            sprite, (packedPosition >> 12) - 1, packedPosition, 1, -1, -1, -1, -1);
    }
}
