#ifndef GUARD_FIELD_ACTOR_H
#define GUARD_FIELD_ACTOR_H

#include "global.h"

struct FieldVisual {
    u8 unknown00[0x12];
    u8 flags;
};

struct FieldAction {
    u8 unknown00[8];
    struct FieldVisual* visual;
    u8 unknown0C[0x40];
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
};

struct FieldRuntime {
    u8 unknown00[0x70];
    struct FieldActor* actorA;
    struct FieldActor* actorB;
    u8 unknown78[8];
    struct FieldActor* actorC;
    struct FieldActor* actorD;
};

extern struct FieldRuntime* gFieldRuntime;

#endif
