#ifndef GUARD_GRAPHICS_PROCESS_STATE_H
#define GUARD_GRAPHICS_PROCESS_STATE_H

#include "global.h"

struct GraphicsStagingSource {
    u8 unknown00[0x5A];
    u16 maskedValue0;
    u16 maskedValue1;
    u16 maskedValue2;
    u8 component0;
    u8 unknown61;
    u8 component1;
    u8 unknown63;
    u8 component2;
};

struct GraphicsStagingValues {
    s16 maskedValue0;
    s16 component0;
    s16 maskedValue1;
    s16 component1;
    s16 maskedValue2;
    s16 component2;
};

struct GraphicsProcessState {
    u8 unknown00[0x18];
    const void* descriptor;
    u8 active;
    u8 unknown1D[0x77];
    void* buffer94;
    void* buffer98;
    u8 unknown9C[8];
    void* bufferA4;
    void* bufferA8;
};

void graphics_copy_staging_values(struct GraphicsStagingSource* source);
void graphics_destroy_transfer_process(struct GraphicsProcessState* process, s32 flags);
void graphics_destroy_vram_process(struct GraphicsProcessState* process, s32 flags);

#endif
