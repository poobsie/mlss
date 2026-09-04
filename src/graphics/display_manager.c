#include "graphics/display_manager.h"

#define SEC(symbol) __attribute__((section(".text.graphics_display_manager." #symbol)))

SEC(sub_8084E84)
void* graphics_display_manager_get_layer_buffer(struct GraphicsDisplayManager* manager, u8 index)
{
    return manager->layers[index].buffer;
}
SEC(sub_8084E84)
const u16 graphics_display_manager_get_layer_buffer_padding = 0;
