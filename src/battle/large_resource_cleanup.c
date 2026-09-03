#include "global.h"

#define SEC(name) __attribute__((section(".text.upper." #name)))

void sub_8021308(void* sprite);
void free_heap_8018D9C(void* resource);
void free_heap_8018DA8(void* object);

struct BattleLargeSpriteOwner {
    u8 unknown000[0x524];
    void* sprite524;
};

struct BattleLargeResourceOwner {
    u8 unknown000[0x804];
    void* resource804;
    u8 unknown808[4];
    void* resource80C;
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

void battle_destroy_large_sprite_owner(
    struct BattleLargeSpriteOwner*, s32)
    __attribute__((alias("sub_8159A64")));
void battle_release_large_resource_pair(struct BattleLargeResourceOwner*)
    __attribute__((alias("sub_8160E6C")));
