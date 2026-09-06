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
#define ui_object_group4_reset_state sub_81634DC
#define ui_object_visual_is_idle sub_8163A08
#define ui_object_update_direction_toward_point sub_8167D50
#define ui_sprite_pair_destroy_base sub_8163B60
#define ui_sprite_pair_destroy_variant sub_8163D4C
#define ui_clear_flag_8_at_490 sub_816AFDC
#define ui_stop_sound_97_if_active sub_816D6D4
#define ui_start_sound_97_if_inactive sub_816D6F0
#define ui_clear_value_ea_and_stop_sound_97 sub_8171DD4
#define ui_value_tracker_reset sub_816D814
#define ui_countdown_start_60 sub_816D898
#define ui_delayed_countdown_start_180 sub_8171F44
#define ui_object_update_vertical_bounce sub_816D734

struct UiObject;
struct UiObjectPairValues;
struct UiSpritePair;
struct UiObjectGrid;
struct UiObjectGroup4;
struct UiObjectNodeList;
struct UiValueTracker;
struct UiCountdown;
struct UiDelayedCountdown;
struct UiBouncingObject;
void ui_object_copy_pair_values(struct UiObjectPairValues* object);
void ui_object_configure_mode6(struct UiObject* object, s32 value);
void ui_object_set_visual(struct UiObject* object, void* visual);
void ui_object_grid_reset_visual(struct UiObjectGrid* grid, u32 row, u32 column);
void ui_object_list_apply_state(struct UiObjectNodeList* list, u32 mode, u32 value);
void ui_object_group4_reset_state(struct UiObjectGroup4* group);
u32 ui_object_visual_is_idle(struct UiObject* object);
void ui_object_update_direction_toward_point(void* unused,
                                             struct UiObject* object,
                                             s32 targetX, s32 targetY);
void ui_object_reset(struct UiObject* object, void* value);
void ui_sprite_pair_hide(struct UiSpritePair* object);
void ui_value_tracker_reset(struct UiValueTracker* tracker);
void ui_countdown_start_60(struct UiCountdown* countdown);
void ui_delayed_countdown_start_180(struct UiDelayedCountdown* countdown);
void ui_object_update_vertical_bounce(struct UiBouncingObject* object);

#endif
