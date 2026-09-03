#include "graphics/sprite_heap.h"

void sprite_heap_initialize_allocation_header(struct SpriteHeapOwner* object)
    __attribute__((section(".text.sub_80208E0")));
void sprite_heap_initialize_allocation_header(struct SpriteHeapOwner* object) {
    struct SpriteHeapAllocationHeader* allocation = object->allocation;
    allocation->referenceCount = 1;
    allocation->value04 = object->value50;
    allocation->data = object->data4C;
    allocation->value0C = 0;
}
