#ifndef GUARD_FIELD_SPRITE_ATTRIBUTE_SNAPSHOT_H
#define GUARD_FIELD_SPRITE_ATTRIBUTE_SNAPSHOT_H

#include "global.h"

struct FieldSpriteAttributes {
    u8 unknown00[0x0E];
    u16 attribute0E;
    u8 unknown10[0x0F];
    u8 attributeGroup0 : 2;
    u8 attributeGroup1 : 2;
    u8 attributeGroup2 : 2;
    u8 attributeGroup3 : 2;
    u8 attribute20;
};

struct FieldSavedSpriteAttributes {
    struct FieldSpriteAttributes* sprite;
    u8 unknown04[0x0B];
    u8 savedAttribute20;
    u16 unknown10_0 : 3;
    u16 attributeGroup0 : 2;
    u16 attributeGroup1 : 2;
    u16 attributeGroup2 : 2;
    u16 attributeGroup3 : 2;
    u16 unknown10_11 : 5;
    u16 savedAttribute0E;
    u8 unknown14[0x2C];
};

struct FieldSpriteAttributeOwner {
    u8 unknown000[0x158];
    struct FieldSavedSpriteAttributes* records158;
};

struct FieldSpriteAttributeRuntime {
    u8 unknown00[0x14];
    struct FieldSpriteAttributeOwner* spriteAttributeOwner14;
};

#define field_save_indexed_sprite_attributes sub_80F9544
#define field_restore_indexed_sprite_attributes sub_80F95FC

void field_save_indexed_sprite_attributes(
    struct FieldSpriteAttributeRuntime* runtime, u8 index);
void field_restore_indexed_sprite_attributes(
    struct FieldSpriteAttributeRuntime* runtime, u8 index);

#endif
