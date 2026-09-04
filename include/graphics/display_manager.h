#ifndef GUARD_GRAPHICS_DISPLAY_MANAGER_H
#define GUARD_GRAPHICS_DISPLAY_MANAGER_H

#include "global.h"

struct GraphicsDisplayLayer {
    void* buffer;
    u8 unknown04[0x10];
};

struct GraphicsDisplayManager {
    u8 unknown00[0x0C];
    struct GraphicsDisplayLayer layers[1];
};

#define graphics_display_manager_get_layer_buffer sub_8084E84

void* graphics_display_manager_get_layer_buffer(struct GraphicsDisplayManager* manager, u8 index);

#endif
