#ifndef GUARD_OBJECT_RUNTIME_OBJECT_H
#define GUARD_OBJECT_RUNTIME_OBJECT_H

#include "global.h"

enum RuntimeObjectVariant {
    RUNTIME_OBJECT_VARIANT_FIRST = -1,
    RUNTIME_OBJECT_VARIANT_SECOND = -2,
};

struct RuntimeObjectState {
    u8 unknown00[0xEC];
    s16 variant;
};

struct RuntimeObject;
typedef void (*RuntimeObjectCallback)(struct RuntimeObject* object);

struct RuntimeObject {
    u8 unknown00[0x28];
    struct RuntimeObjectState* state;
    u8 unknown2C[0x3C];
    RuntimeObjectCallback cleanup;
};

void sub_8087540(struct RuntimeObject* object);

#endif
