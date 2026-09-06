#ifndef GUARD_RUNTIME_CALLBACK_TABLE_H
#define GUARD_RUNTIME_CALLBACK_TABLE_H

#include "global.h"

struct RuntimeCallbackTable;
typedef void (*RuntimeForwardedCallback)(
    void* argument, struct RuntimeCallbackTable* table, void* callbackSlot);
typedef void (*RuntimeFrameCallback)(void);

#define runtime_dispatch_frame_callbacks sub_8029910

struct RuntimeCallbackTable {
    u8 unknown00[0x1A0];
    RuntimeForwardedCallback callback;
};

void runtime_dispatch_frame_callbacks(void);

#endif
