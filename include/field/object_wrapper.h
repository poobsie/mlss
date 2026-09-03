#ifndef GUARD_FIELD_OBJECT_WRAPPER_H
#define GUARD_FIELD_OBJECT_WRAPPER_H

#include "global.h"

struct FieldObjectCallbackEntry {
    s16 receiverOffset;
    u16 reserved;
    int (*function)();
};

struct FieldObjectCallbackTable {
    u8 unknown00[0x10];
    struct FieldObjectCallbackEntry slot10;
    struct FieldObjectCallbackEntry slot18;
    struct FieldObjectCallbackEntry slot20;
    struct FieldObjectCallbackEntry slot28;
    struct FieldObjectCallbackEntry slot30;
    u8 unknown38[8];
    struct FieldObjectCallbackEntry slot40;
    struct FieldObjectCallbackEntry slot48;
    struct FieldObjectCallbackEntry slot50;
    struct FieldObjectCallbackEntry slot58;
    struct FieldObjectCallbackEntry slot60;
    struct FieldObjectCallbackEntry slot68;
    struct FieldObjectCallbackEntry slot70;
    u8 unknown78[0x10];
    struct FieldObjectCallbackEntry slot88;
};

struct FieldObjectWrapper {
    u8 unknown000[0x20C];
    u8 flags20C;
    u8 unknown20D[0x12B];
    struct FieldObjectCallbackTable* callbacks;
    u8 unknown33C[8];
    struct FieldObjectWrapper* child;
};

#endif
