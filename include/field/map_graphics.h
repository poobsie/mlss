#ifndef GUARD_FIELD_MAP_GRAPHICS_H
#define GUARD_FIELD_MAP_GRAPHICS_H

#include "process/process.h"

struct FieldMapGraphicsProcess {
    struct Process process;
    s16 loadState;
    u16 definitionIndex;
    s16 deltaX;
    s16 deltaY;
    u16 baseX;
    u16 baseY;
    u16 scaleX;
    u16 scaleY;
    u8 unknown2C[0x0C];
    u16* expandedTilemaps;
    u16* cellIndices;
    void* graphicsWorkspace;
    u16* metatileDefinitions;
};

#define field_map_graphics_destroy sub_805A99C

void field_map_graphics_destroy(
    struct FieldMapGraphicsProcess* process, u32 flags);

#endif
