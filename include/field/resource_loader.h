#ifndef GUARD_FIELD_RESOURCE_LOADER_H
#define GUARD_FIELD_RESOURCE_LOADER_H

#include "process/process.h"

struct FieldResourceLoaderProcess {
    struct Process process;
    u8 unknown1C[4];
    void* firstResource;
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

void field_resource_loader_shutdown(struct FieldResourceLoaderProcess* loader);
void field_resource_loader_destroy(struct FieldResourceLoaderProcess* loader,
                                   u32 flags);

#endif
