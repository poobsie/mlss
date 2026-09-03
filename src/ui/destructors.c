#include "ui/functions.h"
#include "ui/object.h"

void free_heap_8018DA8(void* pointer);
void sub_8021308(void* sprite);

void ui_sprite_pair_destroy_base(struct UiSpritePair* object, s32 flags)
    __attribute__((section(".text.upper.sub_8163B60")));
void ui_sprite_pair_destroy_base(struct UiSpritePair* object, s32 flags) {
    object->vtable = (void*)0x08CDD0F8;
    if (object->firstSprite != 0)
        sub_8021308(object->firstSprite);
    if (object->secondSprite != 0)
        sub_8021308(object->secondSprite);
    object->vtable = (void*)0x08CDD118;
    if (flags & 1)
        free_heap_8018DA8(object);
}

void ui_sprite_pair_destroy_variant(struct UiSpritePair* object, s32 flags)
    __attribute__((section(".text.freeing_destructors.sub_8163D4C")));
void ui_sprite_pair_destroy_variant(struct UiSpritePair* object, s32 flags) {
    object->vtable = (void*)0x08CDD118;
    if (flags & 1)
        free_heap_8018DA8(object);
}
