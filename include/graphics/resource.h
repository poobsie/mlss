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

struct GraphicsSourceEntry {
    u8 unknown00[8];
    void* source;
};

struct GraphicsSourceSet {
    struct GraphicsSourceEntry* first;
    u8 unknown04[8];
    struct GraphicsSourceEntry* second;
};

struct GraphicsUploadOwner {
    u8 unknown00[0x1C];
    struct GraphicsSourceSet* sources;
};

struct GraphicsTileBufferOwner {
    void* firstSprite;
    void* secondSprite;
    u8 unknown08[0x18];
    void* tileBuffer20;
    u8 unknown24[0x14];
    void* transfer38;
};

struct GraphicsPaletteOwner {
    void* resource00;
    void* source04;
    void* optionalResource08;
    u8 unknown0C[4];
    void* destination10;
    u8 unknown14[8];
    void* resource1C;
    u8 unknown20[4];
    u32 value24;
    u32 value28;
    u16* output2C;
    u16* output30;
};

#endif
