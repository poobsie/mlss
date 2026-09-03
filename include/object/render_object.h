#ifndef GUARD_OBJECT_RENDER_OBJECT_H
#define GUARD_OBJECT_RENDER_OBJECT_H

#include "global.h"

struct RenderObject {
    u8 unknown00[0x24];
    u8 active;
    u8 unknown25[0x0B];
    const void* descriptor;
    u16 value;
};

struct DescriptorObject {
    u8 unknown00[0x0C];
    const void* descriptor;
};

#endif
