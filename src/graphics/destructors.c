#include "graphics/functions.h"
#include "graphics/resource.h"

void free_heap_8018DA8(void* pointer);
void heap_free_block(void* pointer);

void graphics_destroy_palette_owner(struct GraphicsPaletteOwner* object,
                                    u32 flags)
    __attribute__((section(".text.sub_8165454")));
void graphics_destroy_palette_owner(struct GraphicsPaletteOwner* object,
                                    u32 flags) {
    heap_free_block(object->resource1C);
    if (object->optionalResource08 != 0)
        heap_free_block(object->optionalResource08);
    heap_free_block(object->resource00);
    if (flags & 1)
        free_heap_8018DA8(object);
}

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
