#ifndef GUARD_FIELD_SCENE_OBJECT_H
#define GUARD_FIELD_SCENE_OBJECT_H

#include "common.h"

struct FieldSceneObject {
    u8 unknown000[0x20F];
    u8 flags20F;
    u8 unknown210[0x2B];
    u8 state23B;
    u8 unknown23C;
    u8 state23D;
    u8 unknown23E[0x56];
    struct Sprite* sprite;
    u8 unknown298[0xA6];
    u16 flags33E;
    s16 value340;
};

#endif
