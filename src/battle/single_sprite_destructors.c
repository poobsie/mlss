#include "battle/object.h"

#define SEC(name) __attribute__((section(".text.upper." #name)))

void sub_8021308(void* sprite);
void free_heap_8018DA8(void* object);

#define DEFINE_SINGLE_SPRITE_DESTRUCTOR(name)                            \
SEC(name) void name(struct BattleSingleSpriteOwner* object, s32 flags)   \
{                                                                        \
    sub_8021308(object->sprite);                                         \
    if (flags & 1)                                                       \
        free_heap_8018DA8(object);                                       \
}

DEFINE_SINGLE_SPRITE_DESTRUCTOR(sub_81617F4)
DEFINE_SINGLE_SPRITE_DESTRUCTOR(sub_8161A38)
DEFINE_SINGLE_SPRITE_DESTRUCTOR(sub_8161C08)

void battle_destroy_single_sprite_owner_variant_a(
    struct BattleSingleSpriteOwner*, s32)
    __attribute__((alias("sub_81617F4")));
void battle_destroy_single_sprite_owner_variant_b(
    struct BattleSingleSpriteOwner*, s32)
    __attribute__((alias("sub_8161A38")));
void battle_destroy_single_sprite_owner_variant_c(
    struct BattleSingleSpriteOwner*, s32)
    __attribute__((alias("sub_8161C08")));

SEC(sub_81581FC)
void sub_81581FC(struct BattleSpriteSlotOwner* object, s32 flags)
{
    if (object->sprite != 0)
        sub_8021308(object->sprite);
    if (flags & 1)
        free_heap_8018DA8(object);
}

SEC(sub_8158330)
void sub_8158330(struct BattleSpriteTripleOwner* object, s32 flags)
{
    if (object->sprites[0] != 0)
        sub_8021308(object->sprites[0]);
    if (object->sprites[1] != 0)
        sub_8021308(object->sprites[1]);
    if (object->sprites[2] != 0)
        sub_8021308(object->sprites[2]);
    if (flags & 1)
        free_heap_8018DA8(object);
}

void battle_destroy_sprite_slot_owner(struct BattleSpriteSlotOwner*, s32)
    __attribute__((alias("sub_81581FC")));
void battle_destroy_sprite_triple_owner(struct BattleSpriteTripleOwner*, s32)
    __attribute__((alias("sub_8158330")));
