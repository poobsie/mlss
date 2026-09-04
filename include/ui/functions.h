#ifndef GUARD_UI_FUNCTIONS_H
#define GUARD_UI_FUNCTIONS_H

#include "global.h"

#define ui_object_reset_and_update sub_81639E0
#define ui_object_reset sub_81639F8
#define ui_sprite_pair_hide sub_8163A24
#define ui_sprite_pair_show sub_8163A44
#define ui_object_set_values_18_20 sub_8163A64
#define ui_object_copy_pair_values sub_8163A6C
#define ui_object_configure_mode6 sub_81639C4
#define ui_object_set_visual sub_81639D4
#define ui_object_grid_reset_visual sub_8163650
#define ui_object_list_apply_state sub_8163864
#define ui_sprite_pair_destroy_base sub_8163B60
#define ui_sprite_pair_destroy_variant sub_8163D4C
#define ui_clear_flag_8_at_490 sub_816AFDC
#define ui_stop_sound_97_if_active sub_816D6D4
#define ui_start_sound_97_if_inactive sub_816D6F0
#define ui_clear_value_ea_and_stop_sound_97 sub_8171DD4

struct UiObject;
struct UiObjectPairValues;
struct UiObjectGrid;
struct UiObjectNodeList;
void ui_object_copy_pair_values(struct UiObjectPairValues* object);
void ui_object_configure_mode6(struct UiObject* object, s32 value);
void ui_object_set_visual(struct UiObject* object, void* visual);
void ui_object_grid_reset_visual(struct UiObjectGrid* grid, u32 row, u32 column);
void ui_object_list_apply_state(struct UiObjectNodeList* list, u32 mode, u32 value);

#endif
