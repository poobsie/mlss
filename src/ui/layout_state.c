#include "ui/layout_state.h"
void ui_style_state_initialize(struct UiStyleState* state) __attribute__((section(".text.sub_8163320")));
void ui_style_state_initialize(struct UiStyleState* state) { state->flags = 0x10; state->value02 = 0; }
__attribute__((section(".text.sub_8163320"))) const u16 ui_style_state_initialize_padding = 0;
struct UiDefinitionNode* ui_definition_node_initialize(struct UiDefinitionNode* node) __attribute__((section(".text.sub_81638B0")));
struct UiDefinitionNode* ui_definition_node_initialize(struct UiDefinitionNode* node) { node->value04 = 0; node->value00 = 0; node->value08 = 0; node->definition = (const void*)0x08CDD0E8; return node; }
u32 ui_pointer_slot_is_empty(void* const* slot) __attribute__((section(".text.sub_8163748")));
u32 ui_pointer_slot_is_empty(void* const* slot) { return *slot == 0; }
__attribute__((section(".text.sub_8163748"))) const u16 ui_pointer_slot_is_empty_padding = 0;
void ui_layout_set_data_64(struct UiLayoutObject* object, u32 data) __attribute__((section(".text.sub_8163B5C")));
void ui_layout_set_data_64(struct UiLayoutObject* object, u32 data) { object->data64 = data; }
void ui_reset_shared_halfword(void) __attribute__((section(".text.sub_8163BB8")));
void ui_reset_shared_halfword(void) { *(u16*)0x0300102C = 0; }
void ui_layout_set_origin(struct UiLayoutObject* object, u32 x, u32 y) __attribute__((section(".text.sub_816544C")));
void ui_layout_set_origin(struct UiLayoutObject* object, u32 x, u32 y) { object->originX = x; object->originY = y; }
__attribute__((section(".text.sub_816544C"))) const u16 ui_layout_set_origin_padding = 0;
