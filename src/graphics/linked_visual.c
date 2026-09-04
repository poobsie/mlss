#include "graphics/linked_visual.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(symbol) \
    __attribute__((section(".text.misc_helpers_02." STRINGIFY(symbol))))

void sub_807BDDC(struct GraphicsLinkedVisual* visual);
void sub_80842D8(struct GraphicsLinkedVisual* visual);
void sub_8084294(struct GraphicsLinkedVisual* visual);
void sub_8021308(struct GraphicsLinkedVisual* visual);

SEC(graphics_destroy_linked_visual)
void graphics_destroy_linked_visual(struct GraphicsLinkedVisual* visual)
{
    register unsigned int value asm("r0");
    register unsigned int flags asm("r1");

    if (visual != 0) {
        sub_807BDDC(visual);
        value = visual->flags13;
        flags = -5;
        flags &= value;
        value = -9;
        flags &= value;
        visual->flags13 = flags;
        sub_8084294(visual);
        sub_8021308(visual);
    }
}
SEC(graphics_destroy_linked_visual)
const unsigned short graphics_destroy_linked_visual_padding = 0;

SEC(graphics_deactivate_linked_visual)
void graphics_deactivate_linked_visual(struct GraphicsLinkedVisual* visual)
{
    sub_807BDDC(visual);
    sub_80842D8(visual);
}
