#include "graphics/functions.h"
#include "graphics/resource.h"

void graphics_transfer_copy_2048_bytes(struct GraphicsTransfer* transfer)
    __attribute__((section(".text.high.sub_8160E4C")));
void graphics_transfer_copy_2048_bytes(struct GraphicsTransfer* transfer) {
    vu32* dma = (vu32*)0x040000D4;
    dma[0] = (u32)transfer;
    dma[1] = (u32)transfer->destination;
    dma[2] = 0x84000200;
    (void)dma[2];
}

void graphics_copy_runtime_transfer_pair(void)
    __attribute__((section(".text.upper.sub_81615E4")));
void graphics_copy_runtime_transfer_pair(void) {
    graphics_transfer_copy_2048_bytes(
        (*(struct GraphicsRuntime**)0x03001024)->firstTransfer);
    graphics_transfer_copy_2048_bytes(
        (*(struct GraphicsRuntime**)0x03001024)->secondTransfer);
}
