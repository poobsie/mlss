#include "battle/resource_destructors.h"

#define SEC(symbol) __attribute__((section(".text.battle_resource_destructors." #symbol)))

void free_heap_8018D9C(void* pointer);
void free_heap_8018DA8(void* pointer);
void sub_8021308(void* resource);

struct BattleRuntimeResourceOwner {
    void* buffer;
    u8 unknown04[0x24];
    void* resource;
};

struct BattleCoordinateResourcePair {
    u8 unknown00[8];
    void* firstResource;
    void* secondResource;
};

SEC(sub_8150F60)
void battle_destroy_runtime_resource_owner(
    struct BattleRuntimeResourceOwner* owner, s32 flags)
{
    if (owner->resource != 0)
        sub_8021308(owner->resource);
    if (owner->buffer != 0)
        free_heap_8018D9C(owner->buffer);
    if (flags & 1)
        free_heap_8018DA8(owner);
}
const u16 battle_destroy_runtime_resource_owner_padding SEC(sub_8150F60) = 0;

SEC(sub_8161924)
void battle_destroy_coordinate_resource_pair(
    struct BattleCoordinateResourcePair* owner, s32 flags)
{
    if (owner->firstResource != 0)
        sub_8021308(owner->firstResource);
    if (owner->secondResource != 0)
        sub_8021308(owner->secondResource);
    if (flags & 1)
        free_heap_8018DA8(owner);
}
const u16 battle_destroy_coordinate_resource_pair_padding SEC(sub_8161924) = 0;
