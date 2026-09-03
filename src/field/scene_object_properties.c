#include "field/functions.h"
#include "field/scene_object.h"

#define FIELD_SECTION(name) __attribute__((section(name)))

void field_set_flags_20d_217(struct FieldSceneObject* object)
    FIELD_SECTION(".text.sub_8047784");
void field_set_flags_20d_217(struct FieldSceneObject* object) {
    ((u8*)object)[0x20D] |= 0x10;
    ((u8*)object)[0x217] |= 1;
}

void field_set_value_239_and_sprite_20(struct FieldSceneObject* object, u8 value)
    FIELD_SECTION(".text.sub_804790C");
void field_set_value_239_and_sprite_20(struct FieldSceneObject* object, u8 value) {
    ((u8*)object)[0x239] = value;
    ((u8*)object->sprite)[0x20] = value;
}

void field_set_value_23e(struct FieldSceneObject* object, u16 value)
    FIELD_SECTION(".text.sub_804794C");
void field_set_value_23e(struct FieldSceneObject* object, u16 value) {
    object->value23E = value;
}

void field_clear_flags_2b5_high_bits(struct FieldSceneObject* object)
    FIELD_SECTION(".text.sub_8047994");
void field_clear_flags_2b5_high_bits(struct FieldSceneObject* object) {
    ((u8*)object)[0x2B5] &= 0x3F;
}

int field_test_flag_2b5_08(struct FieldSceneObject* object)
    FIELD_SECTION(".text.sub_8047AF4");
int field_test_flag_2b5_08(struct FieldSceneObject* object) {
    return (object->flags2B5 >> 3) & 1;
}

void field_shift_value_266_to_previous(struct FieldSceneObject* object, u16 value)
    FIELD_SECTION(".text.early_bitfield_updates.sub_8047B5C");
void field_shift_value_266_to_previous(struct FieldSceneObject* object, u16 value) {
    s32 offset = 0x266;
    u16* source = (u16*)((u8*)object + offset);
    u16 previous = *source;
    offset = 0x268;
    *(u16*)((u8*)object + offset) = previous;
    *source = value;
}
