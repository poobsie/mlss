#ifndef GUARD_FIELD_ACTOR_H
#define GUARD_FIELD_ACTOR_H

#include "global.h"

struct FieldVisual {
    u8 unknown00[0x11];
    u8 flags11;
    u8 flags;
};

struct RuntimeObject;

struct FieldAction {
    u8 unknown00[8];
    struct FieldVisual* visual;
    u8 unknown0C[0x24];
    struct RuntimeObject* activeObject;
    u8 unknown34[0x18];
    void (*update)(void);
};

struct FieldActor {
    u8 unknown00[8];
    struct FieldAction action;
    u8 unknown58[0x26];
    u8 stateFlags;
    u8 unknown7F[2];
    u8 flags81;
    s16 soundHandle;
    u8 unknown84[2];
    s16 value86;
    u8 unknown88[0x12];
    s16 value9A;
    u8 unknown9C[0x2F];
    s8 displayOffsetX;
    s8 displayOffsetY;
};

struct FieldRuntime {
    u8 unknown00[0x0A];
    u8 flags0A;
    u8 flags0B;
    u8 unknown0C[0x34];
    /* Nonzero while this class of field-object transition is blocked. */
    u32 guard40;
    u8 unknown44[0x10];
    /* Head of RuntimeObject::listNext chain managed by the field runtime. */
    struct RuntimeObject* runtimeObjectListHead;
    u8 unknown58[0x18];
    struct FieldActor* actorA;
    struct FieldActor* actorB;
    u8 unknown78[8];
    struct FieldActor* actorC;
    struct FieldActor* actorD;
};

extern struct FieldRuntime* gFieldRuntime;

#endif
