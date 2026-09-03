#ifndef GUARD_FIELD_SCENE_OBJECT_H
#define GUARD_FIELD_SCENE_OBJECT_H

#include "common.h"

struct FieldSceneObject {
    u8 unknown000[0x20C];
    u8 flags20C;
    u8 flags20D;
    u8 unknown20E;
    u8 flags20F;
    u8 unknown210[7];
    u8 flags217;
    u8 unknown218[0x21];
    u8 value239;
    u8 unknown23A;
    u8 state23B;
    u8 unknown23C;
    u8 state23D;
    u16 value23E;
    u8 unknown240[0x26];
    u16 value266;
    u16 previousValue268;
    u8 unknown26A[4];
    u8 selectedEntryIndex;
    u8 unknown26F[0x25];
    struct Sprite* sprite;
    u8 unknown298[0x1D];
    u8 flags2B5;
    u8 flags2B6;
    u8 unknown2B7[0x7D];
    void* entryStateTable;
    u8 unknown338[6];
    u16 flags33E;
    s16 value340;
};

#endif
