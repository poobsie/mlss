#ifndef GUARD_FIELD_RESOURCE_LOADER_H
#define GUARD_FIELD_RESOURCE_LOADER_H

#include "process/process.h"

struct FieldOwnedResource {
    void* allocation;
};

struct FieldResourceBlockList {
    u8 unknown00[0x0C];
    void* blocks;
};

struct FieldResourceLoaderProcess {
    struct Process process;
    u8 unknown1C[4];
    struct FieldOwnedResource* firstResource;
    void* workspace;
    void* secondResource;
};

struct FieldResourceRuntime {
    u8 unknown000[0x100];
    u32 flags100;
    u8 unknown104[0x458];
    void* resourceDefault55C;
    void* resourceDefault560;
    void* resourceDefault564;
    void* resourceDefault568;
    void* resourceDefault56C;
};

#define field_resource_loader_shutdown sub_80FAEFC
#define field_resource_loader_destroy sub_80FAFD8
#define field_owned_resource_destroy sub_80E8EFC
#define field_resource_block_list_destroy sub_80E9484

void field_resource_loader_shutdown(struct FieldResourceLoaderProcess* loader);
void field_resource_loader_destroy(struct FieldResourceLoaderProcess* loader,
                                   u32 flags);
void field_owned_resource_destroy(struct FieldOwnedResource* resource, u32 flags);
void field_resource_block_list_destroy(struct FieldResourceBlockList* list,
                                       u32 flags);

#endif
