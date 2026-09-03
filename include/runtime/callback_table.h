#ifndef GUARD_RUNTIME_CALLBACK_TABLE_H
#define GUARD_RUNTIME_CALLBACK_TABLE_H

#include "global.h"

struct RuntimeCallbackTable;
typedef void (*RuntimeForwardedCallback)(
    void* argument, struct RuntimeCallbackTable* table, void* callbackSlot);

struct RuntimeCallbackTable {
    u8 unknown00[0x1A0];
    RuntimeForwardedCallback callback;
};

#endif
