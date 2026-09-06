#include "graphics/resource_list.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(name) __attribute__((section(".text.upper." STRINGIFY(name))))

void free_heap_8018DA8(void* allocation);
void sub_81346EC(struct GraphicsResourceList* list);

SEC(graphics_resource_list_contains)
s32 graphics_resource_list_contains(
    const struct GraphicsResourceList* list,
    const struct GraphicsResourceListNode* candidate)
{
    const struct GraphicsResourceListNode* node = list->head;

    while (node != 0) {
        if (node == candidate)
            return 1;
        node = node->next;
    }
    return 0;
}

SEC(graphics_destroy_resource_list)
void graphics_destroy_resource_list(
    struct GraphicsResourceList* list, u32 flags)
{
    list->descriptor = (const void*)0x08CDC438;
    sub_81346EC(list);
    if (flags & 1)
        free_heap_8018DA8(list);
}
