#ifndef GUARD_FIELD_LINKED_OBJECT_H
#define GUARD_FIELD_LINKED_OBJECT_H

#include "global.h"

struct FieldLinkedObject {
    u8 unknown000[4];
    u16 state;
    u8 unknown006[0x33E];
    s8 marker344;
};

struct FieldLinkedObjectOwner {
    u8 unknown000[0x200];
    struct FieldLinkedObject* primary;
    struct FieldLinkedObject* secondary;
};

#endif
