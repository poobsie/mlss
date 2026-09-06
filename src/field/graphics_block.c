#include "field/graphics_block.h"
#include "common.h"
#include "gba/syscall.h"
#include "memory/heap.h"

#define SEC(symbol) __attribute__((section(".text.field_graphics_block." #symbol)))

struct FieldGraphicsStateOverlay {
    u8 unknown00[0x8C0];
    u8 resourceIndex8C0;
};

#define GRAPHICS_DECOMPRESS_CALLBACK \
    (*(void (**)(const void*, void*))0x03000C84)

extern struct FieldGraphicsStateOverlay gFieldGraphicsState __asm__("gGameState");

void* sub_8127ECC(u32 index, u32* size);

SEC(sub_8127E50)
s32 field_transfer_graphics_resource(
    const void* source, void* destination, bool32 keepAllocated)
{
    s32 size = sub_80198B0((int*)source);

    if (keepAllocated != FALSE) {
        destination = heap_alloc_block(
            TRUE, size, (const char*)0x08210F64);
        GRAPHICS_DECOMPRESS_CALLBACK(source, destination);
    } else {
        void* temporary = heap_alloc_block(
            TRUE, size, (const char*)0x08210F64);
        s32 copySize;

        GRAPHICS_DECOMPRESS_CALLBACK(source, temporary);
        copySize = size;
        if (size < 0)
            copySize = size + 3;
        CpuSet(
            temporary, destination,
            0x04000000 | ((u32)(copySize << 9) >> 11));
        heap_free_block(temporary);
    }
    return size;
}

SEC(sub_81229F0)
void field_load_indexed_graphics_block(struct FieldGraphicsWorkspace* workspace)
{
    void* resource = sub_8127ECC(gFieldGraphicsState.resourceIndex8C0 + 7, NULL);

    field_transfer_graphics_resource(
        resource, workspace->graphicsData840, FALSE);
}
