#ifndef GUARD_UI_LAYOUT_STATE_H
#define GUARD_UI_LAYOUT_STATE_H
#include "global.h"
struct UiStyleState { u16 flags; u16 value02; };
struct UiDefinitionNode { u32 value00; u32 value04; u32 value08; const void* definition; };
struct UiLayoutObject { u8 unknown00[0x24]; u32 originX; u32 originY; u8 unknown2C[0x38]; u32 data64; };
#define ui_style_state_initialize sub_8163320
#define ui_definition_node_initialize sub_81638B0
#define ui_pointer_slot_is_empty sub_8163748
#define ui_layout_set_data_64 sub_8163B5C
#define ui_reset_shared_halfword sub_8163BB8
#define ui_layout_set_origin sub_816544C
#define ui_set_flag_490_08 sub_816AFF0
#define ui_shared_mask_contains sub_8163BA0
void ui_style_state_initialize(struct UiStyleState* state);
struct UiDefinitionNode* ui_definition_node_initialize(struct UiDefinitionNode* node);
u32 ui_pointer_slot_is_empty(void* const* slot);
void ui_layout_set_data_64(struct UiLayoutObject* object, u32 data);
void ui_reset_shared_halfword(void);
void ui_layout_set_origin(struct UiLayoutObject* object, u32 x, u32 y);
void ui_set_flag_490_08(void* object);
u32 ui_shared_mask_contains(u16 mask);
#endif
