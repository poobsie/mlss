#ifndef GUARD_GRAPHICS_PROCESS_STATE_H
#define GUARD_GRAPHICS_PROCESS_STATE_H

#include "global.h"

struct GraphicsStagingSource {
    u8 unknown00[0x5A];
    u16 maskedValue0;
    u16 maskedValue1;
    u16 maskedValue2;
    u8 component0;
    u8 unknown61;
    u8 component1;
    u8 unknown63;
    u8 component2;
};

struct GraphicsStagingValues {
    s16 maskedValue0;
    s16 component0;
    s16 maskedValue1;
    s16 component1;
    s16 maskedValue2;
    s16 component2;
};

struct GraphicsCompactStagingSource {
    u8 unknown00[0x30];
    u16 maskedValue0;
    u16 maskedValue1;
    u16 component0;
    u16 component1;
};

struct GraphicsTransferRuntimeSelection {
    u8 unknown00[0x0B];
    u8 destinationRecord;
};

struct GraphicsResourceEntryOwner {
    u8 unknown00[0x57C];
    void* resourceObject;
    u8 resourceEntryIndices[4];
};

struct GraphicsRuntimeConfigurationProcess {
    u8 unknown00[0x1C];
    s16 state;
    u16 configurationIndex;
};

extern volatile struct GraphicsTransferRuntimeSelection
    gGraphicsTransferRuntimeSelection;
extern const u8 gGraphicsTransferDestinationTable[][4];

struct GraphicsProcessState {
    u8 unknown00[0x18];
    const void* descriptor;
    u8 active;
    u8 unknown1D[0x77];
    void* buffer94;
    void* buffer98;
    u8 unknown9C[8];
    void* bufferA4;
    void* bufferA8;
};

struct Process;
#define graphics_terminate_process_label_at_2 sub_805CCD8
#define graphics_apply_staging_source sub_8059FE4
#define graphics_copy_compact_staging_values sub_805A95C
#define graphics_free_owner_if_requested sub_805CCC0
#define graphics_frame_transfer_callback sub_805C5F4
#define graphics_selected_register_transfer_callback sub_805C644
#define graphics_apply_indexed_resource_entry_value sub_805C78C
#define graphics_copy_indexed_tile_resource_to_vram sub_805C9A4
#define graphics_copy_indexed_tile_resource_to_vram_alternate sub_805D8DC
#define graphics_rebuild_and_upload_vram_buffer sub_805D9CC
#define graphics_load_runtime_configuration sub_805D914
#define graphics_set_configuration_state_and_load sub_805DA04

void graphics_copy_staging_values(struct GraphicsStagingSource* source);
void graphics_apply_staging_source(struct GraphicsStagingSource* source);
void graphics_copy_compact_staging_values(
    struct GraphicsCompactStagingSource* source);
void graphics_free_owner_if_requested(void* owner, s32 flags);
void graphics_frame_transfer_callback(void);
void graphics_selected_register_transfer_callback(void);
void graphics_apply_indexed_resource_entry_value(
    struct GraphicsResourceEntryOwner* owner, u8 index, u8 value);
void graphics_copy_indexed_tile_resource_to_vram(
    void* owner, u16 destinationTile, u8 tileCount, u16 resourceIndex);
void graphics_copy_indexed_tile_resource_to_vram_alternate(
    void* owner, u16 destinationTile, u8 tileCount, u16 resourceIndex);
void graphics_rebuild_and_upload_vram_buffer(
    struct GraphicsProcessState* process);
void graphics_load_runtime_configuration(void* owner, u16 configurationIndex);
void graphics_set_configuration_state_and_load(
    struct GraphicsRuntimeConfigurationProcess* process,
    u16 configurationIndex);
void graphics_destroy_transfer_process(struct GraphicsProcessState* process, s32 flags);
void graphics_destroy_vram_process(struct GraphicsProcessState* process, s32 flags);
void graphics_terminate_process_label_at_2(struct Process* process);

#endif
