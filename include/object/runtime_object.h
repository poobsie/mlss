#ifndef GUARD_OBJECT_RUNTIME_OBJECT_H
#define GUARD_OBJECT_RUNTIME_OBJECT_H

#include "global.h"

enum RuntimeObjectVariant {
    RUNTIME_OBJECT_VARIANT_FIRST = -1,
    RUNTIME_OBJECT_VARIANT_SECOND = -2,
};

struct RuntimeObjectState {
    u8 unknown00[0xE0];
    s32 floorHeight;
    u8 unknownE4[8];
    s16 variant;
    u8 unknownEE[0x23];
    s8 flags111;
    u8 unknown112[2];
    u32 snapshot114;
};

struct RuntimeObject;
typedef void (*RuntimeObjectCallback)(struct RuntimeObject* object);

struct RuntimeObjectVisual {
    u8 unknown00[0x12];
    u8 flags;
    u8 unknown13[0x0D];
    u8 parameter20;
};

struct RuntimeObject {
    u8 unknown00[8];
    struct RuntimeObjectVisual* visual;
    u8 unknown0C[0x0C];
    s32 verticalPosition;
    u8 unknown1C[0x0C];
    struct RuntimeObjectState* state;
    u8 unknown2C[0x14];
    s32 verticalBase;
    u8 unknown44[8];
    RuntimeObjectCallback update;
    u8 unknown50[0x18];
    RuntimeObjectCallback cleanup;
    const void* descriptor;
    u8 unknown70[6];
    u8 flags76;
    u8 flags77;
    u8 unknown78[0x1C];
    s32 verticalAcceleration;
    u8 unknown98[4];
    s32 behaviorState;
    u8 unknownA0[0x0C];
    s16 timer;
    u8 unknownAE[4];
    s16 verticalVelocity;
};

void sub_8087540(struct RuntimeObject* object);
void runtime_object_finish_action(struct RuntimeObject* object);

#endif
