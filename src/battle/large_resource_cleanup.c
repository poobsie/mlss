#include "global.h"
#include "battle/functions.h"
#include "battle/object.h"

#define SEC(name) __attribute__((section(".text.upper." #name)))

void sub_8021308(void* sprite);
void free_heap_8018D9C(void* resource);
void free_heap_8018DA8(void* object);
void sprite_show_8020CBC(struct BattleSprite* sprite);
struct BattleSprite* sub_8020DD0(s32, s32, s32, s32, s32, s32, s32);
void sub_801E150(struct BattleSprite*, s32, s32, s32, s32);

SEC(sub_815D8CC)
struct BattleSpriteArrayOwner9* battle_initialize_sprite_array9(
    struct BattleSpriteArrayOwner9* object)
{
    s32 i;

    for (i = 0; i <= 8; i++) {
        object->sprites[i] = sub_8020DD0(4, 0x5005, 0, -1, -1, -1, -1);
        if (i > 3)
            object->sprites[i]->xPosition = (i + 1) * 16 + 40;
        else
            object->sprites[i]->xPosition = i * 16 + 40;
        object->sprites[i]->yPosition = 60;
        sub_801E150(object->sprites[i], i + 10, -1, 0, 0);
        object->delays[i] = 0;
        object->phases[i] = i * 4 + i;
        object->angles[i] = 0;
    }
    object->countdown = 1000;
    return object;
}
SEC(sub_815D8CC) const u16 battle_initialize_sprite_array9_padding = 0;

SEC(sub_815EA64)
void battle_show_sprite_array9(struct BattleSpriteArrayOwner9* object)
{
    struct BattleSprite** sprites = object->sprites;

    if (object->sprites[0] != 0) sprite_show_8020CBC(object->sprites[0]);
    if (sprites[1] != 0) sprite_show_8020CBC(sprites[1]);
    if (object->sprites[2] != 0) sprite_show_8020CBC(object->sprites[2]);
    if (object->sprites[3] != 0) sprite_show_8020CBC(object->sprites[3]);
    if (object->sprites[4] != 0) sprite_show_8020CBC(object->sprites[4]);
    if (object->sprites[5] != 0) sprite_show_8020CBC(object->sprites[5]);
    if (object->sprites[6] != 0) sprite_show_8020CBC(object->sprites[6]);
    if (object->sprites[7] != 0) sprite_show_8020CBC(object->sprites[7]);
    if (object->sprites[8] != 0) sprite_show_8020CBC(object->sprites[8]);
}
SEC(sub_815EA64) const u16 battle_show_sprite_array9_padding = 0;

SEC(sub_815EB70)
void battle_destroy_sprite_array5(struct BattleSpriteArrayOwner5* object, s32 flags)
{
    struct BattleSprite** sprites = object->sprites;
    if (object->sprites[0] != 0)
        sub_8021308(object->sprites[0]);
    if (sprites[1] != 0)
        sub_8021308(sprites[1]);
    if (object->sprites[2] != 0)
        sub_8021308(object->sprites[2]);
    if (object->sprites[3] != 0)
        sub_8021308(object->sprites[3]);
    if (object->sprites[4] != 0)
        sub_8021308(object->sprites[4]);
    if (flags & 1)
        free_heap_8018DA8(object);
}
SEC(sub_815EB70) const u16 sub_815EB70_padding = 0;

SEC(sub_815EACC)
void battle_destroy_sprite_array9(struct BattleSpriteArrayOwner9* object, s32 flags)
{
    struct BattleSprite** sprites = object->sprites;
    if (object->sprites[0] != 0) sub_8021308(object->sprites[0]);
    if (sprites[1] != 0) sub_8021308(sprites[1]);
    if (object->sprites[2] != 0) sub_8021308(object->sprites[2]);
    if (object->sprites[3] != 0) sub_8021308(object->sprites[3]);
    if (object->sprites[4] != 0) sub_8021308(object->sprites[4]);
    if (object->sprites[5] != 0) sub_8021308(object->sprites[5]);
    if (object->sprites[6] != 0) sub_8021308(object->sprites[6]);
    if (object->sprites[7] != 0) sub_8021308(object->sprites[7]);
    if (object->sprites[8] != 0) sub_8021308(object->sprites[8]);
    if (flags & 1)
        free_heap_8018DA8(object);
}
SEC(sub_815EACC) const u16 sub_815EACC_padding = 0;

struct BattleLargeSpriteOwner {
    u8 unknown000[0x524];
    void* sprite524;
};

SEC(sub_8159A64)
void sub_8159A64(struct BattleLargeSpriteOwner* object, s32 flags)
{
    if (object->sprite524 != 0)
        sub_8021308(object->sprite524);
    if (flags & 1)
        free_heap_8018DA8(object);
}

SEC(sub_8160E6C)
void sub_8160E6C(struct BattleLargeResourceOwner* object)
{
    if (object->resource804 != 0) {
        free_heap_8018D9C(object->resource804);
        object->resource804 = 0;
    }
    if (object->resource80C != 0) {
        free_heap_8018D9C(object->resource80C);
        object->resource80C = 0;
    }
}

SEC(sub_8160EA4)
void battle_destroy_large_resource_pair(struct BattleLargeResourceOwner* object, s32 flags)
{
    sub_8160E6C(object);
    if (flags & 1)
        free_heap_8018DA8(object);
}

SEC(sub_8160EA4) const u16 sub_8160EA4_padding = 0;

void battle_destroy_large_sprite_owner(
    struct BattleLargeSpriteOwner*, s32)
    __attribute__((alias("sub_8159A64")));
void battle_release_large_resource_pair(struct BattleLargeResourceOwner*)
    __attribute__((alias("sub_8160E6C")));
