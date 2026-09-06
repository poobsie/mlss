#ifndef GUARD_FIELD_GRAPHICS_BLOCK_H
#define GUARD_FIELD_GRAPHICS_BLOCK_H

#include "global.h"

struct FieldGraphicsWorkspace {
    u8 unknown00[0x840];
    u8 graphicsData840[1];
};

#define field_load_indexed_graphics_block sub_81229F0
#define field_transfer_graphics_resource sub_8127E50
int field_transfer_graphics_resource(
    const void* source, void* destination, bool32 keepAllocated);
void field_load_indexed_graphics_block(struct FieldGraphicsWorkspace* workspace);

#endif
