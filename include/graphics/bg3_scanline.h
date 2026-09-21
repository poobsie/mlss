#ifndef GUARD_GRAPHICS_BG3_SCANLINE_H
#define GUARD_GRAPHICS_BG3_SCANLINE_H

#include "global.h"

struct GraphicsBg3ScanlineTransfer {
    u16 initialBg3X;
    u16 initialBg3Y;
    u32 scanlineCoordinates[1];
};

#define GRAPHICS_BG3_SCANLINE_TRANSFER \
    (*(struct GraphicsBg3ScanlineTransfer**)0x03001030)

#define graphics_start_bg3_scanline_dma sub_816B384

void graphics_start_bg3_scanline_dma(void);

#endif
