#include "graphics/functions.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(symbol) \
    __attribute__((section(".text.misc_helpers_02." STRINGIFY(symbol))))

#define GRAPHICS_RESOURCE_FCC (*(void**)0x03000FCC)

void sub_80E6FB8(void* resource, s32 layer);
void sub_80E7118(void* resource, u8 mask);

SEC(graphics_update_global_resource_fcc_layer_4_mask_16)
void graphics_update_global_resource_fcc_layer_4_mask_16(void)
{
    sub_80E6FB8(GRAPHICS_RESOURCE_FCC, 4);
    sub_80E7118(GRAPHICS_RESOURCE_FCC, 0x10);
}
