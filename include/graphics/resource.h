#ifndef GUARD_GRAPHICS_RESOURCE_H
#define GUARD_GRAPHICS_RESOURCE_H

#include "global.h"

struct GraphicsTransfer {
    u8 data[0x810];
    void* destination;
};

struct GraphicsResourceOwner {
    struct GraphicsTransfer* transfer;
    const void* vtable;
};

struct GraphicsRuntime {
    u8 unknown00[0x2C];
    struct GraphicsTransfer* firstTransfer;
    struct GraphicsTransfer* secondTransfer;
};

#endif
