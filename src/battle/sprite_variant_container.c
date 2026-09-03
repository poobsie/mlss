#include "global.h"

#define SEC(name) __attribute__((section(".text.upper." #name)))

void* alloc_Zero(s32 size, s32 clear, const void* tag, s32 line);
void free_heap_8018DA8(void* object);
void sub_81617F4(void* object, s32 flags);
void sub_8161C08(void* object, s32 flags);
void* sub_8161698(void* object);
void* sub_8161AAC(void* object);

struct BattleSpriteVariantContainer {
    void* unknown00;
    const void* descriptor;
    void* firstVariant;
    void* secondVariant;
    u32 value10;
    u32 value14;
};

SEC(sub_8158044)
void* sub_8158044(struct BattleSpriteVariantContainer* object)
{
    object->unknown00 = 0;
    object->descriptor = (void*)0x08CDC4D0;
    object->value10 = 0;
    object->value14 = 0;
    object->firstVariant = 0;
    object->secondVariant = 0;
    if ((s32)((s32)(*(u8*)0x03001010 << 0x1B) >> 0x1B) <= 5) {
        object->secondVariant =
            sub_8161AAC(alloc_Zero(0x34, 1, (void*)0x082126E0, 0));
    } else {
        object->firstVariant =
            sub_8161698(alloc_Zero(0x34, 1, (void*)0x082126E0, 0));
    }
    return object;
}

SEC(sub_8158000)
void sub_8158000(struct BattleSpriteVariantContainer* object, s32 flags)
{
    void* first;
    void* second;

    object->descriptor = (void*)0x08CDC4D0;
    first = object->firstVariant;
    if (first != 0)
        sub_81617F4(first, 3);
    second = object->secondVariant;
    if (second != 0)
        sub_8161C08(second, 3);
    object->descriptor = (void*)0x08CDCA30;
    if (flags & 1)
        free_heap_8018DA8(object);
}

void* battle_initialize_sprite_variant_container(
    struct BattleSpriteVariantContainer*)
    __attribute__((alias("sub_8158044")));
void battle_destroy_sprite_variant_container(
    struct BattleSpriteVariantContainer*, s32)
    __attribute__((alias("sub_8158000")));
