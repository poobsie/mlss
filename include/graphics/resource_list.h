#ifndef GUARD_GRAPHICS_RESOURCE_LIST_H
#define GUARD_GRAPHICS_RESOURCE_LIST_H

#include "global.h"

struct GraphicsResourceListNode {
    struct GraphicsResourceListNode* previous;
    struct GraphicsResourceListNode* next;
};

struct GraphicsResourceList {
    struct GraphicsResourceListNode* head;
    struct GraphicsResourceListNode* tail;
    s32 count;
    const void* descriptor;
};

#define graphics_resource_list_contains sub_81346D0
#define graphics_destroy_resource_list sub_81347C0

s32 graphics_resource_list_contains(
    const struct GraphicsResourceList* list,
    const struct GraphicsResourceListNode* candidate);
void graphics_destroy_resource_list(
    struct GraphicsResourceList* list, u32 flags);

#endif
