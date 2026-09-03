#include "field/functions.h"
#include "field/scene_object.h"

#define FIELD_SECTION(name) __attribute__((section(name)))

void sub_8116654(void* table, u8 index);
void sub_8116680(void* table, u8 index);
void sub_804761C(struct FieldSceneObject* object, u32 value);

struct __attribute__((packed)) LowBit {
    u8 value : 1;
};

struct __attribute__((packed)) MiddleTwoBits {
    u8 low : 4;
    u8 value : 2;
};

void field_set_flag_20c_01(struct FieldSceneObject* object, u32 value)
    FIELD_SECTION(".text.early_code_helpers.sub_804776C");
void field_set_flag_20c_01(struct FieldSceneObject* object, u32 value) {
    ((struct LowBit*)&object->flags20C)->value = value;
}

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

void field_clear_flags_2b6_30(struct FieldSceneObject* object)
    FIELD_SECTION(".text.early_code_helpers.sub_8047958");
void field_clear_flags_2b6_30(struct FieldSceneObject* object) {
    ((struct MiddleTwoBits*)&object->flags2B6)->value = 0;
}

void field_clear_flags_2b5_high_bits(struct FieldSceneObject* object)
    FIELD_SECTION(".text.sub_8047994");
void field_clear_flags_2b5_high_bits(struct FieldSceneObject* object) {
    ((u8*)object)[0x2B5] &= 0x3F;
}

void field_clear_flags_2b5_30(struct FieldSceneObject* object)
    FIELD_SECTION(".text.early_code_helpers.sub_80479A8");
void field_clear_flags_2b5_30(struct FieldSceneObject* object) {
    ((struct MiddleTwoBits*)&object->flags2B5)->value = 0;
}

int field_test_flag_2b5_08(struct FieldSceneObject* object)
    FIELD_SECTION(".text.sub_8047AF4");
int field_test_flag_2b5_08(struct FieldSceneObject* object) {
    return (object->flags2B5 >> 3) & 1;
}

int field_test_flag_291_01(struct FieldSceneObject* object)
    FIELD_SECTION(".text.early_code_helpers.sub_803E9F0");
int field_test_flag_291_01(struct FieldSceneObject* object) {
    return 1 & object->flags291;
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

void field_selected_entry_change_state_2_to_1(struct FieldSceneObject* object)
    FIELD_SECTION(".text.early_code_helpers.sub_8047D44");
void field_selected_entry_change_state_2_to_1(struct FieldSceneObject* object) {
    sub_8116654(object->entryStateTable, object->selectedEntryIndex);
}

void field_selected_entry_change_state_1_to_2(struct FieldSceneObject* object)
    FIELD_SECTION(".text.early_code_helpers.sub_8047D64");
void field_selected_entry_change_state_1_to_2(struct FieldSceneObject* object) {
    sub_8116680(object->entryStateTable, object->selectedEntryIndex);
}

void field_apply_position_delta(void* unused, struct FieldSceneObject* object)
    FIELD_SECTION(".text.text_late_helpers.sub_81507EC");
void field_apply_position_delta(void* unused, struct FieldSceneObject* object) {
    object->positionX += object->positionDeltaX;
    object->positionY += object->positionDeltaY;
}

void field_clear_scene_object_modes(struct FieldSceneObject* object)
    FIELD_SECTION(".text.upper.sub_8150590");
void field_clear_scene_object_modes(struct FieldSceneObject* object)
{
    field_set_flag_20c_01(object, 0);
    sub_804761C(object, 0);
}
