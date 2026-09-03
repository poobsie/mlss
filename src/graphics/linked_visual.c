#include "graphics/linked_visual.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(symbol) \
    __attribute__((section(".text.misc_helpers_02." STRINGIFY(symbol))))

void sub_807BDDC(struct GraphicsLinkedVisual* visual);
void sub_80842D8(struct GraphicsLinkedVisual* visual);

SEC(graphics_deactivate_linked_visual)
void graphics_deactivate_linked_visual(struct GraphicsLinkedVisual* visual)
{
    sub_807BDDC(visual);
    sub_80842D8(visual);
}
