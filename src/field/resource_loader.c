#include "field/resource_loader.h"

void heap_free_block(void* allocation);
void sub_80E5968(void* resource, s32 flags);
void sub_80E8EFC(void* resource, s32 flags);
void sub_80F94A8(void);
void sub_80FADD4(struct FieldResourceLoaderProcess* loader);

#define SEC(group, symbol) __attribute__((section(".text." group "." #symbol)))

#define FIELD_RESOURCE_RUNTIME (*(struct FieldResourceRuntime**)0x03000FC0)

#define FIELD_RESOURCE_DEFAULT_55C (*(void**)0x083B9704)
#define FIELD_RESOURCE_DEFAULT_560 (*(void**)0x083B98C4)
#define FIELD_RESOURCE_DEFAULT_564 (*(void**)0x083B9D00)
#define FIELD_RESOURCE_DEFAULT_568 (*(void**)0x083BA13C)
#define FIELD_RESOURCE_DEFAULT_56C (*(void**)0x083BA4A8)

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
        sub_80E8EFC(loader->firstResource, 3);
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
