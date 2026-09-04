#ifndef GUARD_GRAPHICS_FUNCTIONS_H
#define GUARD_GRAPHICS_FUNCTIONS_H

#include "global.h"

struct GraphicsPackedValueOwner;
struct GraphicsTileBufferOwner;
struct GraphicsPaletteOwner;
struct GraphicsResourceOwner;
struct GraphicsPositionState;

#define graphics_transfer_copy_2048_bytes sub_8160E4C
#define graphics_destroy_resource_owner_a sub_816154C
#define graphics_destroy_resource_owner_b sub_8161580
#define graphics_destroy_resource_owner_c sub_81615B4
#define graphics_copy_runtime_transfer_pair sub_81615E4
#define graphics_upload_fixed_tile_regions sub_8029460
#define graphics_noop_result sub_816132C
#define graphics_release_owned_resource sub_81612E4
#define graphics_position_state_is_idle sub_81631DC
#define graphics_initialize_position_state sub_8163264
#define graphics_destroy_position_state sub_8163280
#define graphics_counter_tick sub_81632C8
#define graphics_counter_reset sub_81632EC
#define graphics_destroy_counter sub_8163308
#define graphics_initialize_binding_record sub_816391C
#define graphics_write_rgb555 sub_8165250
#define graphics_clear_owned_8192_byte_buffer sub_8165404
#define graphics_destroy_value_pair_owner sub_8167E9C
#define graphics_clear_value_pair sub_8167F30
#define graphics_clear_tile_buffer sub_816507C
#define graphics_upload_tile_buffer sub_81650DC
#define graphics_upload_palette_state sub_8165420
#define graphics_destroy_palette_owner sub_8165454
#define graphics_resource_owner_initialize sub_816156C
#define graphics_position_state_reset sub_8163298
#define graphics_position_state_write_shared sub_816316C
#define graphics_fill_background_palettes sub_8163D80
#define graphics_advance_by_nibble_width sub_810D260
#define graphics_extract_mode_relative_index sub_8127E38
#define graphics_extract_owner_mode_relative_index sub_80E8F1C
#define graphics_update_global_resource_fcc_layer_4_mask_16 sub_80F032C

u32 graphics_extract_mode_relative_index(u32 value);
u32 graphics_extract_owner_mode_relative_index(
    struct GraphicsPackedValueOwner* owner,
    s32 value);
void graphics_update_global_resource_fcc_layer_4_mask_16(void);
void graphics_clear_tile_buffer(struct GraphicsTileBufferOwner* object);
void graphics_upload_tile_buffer(struct GraphicsTileBufferOwner* object);
void graphics_upload_palette_state(struct GraphicsPaletteOwner* object);
void graphics_destroy_palette_owner(struct GraphicsPaletteOwner* object,
                                    u32 flags);
struct GraphicsResourceOwner* graphics_resource_owner_initialize(
    struct GraphicsResourceOwner* object);
void graphics_position_state_reset(struct GraphicsPositionState* state,
                                   u16 flags);
void graphics_position_state_write_shared(struct GraphicsPositionState* state);
void graphics_fill_background_palettes(u16 value);

#endif
