#include "graphics/functions.h"
#include "graphics/resource.h"

void free_heap_8018DA8(void* pointer);

#define DEFINE_GRAPHICS_RESOURCE_DESTRUCTOR(name, sectionName)                 \
    void name(struct GraphicsResourceOwner* object, u32 flags)                \
        __attribute__((section(sectionName)));                                 \
    void name(struct GraphicsResourceOwner* object, u32 flags)                \
    {                                                                          \
        object->vtable = (void*)0x08CDD090;                                     \
        if (flags & 1)                                                         \
            free_heap_8018DA8(object);                                         \
    }

DEFINE_GRAPHICS_RESOURCE_DESTRUCTOR(graphics_destroy_resource_owner_a,
                                    ".text.high.sub_816154C")
DEFINE_GRAPHICS_RESOURCE_DESTRUCTOR(graphics_destroy_resource_owner_b,
                                    ".text.freeing_destructors.sub_8161580")
DEFINE_GRAPHICS_RESOURCE_DESTRUCTOR(graphics_destroy_resource_owner_c,
                                    ".text.freeing_destructors.sub_81615B4")
