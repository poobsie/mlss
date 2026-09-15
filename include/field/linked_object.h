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
    u8 unknown208[2];
    u16 flags20A;
};

#define field_linked_object_check_state_2a_2b sub_803C468

u8 field_linked_object_check_state_2a_2b(
    struct FieldLinkedObjectOwner* owner);

#endif
