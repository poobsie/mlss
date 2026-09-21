#ifndef GUARD_FIELD_SCENE_OBJECT_H
#define GUARD_FIELD_SCENE_OBJECT_H

#include "common.h"

struct FieldSceneObject;
/* Flag groups are observed; their gameplay meanings are not yet established. */
#define FIELD_SCENE_FLAGS_2B5_HIGH 0xC0
#define FIELD_SCENE_FLAGS_2B5_MIDDLE 0x30
#define FIELD_SCENE_FLAGS_2B5_LOW 0x07
#define FIELD_SCENE_FLAGS_2B5_08 (1 << 3)
typedef void (*FieldSceneDispatch)(u32, struct FieldSceneObject*);
typedef void (*FieldSceneChainCallback)(
    u32, struct FieldSceneObject*, void* callbackSlot);

#define field_install_and_run_scene_dispatch_81395ac sub_8139970
void field_install_and_run_scene_dispatch_81395ac(
    u32 context, struct FieldSceneObject* object);
#define field_scene_update_vertical_deceleration sub_8139200
void field_scene_update_vertical_deceleration(struct FieldSceneObject* object);
#define field_scene_countdown_linked_selection_then_restore_callback sub_813915C
void field_scene_countdown_linked_selection_then_restore_callback(
    u32 context, struct FieldSceneObject* object,
    FieldSceneChainCallback* callbackSlot);
#define field_scene_load_scaled_bounds sub_8139030
void field_scene_load_scaled_bounds(
    struct FieldSceneObject* object, s32 halfwordOffset);
#define field_scene_copy_four_selection_values sub_8139070
void field_scene_copy_four_selection_values(
    struct FieldSceneObject* object, s32 halfwordOffset);

struct FieldCallbackSlots {
    FieldSceneChainCallback slots[4];
};

struct FieldSceneLayoutRegion {
    u8 unknown100[0x28];
    u16 selectionValues[4];
    u8 unknown130[8];
    s16 boundsYStart;
    s16 boundsYEnd;
    s16 boundsXStart;
    s16 boundsXEnd;
};

struct FieldSceneObject {
    u8 unknown000[0x0C];
    s32 positionX;
    s32 positionY;
    /* Four fixed-point words are quantized together by sub_8046980. */
    s32 baseElevation;
    s32 elevationOffset;
    u8 unknown01C[0x38];
    u8 mode054;
    u8 unknown055[0xAB];
    struct FieldSceneLayoutRegion layout100;
    u8 unknown140[0x58];
    FieldSceneDispatch dispatch198;
    FieldSceneDispatch dispatch19C;
    FieldSceneChainCallback callback1A0;
    FieldSceneChainCallback callback1A4;
    u8 unknown1A8[4];
    FieldSceneChainCallback callback1AC;
    const u8* selectionTable;
    const s16* boundsTable1B4;
    u8 unknown1B8[0x18];
    u16 selectionIndex;
    u16 selectedValue;
    u16 selectionResetValue;
    u8 callbackStateFlags;
    u8 unknown1D7[0x35];
    u8 flags20C;
    u8 flags20D;
    u8 unknown20E;
    u8 flags20F;
    u8 unknown210[4];
    u8 flags214;
    u8 unknown215[2];
    u8 flags217;
    u16 value218;
    u8 unknown21A[0x1F];
    u8 spriteMotionScale;
    u8 unknown23A;
    u8 state23B;
    u8 unknown23C;
    u8 state23D;
    u16 movementStepMagnitude;
    u8 unknown240[2];
    s16 positionDeltaX;
    s16 positionDeltaY;
    u8 unknown246[2];
    s32 motionAcceleration248;
    s32 motionLimit24C;
    u8 unknown250[8];
    s32 motionVelocity258;
    s32 motionState25C;
    u8 unknown260[6];
    u16 value266;
    u16 previousValue268;
    u8 unknown26A[4];
    u8 selectedEntryIndex;
    u8 unknown26F[7];
    u16 verticalExtent276;
    u8 unknown278[0x19];
    u8 flags291;
    u8 unknown292[2];
    struct Sprite* sprite;
    u8 unknown298[0x1D];
    u8 flags2B5;
    u8 flags2B6;
    u8 unknown2B7[0x23];
    s16 savedPositionDeltaX;
    s16 savedPositionDeltaY;
    u16 motionStepCount;
    s16 value2E0;
    u8 unknown2E2[0x12];
    s32 motionPhase;
    s16 motionPhaseStep;
    u8 unknown2FA[0x3A];
    void* entryStateTable;
    const void* descriptor;
    u16 unknown33C;
    u16 flags33E;
    s16 value340;
    u8 unknown342[2];
    struct FieldSceneObject* linkedSceneObject344;
    s32 movementStartX;
    s32 movementStartY;
    u8 unknown350[0x0A];
    u8 flags35A;
    u8 flags35B;
};

#endif
