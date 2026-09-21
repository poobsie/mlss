#ifndef GUARD_GRAPHICS_DECOMPRESSION_H
#define GUARD_GRAPHICS_DECOMPRESSION_H

#include "global.h"

typedef void (*GraphicsDecompressCallback)(
    const void* source, void* destination);

#define GRAPHICS_DECOMPRESS_CALLBACK \
    (*(GraphicsDecompressCallback*)0x03000C84)

#define graphics_decompress_and_transfer_resource sub_8163DB8

void graphics_decompress_and_transfer_resource(
    const void* source, void* destination);

#endif
