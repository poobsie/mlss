#ifndef GUARD_GRAPHICS_SPRITE_HEAP_H
#define GUARD_GRAPHICS_SPRITE_HEAP_H

#include "global.h"

struct SpriteHeapAllocationHeader {
    u32 referenceCount;
    u32 value04;
    void* data;
    u32 value0C;
};

struct SpriteHeapOwner {
    u8 unknown00[0x48];
    struct SpriteHeapAllocationHeader* allocation;
    void* data4C;
    u32 value50;
};

#define sprite_heap_initialize_allocation_header sub_80208E0

#endif
