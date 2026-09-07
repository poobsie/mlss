#include "graphics/indexed_blob.h"

#define BLOB_SEC(name) \
    __attribute__((section(".text.graphics_indexed_blob." #name)))

BLOB_SEC(sub_8127ECC)
const void* graphics_get_indexed_blob(u32 index, u32* size)
{
    register u32* outputSize asm("r4") = size;
    register u32 byteOffset asm("r3") = index * 4;
    register const u8* tableBase asm("r2") = (const u8*)0x08A57994;
    register u32 entry asm("r0") = byteOffset;
    register const u8* blob asm("r1");

    entry += (u32)tableBase;
    entry = *(const u32*)entry;
    blob = (const u8*)entry + (u32)tableBase;

    if (outputSize != 0) {
        entry = (u32)(tableBase + 4);
        entry = byteOffset + entry;
        entry = *(const u32*)entry;
        entry += (u32)tableBase;
        entry -= (u32)blob;
        *outputSize = entry;
    }
    return blob;
}
