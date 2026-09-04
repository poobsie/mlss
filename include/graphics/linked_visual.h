#ifndef GUARD_GRAPHICS_LINKED_VISUAL_H
#define GUARD_GRAPHICS_LINKED_VISUAL_H

struct GraphicsLinkedVisual {
    unsigned char unknown00[0x13];
    unsigned char flags13;
};

#define graphics_deactivate_linked_visual sub_807FB64
#define graphics_destroy_linked_visual sub_807FB34

void graphics_deactivate_linked_visual(struct GraphicsLinkedVisual* visual);
void graphics_destroy_linked_visual(struct GraphicsLinkedVisual* visual);

#endif
