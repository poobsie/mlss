#include "graphics/functions.h"
#include "graphics/resource.h"
#include "memory/heap.h"

void sub_8018218(void* source, void* destination, u32 size, u32 width, u32 mode);
int sub_80198B0(int* source);

typedef void (*GraphicsDecompressCallback)(const void* source,
                                           void* destination);

#define GRAPHICS_DECOMPRESS_CALLBACK \
    (*(GraphicsDecompressCallback*)0x03000C84)

void graphics_upload_fixed_tile_regions(struct GraphicsUploadOwner* object)
    __attribute__((section(".text.early_code_helpers_3.sub_8029460")));
void graphics_upload_fixed_tile_regions(struct GraphicsUploadOwner* object) {
    sub_8018218(object->sources->first->source, (void*)0x06010400, 0x4C0,
                0x20, 0);
    sub_8018218(object->sources->second->source, (void*)0x060108C0, 0x500,
                0x20, 0);
}

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

void graphics_decompress_and_transfer_resource(
    const void* source, void* destination)
    __attribute__((section(".text.sub_8163DB8")));
void graphics_decompress_and_transfer_resource(
    const void* source, void* destination)
{
    s32 size = sub_80198B0((int*)source);
    void* temporary = heap_alloc_block(
        TRUE, size, (const char*)0x0821280C);

    GRAPHICS_DECOMPRESS_CALLBACK(source, temporary);
    sub_8018218(temporary, destination, size, 0x10, 2);
    heap_free_block(temporary);
}
