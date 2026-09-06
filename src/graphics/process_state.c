#include "graphics/process_state.h"
#include "process/process.h"

#define SEC(name) __attribute__((section(".text.graphics_process_state." #name)))
#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define MISC_SEC(name) \
    __attribute__((section(".text.misc_helpers_01." STRINGIFY(name))))
#define MISC2_SEC(name) \
    __attribute__((section(".text.misc_helpers_02." STRINGIFY(name))))
#define MISC3_SEC(name) \
    __attribute__((section(".text.misc_helpers_03." STRINGIFY(name))))
void free_heap_8018D9C();
void free_heap_8018DA8(void* pointer);
void sub_8029888(s32 channel, s32 value);
void sub_80184F4(void* address);
void sub_8058278(struct GraphicsStagingSource* source);
void sub_80582DC(struct GraphicsStagingSource* source);
void sub_80584F8(struct GraphicsStagingSource* source);
void sub_80587BC(struct GraphicsStagingSource* source, s32 mode);
void sub_8115048(void* resourceObject, u8 configurationId, u8 value);
void graphics_load_runtime_configuration(void* owner, u16 configurationIndex);
void sub_8018218(void* source, void* destination, u32 size, u32 width, u32 mode);
void sub_805D0DC(struct GraphicsProcessState* process);
void sub_805D93C(struct GraphicsProcessState* process, u32 value);
void sub_805D288(struct GraphicsProcessState* process);

#define FRAME_TRANSFER_SOURCE (*(void**)0x03000E08)
#define FRAME_TRANSFER_STAGING (*(u16**)0x03000E0C)

MISC2_SEC(graphics_apply_staging_source)
void graphics_apply_staging_source(struct GraphicsStagingSource* source)
{
    graphics_copy_staging_values(source);
    sub_80582DC(source);
    sub_80587BC(source, 0);
    sub_8058278(source);
    sub_80584F8(source);
}

MISC3_SEC(graphics_copy_compact_staging_values)
void graphics_copy_compact_staging_values(
    struct GraphicsCompactStagingSource* source)
{
    *(s16*)0x02000010 = source->maskedValue0 & 0x1FF;
    *(s16*)0x02000014 = source->maskedValue1 & 0x1FF;
    *(s16*)0x02000012 = source->component0 & 0xFF;
    *(s16*)0x02000016 = source->component1 & 0xFF;
}

SEC(sub_805C5F4)
void graphics_frame_transfer_callback(void)
{
    vu16* displayBase = (vu16*)0x04000014;
    vu16* displayTarget = displayBase + 4;
    u16** stagingGlobal = (u16**)0x03000E0C;
    u16* staging = *stagingGlobal;
    vu32* dma3;

    displayBase[4] = staging[0];
    displayBase[5] = staging[1];
    CpuFastSet(FRAME_TRANSFER_SOURCE, staging, 0xA0);
    dma3 = (vu32*)0x040000B0;
    *(vu16*)0x040000BA = 0;
    dma3[0] = (u32)(*stagingGlobal + 1);
    dma3[1] = (u32)displayTarget;
    dma3[2] = 0xA6400001;
}

SEC(sub_805C644)
void graphics_selected_register_transfer_callback(void)
{
    u32 selection =
        gGraphicsTransferRuntimeSelection.destinationRecord & 0x1F;
    u32 registerOffset =
        ((u32)gGraphicsTransferDestinationTable[selection][0] << 30) >> 28;
    vu16* firstDestination = (vu16*)((u8*)0x04000014 + registerOffset);
    u16** stagingGlobal = (u16**)0x03000E0C;
    u16* staging = *stagingGlobal;
    vu32* dma3;

    firstDestination[0] = staging[0];
    *(vu16*)((u8*)0x04000016 + registerOffset) = staging[1];
    CpuFastSet(FRAME_TRANSFER_SOURCE, staging, 0xA0);
    dma3 = (vu32*)0x040000B0;
    *(vu16*)0x040000BA = 0;
    dma3[0] = (u32)(*stagingGlobal + 1);
    dma3[1] = (u32)firstDestination;
    dma3[2] = 0xA6400001;
}

SEC(sub_805C78C)
void graphics_apply_indexed_resource_entry_value(
    struct GraphicsResourceEntryOwner* owner, u8 index, u8 value)
{
    sub_8115048(
        owner->resourceObject, owner->resourceEntryIndices[index], value);
}

SEC(sub_805DA04)
void graphics_set_configuration_state_and_load(
    struct GraphicsRuntimeConfigurationProcess* process,
    u16 configurationIndex)
{
    process->state = -5;
    process->configurationIndex = configurationIndex;
    graphics_load_runtime_configuration(process, process->configurationIndex);
}

SEC(sub_805C9A4)
void graphics_copy_indexed_tile_resource_to_vram(
    void* owner, u16 destinationTile, u8 tileCount, u16 resourceIndex)
{
    const u8* resourceBase = (const u8*)0x08940C9C;
    const u32* resourceOffsets = (const u32*)resourceBase;
    const void* source = resourceBase + resourceOffsets[resourceIndex];
    void* destination = (u8*)0x06004000 + destinationTile * 32;

    sub_8018218((void*)source, destination, tileCount * 32, 32, 0);
}

SEC(sub_805D8DC)
void graphics_copy_indexed_tile_resource_to_vram_alternate(
    void* owner, u16 destinationTile, u8 tileCount, u16 resourceIndex)
{
    const u8* resourceBase = (const u8*)0x08940C9C;
    const u32* resourceOffsets = (const u32*)resourceBase;
    const void* source = resourceBase + resourceOffsets[resourceIndex];
    void* destination = (u8*)0x06004000 + destinationTile * 32;

    sub_8018218((void*)source, destination, tileCount * 32, 32, 0);
}

SEC(sub_805D9CC)
void graphics_rebuild_and_upload_vram_buffer(
    struct GraphicsProcessState* process)
{
    sub_805D0DC(process);
    sub_805D93C(process, 0);
    sub_805D288(process);
    sub_8018218(process->buffer94, (void*)0x06000000, 0x3000, 32, 0);
}
const u16 graphics_rebuild_and_upload_vram_buffer_padding
    SEC(sub_805D9CC) = 0;

SEC(sub_8059F24) void sub_8059F24(struct GraphicsStagingSource* source)
{
    *(s16*)0x02000014 = source->maskedValue0 & 0x1FF;
    *(s16*)0x02000018 = source->maskedValue1 & 0x1FF;
    *(s16*)0x0200001C = source->maskedValue2 & 0x1FF;
    *(s16*)0x02000016 = source->component0;
    *(s16*)0x0200001A = source->component1;
    *(s16*)0x0200001E = source->component2;
}

SEC(sub_805C73C) void sub_805C73C(struct GraphicsProcessState* process, s32 flags)
{
    process->descriptor = (void*)0x08CDC2B8;
    *(s16*)0x040000BA = 0;
    sub_8029888(0, 0);
    process->active = 0;
    if (*(s32*)0x03000E04 != 0) {
        free_heap_8018D9C();
    }
    if (*(s32*)0x03000E00 != 0) {
        free_heap_8018D9C();
    }
    process_remove((struct Process*)process, flags);
}

SEC(sub_805DA1C) void sub_805DA1C(struct GraphicsProcessState* process, s32 flags)
{
    process->descriptor = (void*)0x08CDC2C8;
    sub_80184F4((void*)0x06000000);
    if (process->bufferA4 != 0) {
        free_heap_8018D9C();
    }
    if (process->bufferA8 != 0) {
        free_heap_8018D9C();
    }
    if (process->buffer98 != 0) {
        free_heap_8018D9C();
    }
    if (process->buffer94 != 0) {
        free_heap_8018D9C();
    }
    process_remove((struct Process*)process, flags);
}

SEC(sub_805CCC0) void graphics_free_owner_if_requested(void* owner, s32 flags)
{
    if (flags & 1)
        free_heap_8018DA8(owner);
}
const u16 graphics_free_owner_if_requested_padding
    SEC(sub_805CCC0) = 0;

void graphics_copy_staging_values(struct GraphicsStagingSource* source)
    __attribute__((alias("sub_8059F24")));
void graphics_destroy_transfer_process(struct GraphicsProcessState* process, s32 flags)
    __attribute__((alias("sub_805C73C")));
void graphics_destroy_vram_process(struct GraphicsProcessState* process, s32 flags)
    __attribute__((alias("sub_805DA1C")));

MISC_SEC(graphics_terminate_process_label_at_2)
void graphics_terminate_process_label_at_2(struct Process* process)
{
    process->label[2] = 0;
}
MISC_SEC(graphics_terminate_process_label_at_2)
const u16 graphics_terminate_process_label_at_2_padding = 0;
