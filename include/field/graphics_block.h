#ifndef GUARD_FIELD_GRAPHICS_BLOCK_H
#define GUARD_FIELD_GRAPHICS_BLOCK_H

#include "global.h"

struct FieldGraphicsWorkspace {
    u8 unknown00[0x840];
    u8 graphicsData840[1];
};

#define field_load_indexed_graphics_block sub_81229F0
void field_load_indexed_graphics_block(struct FieldGraphicsWorkspace* workspace);

#endif
