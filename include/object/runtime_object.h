#ifndef GUARD_OBJECT_RUNTIME_OBJECT_H
#define GUARD_OBJECT_RUNTIME_OBJECT_H

#include "global.h"

enum RuntimeObjectVariant {
    RUNTIME_OBJECT_VARIANT_FIRST = -1,
    RUNTIME_OBJECT_VARIANT_SECOND = -2,
};

struct RuntimeObjectValueSource {
    u8 unknown00[6];
    s8 value6;
};

struct RuntimeObjectVisual;

struct RuntimeObjectState {
    u8 unknown00[0x10];
    struct RuntimeObjectVisual* visual10;
    u8 unknown14[0x24];
    s32 value38;
    u8 unknown3C[0x68];
    s32 valueA4;
    u8 unknownA8[0x0C];
    s16 valueB4;
    u8 unknownB6[0x2A];
    s32 floorHeight;
    struct RuntimeObjectValueSource* valueSourceE4;
    u8 unknownE8[4];
    s16 variant;
    u8 unknownEE[0x23];
    s8 flags111;
    u8 unknown112;
    u8 value113;
    u32 snapshot114;
};

struct RuntimeObject;
struct ObjectPositionHistoryNode;
typedef void (*RuntimeObjectCallback)(struct RuntimeObject* object);

struct RuntimeObjectVisual {
    s16 coordinate0;
    u8 unknown02[2];
    s16 value04;
    s16 value06;
    u8 unknown08[4];
    s16 value0C;
    u8 unknown0E[3];
    u8 flags11;
    u8 flags;
    u8 unknown13[0x0D];
    u8 parameter20;
    u8 value21;
};

struct RuntimeObject {
    u8 unknown00[8];
    struct RuntimeObjectVisual* visual;
    struct ObjectPositionHistoryNode* positionHistory;
    s32 currentPositionX;
    s32 currentPositionY;
    s32 verticalPosition;
    u8 unknown1C[0x0C];
    struct RuntimeObjectState* state;
    void* positionOwner;
    struct RuntimeObject* linkedObject;
    u8 unknown34[4];
    s32 positionX;
    s32 positionY;
    s32 positionZBase;
    u8 unknown44;
    s8 boundaryOffset45;
    u8 unknown46[6];
    RuntimeObjectCallback update;
    RuntimeObjectCallback followup;
    s32 auxiliaryState;
    u8 unknown58[4];
    RuntimeObjectCallback secondaryUpdate;
    RuntimeObjectCallback tertiaryUpdate;
    u8 unknown64[4];
    RuntimeObjectCallback cleanup;
    const void* descriptor;
    u8 unknown70[4];
    s8 value74;
    u8 unknown75;
    u8 flags76;
    u8 flags77;
    u8 unknown78;
    u8 flags79;
    u8 unknown7A[6];
    s32 value80;
    s32 value84;
    u8 unknown88[4];
    s32 value8C;
    u8 unknown90[4];
    s32 verticalAcceleration;
    u32 flags98;
    s32 behaviorState;
    s32 valueA0;
    s32 valueA4;
    s32 valueA8;
    s16 timer;
    s16 secondaryTimer;
    u16 stateValueB0;
    s16 verticalVelocity;
};

void sub_8087540(struct RuntimeObject* object);
void runtime_object_finish_action(struct RuntimeObject* object);

#endif
