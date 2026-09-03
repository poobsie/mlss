#ifndef GUARD_FIELD_SCENE_OBJECT_H
#define GUARD_FIELD_SCENE_OBJECT_H

#include "common.h"

struct FieldSceneObject;
typedef void (*FieldSceneDispatch)(u32, struct FieldSceneObject*);
typedef void (*FieldSceneChainCallback)(
    u32, struct FieldSceneObject*, void* callbackSlot);

struct FieldCallbackSlots {
    FieldSceneChainCallback slots[4];
};

struct FieldSceneObject {
    u8 unknown000[0x0C];
    s32 positionX;
    s32 positionY;
    u8 unknown014[0x184];
    FieldSceneDispatch dispatch198;
    u8 unknown19C[4];
    FieldSceneChainCallback callback1A0;
    FieldSceneChainCallback callback1A4;
    u8 unknown1A8[4];
    FieldSceneChainCallback callback1AC;
    u8 unknown1B0[0x5C];
    u8 flags20C;
    u8 flags20D;
    u8 unknown20E;
    u8 flags20F;
    u8 unknown210[4];
    u8 flags214;
    u8 unknown215[2];
    u8 flags217;
    u8 unknown218[0x21];
    u8 value239;
    u8 unknown23A;
    u8 state23B;
    u8 unknown23C;
    u8 state23D;
    u16 value23E;
    u8 unknown240[2];
    s16 positionDeltaX;
    s16 positionDeltaY;
    u8 unknown246[0x20];
    u16 value266;
    u16 previousValue268;
    u8 unknown26A[4];
    u8 selectedEntryIndex;
    u8 unknown26F[0x22];
    u8 flags291;
    u8 unknown292[2];
    struct Sprite* sprite;
    u8 unknown298[0x1D];
    u8 flags2B5;
    u8 flags2B6;
    u8 unknown2B7[0x7D];
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
};

#endif
