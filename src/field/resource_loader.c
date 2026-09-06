#include "field/resource_loader.h"
#include "field/metadata.h"
#include "memory/heap.h"

void sub_80E5968(void* resource, s32 flags);
void sub_80F94A8(void);
void sub_80FADD4(struct FieldResourceLoaderProcess* loader);
void* sub_80214A4(s32 owner, u16 resourceId, s32 slot, s32 retain);
void* sub_80213A0(s32 owner, u16 resourceId, s32 slot, s32 retain);
void sub_80507E0(void* resourceObject);

#define SEC(group, symbol) __attribute__((section(".text." group "." #symbol)))
#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define MISC2_SEC(symbol) \
    __attribute__((section(".text.misc_helpers_02." STRINGIFY(symbol))))
#define EARLY_RESOURCE_SEC(symbol) \
    __attribute__((section(".text.field_object_resource_handles." #symbol)))

#define FIELD_RESOURCE_RUNTIME (*(struct FieldResourceRuntime**)0x03000FC0)
#define FIELD_RESOURCE_MEMORY_FILL \
    (*(void (**)(u32, void*, u32))0x03001034)
#define FIELD_RESOURCE_LOADER_DEFINITION \
    ((struct ProcessDefinition*)0x08CDC328)
#define FIELD_RESOURCE_LOADER_WORKSPACE_LABEL ((char*)0x082001E0)

#define FIELD_RESOURCE_DEFAULT_55C (*(void**)0x083B9704)
#define FIELD_RESOURCE_DEFAULT_560 (*(void**)0x083B98C4)
#define FIELD_RESOURCE_DEFAULT_564 (*(void**)0x083B9D00)
#define FIELD_RESOURCE_DEFAULT_568 (*(void**)0x083BA13C)
#define FIELD_RESOURCE_DEFAULT_56C (*(void**)0x083BA4A8)

struct FieldResourceDefaultDescriptor {
    u8 unknown00[8];
    void* resource;
};

struct FieldResourceGlobalState {
    u8 unknown000[0x888];
    s8 flags888;
};

extern struct FieldResourceGlobalState gFieldResourceGlobalState
    __asm__("gGameState");

#define FIELD_RESOURCE_DESCRIPTOR_55C \
    ((struct FieldResourceDefaultDescriptor*)0x083B9704)
#define FIELD_RESOURCE_DESCRIPTOR_560 \
    ((struct FieldResourceDefaultDescriptor*)0x083B98C4)
#define FIELD_RESOURCE_DESCRIPTOR_564 \
    ((struct FieldResourceDefaultDescriptor*)0x083B9D00)
#define FIELD_RESOURCE_DESCRIPTOR_568 \
    ((struct FieldResourceDefaultDescriptor*)0x083BA13C)
#define FIELD_RESOURCE_DESCRIPTOR_56C \
    ((struct FieldResourceDefaultDescriptor*)0x083BA4A8)

MISC2_SEC(field_owned_resource_destroy)
void field_owned_resource_destroy(struct FieldOwnedResource* resource, u32 flags)
{
    heap_free_block(resource->allocation);
    if (flags & 1)
        free_heap_8018DA8(resource);
}

MISC2_SEC(field_resource_block_list_destroy)
void field_resource_block_list_destroy(struct FieldResourceBlockList* list,
                                       u32 flags)
{
    if (list->blocks != 0) {
        heap_free_block(list->blocks);
        list->blocks = 0;
    }
    if (flags & 1)
        free_heap_8018DA8(list);
}

SEC("misc_helpers_03", sub_80FAEFC)
void field_resource_loader_shutdown(struct FieldResourceLoaderProcess* loader)
{
    sub_80F94A8();
    sub_80FADD4(loader);
    FIELD_RESOURCE_RUNTIME->flags100 &= ~1;
}

SEC("small_functions_12", sub_80FAFD8)
void field_resource_loader_destroy(struct FieldResourceLoaderProcess* loader,
                                   u32 flags)
{
    loader->process.definition = (struct ProcessDefinition*)0x08CDC328;
    field_resource_loader_shutdown(loader);
    if (loader->firstResource != 0) {
        field_owned_resource_destroy(loader->firstResource, 3);
        loader->firstResource = 0;
    }
    if (loader->secondResource != 0) {
        sub_80E5968(loader->secondResource, 3);
        loader->secondResource = 0;
    }
    heap_free_block(loader->workspace);
    FIELD_RESOURCE_RUNTIME->resourceDefault55C = FIELD_RESOURCE_DEFAULT_55C;
    FIELD_RESOURCE_RUNTIME->resourceDefault560 = FIELD_RESOURCE_DEFAULT_560;
    FIELD_RESOURCE_RUNTIME->resourceDefault564 = FIELD_RESOURCE_DEFAULT_564;
    FIELD_RESOURCE_RUNTIME->resourceDefault568 = FIELD_RESOURCE_DEFAULT_568;
    FIELD_RESOURCE_RUNTIME->resourceDefault56C = FIELD_RESOURCE_DEFAULT_56C;
    process_remove(&loader->process, flags);
}

SEC("small_functions_12", sub_80FB080)
struct FieldResourceLoaderProcess* field_resource_loader_create(
    struct FieldResourceLoaderProcess* loader, u8 priority, char* label)
{
    process_add(&loader->process, priority, label);
    loader->process.definition = FIELD_RESOURCE_LOADER_DEFINITION;
    loader->secondResource = 0;
    loader->firstResource = 0;
    loader->workspace = heap_alloc_block(
        TRUE, 0x9A8, FIELD_RESOURCE_LOADER_WORKSPACE_LABEL);
    FIELD_RESOURCE_MEMORY_FILL(0, loader->workspace, 0x9A8);
    FIELD_RESOURCE_RUNTIME->resourceDefault55C =
        FIELD_RESOURCE_DESCRIPTOR_55C->resource;
    FIELD_RESOURCE_RUNTIME->resourceDefault560 =
        FIELD_RESOURCE_DESCRIPTOR_560->resource;
    FIELD_RESOURCE_RUNTIME->resourceDefault564 =
        FIELD_RESOURCE_DESCRIPTOR_564->resource;
    FIELD_RESOURCE_RUNTIME->resourceDefault568 =
        FIELD_RESOURCE_DESCRIPTOR_568->resource;
    FIELD_RESOURCE_RUNTIME->resourceDefault56C =
        FIELD_RESOURCE_DESCRIPTOR_56C->resource;
    return loader;
}

EARLY_RESOURCE_SEC(sub_80293B8)
void field_load_auxiliary_resource_handles(
    struct FieldObjectResourceRuntime* runtime)
{
    const u16* resourceIds = runtime->resourceIdsC8;
    s32 i = 0;

    while (i < runtime->resourceCount10C) {
        runtime->handleStorage1C->auxiliaryResourceHandles15C[i] =
            sub_80214A4(0, *resourceIds, -1, 1);
        i++;
        resourceIds++;
    }
}

EARLY_RESOURCE_SEC(sub_80293B8)
const u16 field_load_auxiliary_resource_handles_padding = 0;

EARLY_RESOURCE_SEC(sub_8029380)
void field_release_inline_resource_objects(
    struct FieldObjectResourceRuntime* runtime)
{
    void** resourceObject;
    s32 i;

    if (runtime->inlineResourceReleaseEnabled112 != 0) {
        resourceObject = (void**)&runtime->ownedObjects28[2];
        for (i = 0; i < runtime->inlineResourceCount113; i++) {
            sub_80507E0(*resourceObject);
            resourceObject++;
        }
    }
}

EARLY_RESOURCE_SEC(sub_8029380)
const u16 field_release_inline_resource_objects_padding = 0;

EARLY_RESOURCE_SEC(sub_80292EC)
void field_destroy_owned_objects_and_allocations(
    struct FieldObjectResourceRuntime* runtime)
{
    struct FieldRuntimeOwnedObject* object;
    struct FieldRuntimeOwnedObjectDefinition* definition;
    s32 i;

    for (i = 0; i < runtime->ownedObjectCount10B; i++) {
        object = runtime->ownedObjects28[i];
        if (object != 0) {
            definition = object->definition338;
            definition->destroy(
                (u8*)object + definition->ownerOffset8, 3);
        }
    }
    free_heap_8018DA8(runtime->ownedAllocationsA8[0]);
    free_heap_8018DA8(runtime->ownedAllocationsA8[1]);
    free_heap_8018DA8(runtime->ownedAllocationsA8[2]);
    free_heap_8018DA8(runtime->ownedAllocationsA8[3]);
    free_heap_8018DA8(runtime->ownedAllocationsA8[4]);
    free_heap_8018DA8(runtime->ownedAllocationsA8[5]);
    free_heap_8018DA8(runtime->ownedAllocationsA8[6]);
    free_heap_8018DA8(runtime->ownedAllocationsA8[7]);
}

EARLY_RESOURCE_SEC(sub_80292A0)
void field_clear_runtime_flag_and_mode_vram(
    const struct FieldResourceCleanupContext* context)
{
    gFieldResourceGlobalState.flags888 &= -0x41;
    if (context->mode6 == 6) {
        FIELD_RESOURCE_MEMORY_FILL(0, (void*)0x0600C000, 0x20);
        *(u16*)0x02000008 = 0x1508;
    }
}

EARLY_RESOURCE_SEC(sub_80290E0)
void field_flush_dirty_workspace_blocks(
    struct FieldObjectResourceRuntime* runtime)
{
    u32* dirtyBlocks = &runtime->dirtyWorkspaceBlocksF0;
    u32* remainingBlocks;
    const u8* source;
    u8* destination;

    if (*dirtyBlocks != 0) {
        source = runtime->workspace24;
        destination = (u8*)0x02000080;
        remainingBlocks = dirtyBlocks;
        do {
            if (*remainingBlocks & 1)
                CpuFastSet(source, destination, 8);
            source += 0x20;
            destination += 0x20;
            *remainingBlocks >>= 1;
        } while (*remainingBlocks != 0);
    }
}


EARLY_RESOURCE_SEC(sub_80293F8)
void field_load_object_resource_handles(
    struct FieldObjectResourceRuntime* runtime, u16 setIndex)
{
    const u16* resourceIds;
    s32 i;

    runtime->resourceIdsC8 =
        field_get_object_resource_list(setIndex, &runtime->resourceCount10C);
    *(void**)0x03000C78 = 0;
    resourceIds = runtime->resourceIdsC8;
    i = 0;
    while (i < runtime->resourceCount10C) {
        runtime->handleStorage1C->objectResourceHandles5C[i] =
            sub_80213A0(0, *resourceIds, -1, 1);
        i++;
        resourceIds++;
    }
    *(void**)0x03000C78 = (void*)0x0800063C;
}
