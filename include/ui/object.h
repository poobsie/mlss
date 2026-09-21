#ifndef GUARD_UI_OBJECT_H
#define GUARD_UI_OBJECT_H

#include "global.h"

typedef void (*UiObjectAdjustedDestructor)(void* adjustedThis, u32 flags);

struct UiObjectVtable {
    u8 unknown00[8];
    s16 destructorThisAdjustment;
    u16 unknown0A;
    UiObjectAdjustedDestructor destructor;
};

struct UiObject {
    u8 unknown00[0x0C];
    const struct UiObjectVtable* vtable;
    u8 unknown10[8];
    s32 positionX;
    s32 positionYOffset;
    s32 positionY;
    u8 unknown24[0x1C];
    u32 visualState;
    const void* visualDefinition;
    u16 visualStepIndex;
    u8 unknown4A[8];
    u16 directionIndex;
};

struct UiObjectGroup4 {
    struct UiObject* objects[4];
};

struct UiObjectGrid {
    u32 unknown00;
    struct UiObject* objects[6];
};

struct UiObjectPairValues {
    u8 unknown00[0x52];
    u16 value52;
    u16 copiedValue54;
    u16 value56;
    u16 copiedValue58;
};

struct UiSpritePair {
    u8 unknown00[0x0C];
    const void* vtable;
    struct Sprite* firstSprite;
    struct Sprite* secondSprite;
};

#endif
