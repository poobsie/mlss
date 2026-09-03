#ifndef GUARD_FIELD_EVENT_CALLBACKS_H
#define GUARD_FIELD_EVENT_CALLBACKS_H

#include "global.h"

typedef void (*FieldEventCallback)(void);

struct FieldEventContext {
    u8 unknown000[0x198];
    FieldEventCallback update;
    u8 unknown19C[4];
    FieldEventCallback continuation;
    u8 unknown1A4[0x0C];
    u8* selectionTable;
    u8 unknown1B4[0x1C];
    u16 selectionIndex;
    u16 selectedValue;
    u16 resetValue;
    u8 unknown1D6[0x168];
    u8 flags33E;
};

#endif
