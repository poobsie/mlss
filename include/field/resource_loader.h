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

struct FieldObjectResourceHandleStorage {
    u8 unknown000[0x5C];
    void* objectResourceHandles5C[0x40];
    void* auxiliaryResourceHandles15C[1];
};

struct FieldRuntimeOwnedObjectDefinition {
    u8 unknown00[8];
    s16 ownerOffset8;
    u8 unknown0A[2];
    void (*destroy)(void* owner, u32 flags);
};

struct FieldRuntimeOwnedObject {
    u8 unknown000[0x338];
    struct FieldRuntimeOwnedObjectDefinition* definition338;
};

struct FieldResourceCleanupContext {
    u8 unknown00[6];
    s16 mode6;
};

struct FieldObjectResourceRuntime {
    u8 unknown000[0x1C];
    struct FieldObjectResourceHandleStorage* handleStorage1C;
    u8 unknown020[4];
    const u8* workspace24;
    struct FieldRuntimeOwnedObject* ownedObjects28[0x20];
    void* ownedAllocationsA8[8];
    const u16* resourceIdsC8;
    u8 unknown0CC[0x24];
    u32 dirtyWorkspaceBlocksF0;
    u8 unknown0F4[0x17];
    u8 ownedObjectCount10B;
    u8 resourceCount10C;
    u8 unknown10D[5];
    u8 inlineResourceReleaseEnabled112;
    u8 inlineResourceCount113;
};

#define field_resource_loader_shutdown sub_80FAEFC
#define field_resource_loader_destroy sub_80FAFD8
#define field_resource_loader_create sub_80FB080
#define field_load_auxiliary_resource_handles sub_80293B8
#define field_load_object_resource_handles sub_80293F8
#define field_release_inline_resource_objects sub_8029380
#define field_destroy_owned_objects_and_allocations sub_80292EC
#define field_clear_runtime_flag_and_mode_vram sub_80292A0
#define field_flush_dirty_workspace_blocks sub_80290E0
#define field_owned_resource_destroy sub_80E8EFC
#define field_resource_block_list_destroy sub_80E9484

void field_resource_loader_shutdown(struct FieldResourceLoaderProcess* loader);
void field_resource_loader_destroy(struct FieldResourceLoaderProcess* loader,
                                   u32 flags);
struct FieldResourceLoaderProcess* field_resource_loader_create(
    struct FieldResourceLoaderProcess* loader, u8 priority, char* label);
void field_load_auxiliary_resource_handles(
    struct FieldObjectResourceRuntime* runtime);
void field_load_object_resource_handles(
    struct FieldObjectResourceRuntime* runtime, u16 setIndex);
void field_release_inline_resource_objects(
    struct FieldObjectResourceRuntime* runtime);
void field_destroy_owned_objects_and_allocations(
    struct FieldObjectResourceRuntime* runtime);
void field_clear_runtime_flag_and_mode_vram(
    const struct FieldResourceCleanupContext* context);
void field_flush_dirty_workspace_blocks(
    struct FieldObjectResourceRuntime* runtime);
void field_owned_resource_destroy(struct FieldOwnedResource* resource, u32 flags);
void field_resource_block_list_destroy(struct FieldResourceBlockList* list,
                                       u32 flags);

#endif
