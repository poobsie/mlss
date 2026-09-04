#ifndef GUARD_OBJECT_RUNTIME_LEAF_CALLBACKS_H
#define GUARD_OBJECT_RUNTIME_LEAF_CALLBACKS_H

#include "object/runtime_object.h"

#define object_emit_effect_12cd_release_shared_motion_and_finish sub_8063384
#define object_emit_effect_12cd_stop_release_and_finish sub_80633D0
#define object_start_animation_2_and_effect_12a3_when_ready sub_8063420
#define object_restore_saved_xy_and_start_animation_6 sub_80639C0
#define object_move_left_2_until_screen_exit sub_8063BF0
#define object_move_left_and_down_slow_until_screen_exit sub_80643DC
#define object_count_to_15_then_stop_on_visual_complete sub_80644DC
#define object_update_accelerating_arc_until_x_threshold sub_8064B88
#define object_start_animation_3_when_state_clears sub_8065310
#define object_start_animation_9_effect_112b_on_visual_complete sub_8065D10
#define object_start_animation_5_when_value80_clears sub_8063A24
#define object_advance_countdown_visual_sequence sub_8063AD4
#define object_start_animation_7_on_visual_complete sub_8063B2C
#define object_finish_countdown_with_animation_1 sub_8063C24
#define object_emit_effect_1081_and_finish sub_8064424
#define object_start_animation_2_variant_on_ready sub_8064488
#define object_start_animation_3_then_complex_sequence sub_8064514
#define object_idle_when_link_clears sub_80652D4
#define object_emit_effect_eff_and_finish sub_8065384
#define object_start_animation_2_then_effect_sequence sub_80653F4
#define object_advance_visual_timer_with_sound_d5 sub_8065CC4
#define object_branch_animation_on_visual_timer sub_8065DD4
#define object_finish_animation_15_on_countdown sub_8065EA0
#define object_store_motion_target sub_8066540
#define object_copy_position_to_link_and_finish_when_value80_clears sub_8066550
#define object_start_variant_animation_and_sound_when_value80_clears sub_8066604
#define object_prepare_saved_motion_on_visual_complete sub_806670C
#define object_prepare_repeat_variant_on_ready sub_80667C4
#define object_start_animation_9_with_short_timer sub_8066C90
#define object_advance_repeating_animation_count sub_8066CEC
#define object_prepare_fixed_motion_on_visual_complete sub_8066DA4
#define object_start_animation_6_and_random_repeat_count sub_8066E5C
#define object_begin_countdown_motion_when_ready sub_8067838
#define object_advance_alternating_visual_countdown sub_8067F94
#define object_emit_effect_10c6_when_ready sub_806800C
#define object_move_left_by_value84_until_screen_exit sub_8068124
#define object_initialize_behavior_and_resume_motion sub_8068168
#define object_emit_effect_10be_and_finish sub_80681EC
#define object_finish_secondary_countdown_with_animation_7 sub_806822C
#define object_lower_x_until_motion_target sub_8068818
#define object_prepare_linked_motion_when_chain_clears sub_8068844
#define object_finish_variant_countdown_on_visual_complete sub_80688B8
#define object_finish_variant_timer_on_visual_complete sub_8068A50
#define object_move_left_with_periodic_effect_until_screen_exit sub_8068B68
#define object_move_left_with_effect_until_owner_target sub_8068BF0
#define object_start_variant_return_when_value80_clears sub_8068C98
#define object_finish_variant_return_timer sub_8068D74
#define object_resume_after_auxiliary_motion sub_8068E7C
#define object_move_left_until_owner_target_and_emit_effect sub_8068E98
#define object_resume_sequence_when_runtime_ready sub_8069354
#define object_move_left_until_screen_exit sub_8068074
#define object_start_animation_6_when_value80_clears sub_80680A0
#define object_move_left_and_down_until_screen_exit sub_806819C
#define object_move_left_fast_until_screen_exit sub_80687EC
#define object_repeat_animation_until_behavior_count_expires sub_806C800
#define object_finish_visual_and_stop_update sub_806CB3C
#define object_release_position_owner_and_continue sub_806E690

void object_emit_effect_12cd_release_shared_motion_and_finish(
    struct RuntimeObject* object);
void object_emit_effect_12cd_stop_release_and_finish(
    struct RuntimeObject* object);
void object_start_animation_2_and_effect_12a3_when_ready(
    struct RuntimeObject* object);
void object_restore_saved_xy_and_start_animation_6(
    struct RuntimeObject* object);
void object_move_left_2_until_screen_exit(struct RuntimeObject* object);
void object_move_left_and_down_slow_until_screen_exit(
    struct RuntimeObject* object);
void object_count_to_15_then_stop_on_visual_complete(
    struct RuntimeObject* object);
void object_update_accelerating_arc_until_x_threshold(
    struct RuntimeObject* object);
s32 object_start_animation_3_when_state_clears(struct RuntimeObject* object);
void object_start_animation_9_effect_112b_on_visual_complete(
    struct RuntimeObject* object);
void object_start_animation_5_when_value80_clears(
    struct RuntimeObject* object);
void object_advance_countdown_visual_sequence(struct RuntimeObject* object);
void object_start_animation_7_on_visual_complete(
    struct RuntimeObject* object);
void object_finish_countdown_with_animation_1(struct RuntimeObject* object);
void object_emit_effect_1081_and_finish(struct RuntimeObject* object);
void object_start_animation_2_variant_on_ready(struct RuntimeObject* object);
void object_start_animation_3_then_complex_sequence(
    struct RuntimeObject* object);
void object_idle_when_link_clears(struct RuntimeObject* object);
void object_emit_effect_eff_and_finish(struct RuntimeObject* object);
void object_start_animation_2_then_effect_sequence(
    struct RuntimeObject* object);
void object_advance_visual_timer_with_sound_d5(struct RuntimeObject* object);
void object_branch_animation_on_visual_timer(struct RuntimeObject* object);
void object_finish_animation_15_on_countdown(struct RuntimeObject* object);
void object_store_motion_target(
    struct RuntimeObject* object, s32 x, s32 y, s32 z);
void object_copy_position_to_link_and_finish_when_value80_clears(
    struct RuntimeObject* object);
void object_start_variant_animation_and_sound_when_value80_clears(
    struct RuntimeObject* object);
void object_prepare_saved_motion_on_visual_complete(
    struct RuntimeObject* object);
void object_prepare_repeat_variant_on_ready(struct RuntimeObject* object);
void object_start_animation_9_with_short_timer(struct RuntimeObject* object);
void object_advance_repeating_animation_count(struct RuntimeObject* object);
void object_prepare_fixed_motion_on_visual_complete(
    struct RuntimeObject* object);
void object_start_animation_6_and_random_repeat_count(
    struct RuntimeObject* object);
s32 object_begin_countdown_motion_when_ready(struct RuntimeObject* object);
void object_advance_alternating_visual_countdown(
    struct RuntimeObject* object);
s32 object_emit_effect_10c6_when_ready(struct RuntimeObject* object);
void object_move_left_by_value84_until_screen_exit(
    struct RuntimeObject* object);
s32 object_initialize_behavior_and_resume_motion(struct RuntimeObject* object);
void object_emit_effect_10be_and_finish(struct RuntimeObject* object);
void object_finish_secondary_countdown_with_animation_7(
    struct RuntimeObject* object);
void object_lower_x_until_motion_target(struct RuntimeObject* object);
void object_prepare_linked_motion_when_chain_clears(
    struct RuntimeObject* object);
void object_finish_variant_countdown_on_visual_complete(
    struct RuntimeObject* object);
void object_finish_variant_timer_on_visual_complete(
    struct RuntimeObject* object);
void object_move_left_with_periodic_effect_until_screen_exit(
    struct RuntimeObject* object);
void object_move_left_with_effect_until_owner_target(
    struct RuntimeObject* object);
void object_start_variant_return_when_value80_clears(
    struct RuntimeObject* object);
void object_finish_variant_return_timer(struct RuntimeObject* object);
s32 object_resume_after_auxiliary_motion(struct RuntimeObject* object);
void object_move_left_until_owner_target_and_emit_effect(
    struct RuntimeObject* object);
s32 object_resume_sequence_when_runtime_ready(struct RuntimeObject* object);
void object_move_left_until_screen_exit(struct RuntimeObject* object);
void object_start_animation_6_when_value80_clears(struct RuntimeObject* object);
void object_move_left_and_down_until_screen_exit(struct RuntimeObject* object);
void object_move_left_fast_until_screen_exit(struct RuntimeObject* object);
void object_repeat_animation_until_behavior_count_expires(
    struct RuntimeObject* object);
void object_finish_visual_and_stop_update(struct RuntimeObject* object);
s32 object_release_position_owner_and_continue(struct RuntimeObject* object);

#endif
