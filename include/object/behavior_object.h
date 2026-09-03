#ifndef GUARD_OBJECT_BEHAVIOR_OBJECT_H
#define GUARD_OBJECT_BEHAVIOR_OBJECT_H

#include "global.h"

struct BehaviorVisualState {
    u8 unknown00[0x12];
    u8 flags;
    u8 unknown13[0x0D];
    u8 state;
};

struct BehaviorObject;
typedef void (*BehaviorObjectCallback)(struct BehaviorObject* object);

struct BehaviorObject {
    u8 unknown00[8];
    struct BehaviorVisualState* visual;
    u8 unknown0C[0x40];
    BehaviorObjectCallback update;
    u8 unknown50[0x4C];
    s32 countdown;
};

#endif
