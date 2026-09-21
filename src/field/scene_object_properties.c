#include "field/functions.h"
#include "field/scene_object.h"

#define FIELD_SECTION(name) __attribute__((section(name)))

void sub_8047EB8(struct FieldSceneObject* object);

FIELD_SECTION(".text.field_scene_callbacks.sub_8139200")
void field_scene_update_vertical_deceleration(struct FieldSceneObject* object)
{
    u8 flags;
    s32 clearMask;

    if (object->motionState25C != -1) {
        object->elevationOffset += object->motionVelocity258;
        object->motionVelocity258 -= object->motionAcceleration248;
        object->motionState25C++;
        if (object->elevationOffset <= 0) {
            object->elevationOffset = 0;
            object->motionState25C = -1;
            flags = object->flags2B5;
            clearMask = FIELD_SCENE_FLAGS_2B5_08 + 1;
            clearMask = -clearMask;
            clearMask &= flags;
            object->flags2B5 = clearMask;
        }
    }
}
FIELD_SECTION(".text.field_scene_callbacks.sub_8139200")
const u32 field_scene_update_vertical_deceleration_padding = 0x00004770;

FIELD_SECTION(".text.field_scene_properties.sub_8139030")
void field_scene_load_scaled_bounds(
    struct FieldSceneObject* object, s32 halfwordOffset)
{
    struct FieldSceneLayoutRegion* layout = &object->layout100;
    const s16* source = object->boundsTable1B4 + (s16)halfwordOffset;

    layout->boundsXStart = *source * 16 + 8;
    source++;
    layout->boundsYStart = *source * 16 + 8;
    source++;
    layout->boundsXEnd = *source * 16 + 8;
    layout->boundsYEnd = source[1] * 16 + 8;
}

FIELD_SECTION(".text.field_scene_properties.sub_8139070")
void field_scene_copy_four_selection_values(
    struct FieldSceneObject* object, s32 halfwordOffset)
{
    const u16* source =
        (const u16*)object->selectionTable + (s16)halfwordOffset;
    struct FieldSceneLayoutRegion* layout = &object->layout100;
    s16 index;

    index = 0;
    while (index <= 3) {
        layout->selectionValues[index] = *source;
        index++;
        source++;
    }
}
FIELD_SECTION(".text.field_scene_properties.sub_8139070")
const u16 field_scene_copy_four_selection_values_padding = 0;

FIELD_SECTION(".text.field_scene_object_motion.sub_80402C4")
void field_step_scene_vertical_motion(struct FieldSceneObject* object)
{
    s32* motionState;
    s32 basePosition;
    u8 motionLimitFlag;

    motionState = &object->motionState25C;
    if (*motionState >= 0) {
        object->elevationOffset += object->motionVelocity258;
        object->motionVelocity258 -= object->motionAcceleration248;
        motionLimitFlag = 0x20 & object->flags20D;
        if (motionLimitFlag == 0) {
            if (object->elevationOffset <= 0) {
                sub_8047EB8(object);
                object->elevationOffset = motionLimitFlag;
                return;
            }
            goto advance_motion_state;
        }
        if (object->baseElevation + object->elevationOffset <=
                   object->motionLimit24C) {
            sub_8047EB8(object);
            basePosition = object->baseElevation;
            if (basePosition + object->elevationOffset < 0)
                object->elevationOffset = 0 - basePosition;
        } else {
        advance_motion_state:
            *motionState = *motionState + 1;
        }
    }
}

FIELD_SECTION(".text.field_scene_object.sub_8046980")
void sub_8046980(struct FieldSceneObject* object);

void sub_8046980(struct FieldSceneObject* object) {
    u32 positionX;
    u32 positionY;
    u32 baseElevation;
    u32 elevationOffset;
    s32 mask;

    mask = -8;
    if ((object->flags2B5 & 7) != 0) {
        positionX = object->positionX;
        object->positionX = (positionX + ((positionX & 0x80) * 2)) & 0xFFFFFF00;
        positionY = object->positionY;
        object->positionY = (positionY + ((positionY & 0x80) * 2)) & 0xFFFFFF00;
        if ((object->flags20D & 0x40) == 0) {
            baseElevation = object->baseElevation;
            object->baseElevation =
                (baseElevation + ((baseElevation & 0x80) * 2)) & 0xFFFFFF00;
            elevationOffset = object->elevationOffset;
            object->elevationOffset =
                (elevationOffset + ((elevationOffset & 0x80) * 2)) & 0xFFFFFF00;
        }
        object->value2E0 = 0;
        object->positionDeltaX = 0;
        object->positionDeltaY = 0;
        object->flags2B5 &= mask;
    }
}

FIELD_SECTION(".text.field_scene_object.sub_80492DC")
void sub_80492DC(struct FieldSceneObject* object);

void sub_80492DC(struct FieldSceneObject* object) {
    u8 mode;
    s32 value;
    s32 flagsMask;
    s32 clearMask;

    mode = object->mode054;
    flagsMask = -8;
    clearMask = -5;
    /* Preserve the original low-register allocation for this callback byte. */
    asm("" : "+r"(mode));

    if (((mode == 0) && (object->value218 == 0x103E))
        || ((mode == 1) && (object->value218 == 0x1053))) {
        object->flags214 = (object->flags214 & flagsMask) | 3;
        if (object->mode054 == 0) {
            value = 0x1001 + ((object->flags35B & 8) != 0) * 0x27;
        } else {
            value = 0x1002;
        }
        sub_8049000(object, value);
    }
    object->flags35A &= clearMask;
}

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

void field_set_sprite_motion_scale(struct FieldSceneObject* object, u8 value)
    FIELD_SECTION(".text.sub_804790C");
void field_set_sprite_motion_scale(struct FieldSceneObject* object, u8 value) {
    object->spriteMotionScale = value;
    ((u8*)object->sprite)[0x20] = value;
}

void field_set_movement_step_magnitude(struct FieldSceneObject* object, u16 value)
    FIELD_SECTION(".text.sub_804794C");
void field_set_movement_step_magnitude(struct FieldSceneObject* object, u16 value) {
    object->movementStepMagnitude = value;
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

s32 sub_8047A1C(struct FieldSceneObject* object)
    FIELD_SECTION(".text.sub_8047A1C");
s32 field_has_flags_2b5_c0(struct FieldSceneObject* object) {
    s32 bits;
    char result;
    bits = FIELD_SCENE_FLAGS_2B5_HIGH & object->flags2B5;
    result = bits;
    /* Preserve the original register copy before boolean normalization. */
    asm("" : "+r"(result));
    if (bits != 0) {
        result = 1;
    }
    return result;
}

s32 sub_8047A3C(struct FieldSceneObject* object)
    FIELD_SECTION(".text.sub_8047A3C");
s32 field_has_flags_2b5_30(struct FieldSceneObject* object) {
    s32 bits;
    /* The addressable local retains the original condition/register layout. */
    s32* value = &bits;
    s32 result;
    bits = FIELD_SCENE_FLAGS_2B5_MIDDLE & object->flags2B5;
    result = bits;
    /* Preserve the original register copy before boolean normalization. */
    asm("" : "+r"(result));
    if (*value != 0) {
        result = 1;
    }
    return result;
}

s32 sub_8047B78(struct FieldSceneObject* object)
    FIELD_SECTION(".text.sub_8047B78");
s32 field_has_flags_2b5_07(struct FieldSceneObject* object) {
    s32 bits;
    /* The addressable local retains the original condition/register layout. */
    s32* value = &bits;
    s32 result;
    bits = FIELD_SCENE_FLAGS_2B5_LOW & object->flags2B5;
    result = bits;
    /* Preserve the original register copy before boolean normalization. */
    asm("" : "+r"(result));
    if (*value != 0) {
        result = 1;
    }
    return result;
}
