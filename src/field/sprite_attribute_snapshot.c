#include "field/sprite_attribute_snapshot.h"

#define SEC(symbol) \
    __attribute__((section(".text.small_functions_01." #symbol)))

SEC(sub_80F9544)
void field_save_indexed_sprite_attributes(
    struct FieldSpriteAttributeRuntime* runtime, u8 index)
{
    struct FieldSavedSpriteAttributes* record =
        &runtime->spriteAttributeOwner14->records158[index];
    struct FieldSpriteAttributes* sprite = record->sprite;

    if (sprite != NULL) {
        record->savedAttribute0E = sprite->attribute0E;
        record->savedAttribute20 = sprite->attribute20;
        record->attributeGroup0 = sprite->attributeGroup0;
        record->attributeGroup1 = sprite->attributeGroup1;
        record->attributeGroup2 = sprite->attributeGroup2;
        record->attributeGroup3 = sprite->attributeGroup3;
    } else {
        record->savedAttribute0E = 0x8000;
        record->savedAttribute20 = 0x10;
        record->attributeGroup3 = 1;
        record->attributeGroup2 = 1;
        record->attributeGroup1 = 1;
        record->attributeGroup0 = 1;
    }
}

SEC(sub_80F95FC)
void field_restore_indexed_sprite_attributes(
    struct FieldSpriteAttributeRuntime* runtime, u8 index)
{
    struct FieldSavedSpriteAttributes* record =
        &runtime->spriteAttributeOwner14->records158[index];
    struct FieldSpriteAttributes* sprite = record->sprite;

    sprite->attribute0E = record->savedAttribute0E;
    sprite->attribute20 = record->savedAttribute20;
    sprite->attributeGroup0 = record->attributeGroup0;
    sprite->attributeGroup1 = record->attributeGroup1;
    sprite->attributeGroup2 = record->attributeGroup2;
    sprite->attributeGroup3 = record->attributeGroup3;
}
