#ifndef GUARD_FIELD_SCENE_OBJECT_H
#define GUARD_FIELD_SCENE_OBJECT_H

#include "common.h"

struct FieldSceneObject;
/* Flag groups are observed; their gameplay meanings are not yet established. */
#define FIELD_SCENE_FLAGS_2B5_HIGH 0xC0
#define FIELD_SCENE_FLAGS_2B5_MIDDLE 0x30
#define FIELD_SCENE_FLAGS_2B5_LOW 0x07
typedef void (*FieldSceneDispatch)(u32, struct FieldSceneObject*);
typedef void (*FieldSceneChainCallback)(
    u32, struct FieldSceneObject*, void* callbackSlot);

#define field_install_and_run_scene_dispatch_81395ac sub_8139970
void field_install_and_run_scene_dispatch_81395ac(
    u32 context, struct FieldSceneObject* object);

struct FieldCallbackSlots {
    FieldSceneChainCallback slots[4];
};

struct FieldSceneObject {
    u8 unknown000[0x0C];
    s32 positionX;
    s32 positionY;
    /* Four fixed-point words are quantized together by sub_8046980. */
    s32 position14;
    s32 position18;
    u8 unknown01C[0x38];
    u8 mode054;
    u8 unknown055[0x143];
    FieldSceneDispatch dispatch198;
    FieldSceneDispatch dispatch19C;
    FieldSceneChainCallback callback1A0;
    FieldSceneChainCallback callback1A4;
    u8 unknown1A8[4];
    FieldSceneChainCallback callback1AC;
    const u8* selectionTable;
    u8 unknown1B4[0x1C];
    u16 selectionIndex;
    u16 selectedValue;
    u8 unknown1D4[0x38];
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
    u8 value239;
    u8 unknown23A;
    u8 state23B;
    u8 unknown23C;
    u8 state23D;
    u16 value23E;
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
    u8 unknown2B7[0x29];
    s16 value2E0;
    u8 unknown2E2[0x52];
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
