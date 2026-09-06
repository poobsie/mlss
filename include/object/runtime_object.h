#ifndef GUARD_OBJECT_RUNTIME_OBJECT_H
#define GUARD_OBJECT_RUNTIME_OBJECT_H

#include "global.h"

enum RuntimeObjectVariant {
    RUNTIME_OBJECT_VARIANT_FIRST = -1,
    RUNTIME_OBJECT_VARIANT_SECOND = -2,
};

struct RuntimeObjectValueSource {
    u8 unknown00[6];
    s8 value6;
};

struct RuntimeObjectVisual;

struct RuntimeObjectState {
    u8 unknown00[0x10];
    struct RuntimeObjectVisual* visual10;
    u8 unknown14[0x24];
    s32 value38;
    s32 value3C;
    s32 value40;
    u8 unknown44[0x60];
    s32 valueA4;
    u8 unknownA8[0x0C];
    s16 valueB4;
    u8 unknownB6[0x0D];
    s8 displayOffsetX;
    s8 displayOffsetY;
    s8 displayOffsetZ;
    u8 unknownC6[0x12];
    s32 valueD8;
    s32 valueDC;
    s32 floorHeight;
    struct RuntimeObjectValueSource* valueSourceE4;
    u8 unknownE8[4];
    s16 variant;
    u8 unknownEE[0x23];
    s8 flags111;
    u8 unknown112;
    u8 value113;
    u32 snapshot114;
};

struct RuntimeObject;
struct ObjectPositionHistoryNode;
typedef void (*RuntimeObjectCallback)(struct RuntimeObject* object);

struct RuntimeObjectVisual {
    s16 coordinate0;
    u8 unknown02[2];
    s16 value04;
    s16 value06;
    u8 unknown08[4];
    s16 value0C;
    u8 unknown0E[3];
    u8 flags11;
    u8 flags;
    u8 unknown13[0x0D];
    u8 parameter20;
    u8 value21;
};

struct RuntimeObject {
    u8 unknown00[8];
    struct RuntimeObjectVisual* visual;
    struct ObjectPositionHistoryNode* positionHistory;
    s32 currentPositionX;
    s32 currentPositionY;
    s32 verticalPosition;
    u8 unknown1C[0x0C];
    struct RuntimeObjectState* state;
    void* positionOwner;
    struct RuntimeObject* linkedObject;
    u8 unknown34[4];
    s32 positionX;
    s32 positionY;
    s32 positionZBase;
    u8 unknown44;
    s8 boundaryOffset45;
    u8 unknown46[6];
    RuntimeObjectCallback update;
    RuntimeObjectCallback followup;
    s32 auxiliaryState;
    RuntimeObjectCallback auxiliaryUpdate;
    RuntimeObjectCallback secondaryUpdate;
    RuntimeObjectCallback tertiaryUpdate;
    u8 unknown64[4];
    RuntimeObjectCallback cleanup;
    const void* descriptor;
    u8 unknown70[4];
    s8 value74;
    u8 unknown75;
    u8 flags76;
    u8 flags77;
    u8 unknown78;
    u8 flags79;
    s16 unknown7A;
    u16 unknown7C;
    u8 unknown7E[2];
    s32 value80;
    s32 value84;
    u8 unknown88[4];
    s32 value8C;
    u8 unknown90[2];
    s16 motionDuration92;
    s32 verticalAcceleration;
    u32 value98;
    s32 behaviorState;
    s32 valueA0;
    s32 valueA4;
    s32 valueA8;
    s16 timer;
    s16 secondaryTimer;
    u16 stateValueB0;
    s16 verticalVelocity;
    u8 unknownB4[0x0F];
    s8 displayOffsetX;
    s8 displayOffsetY;
    s8 displayOffsetZ;
};

void sub_8087540(struct RuntimeObject* object);
void runtime_object_finish_action(struct RuntimeObject* object);

#define runtime_object_when_value80_clear_prepare_state_motion sub_808750C
#define runtime_object_clear_behavior sub_8087540
#define runtime_object_advance_vertical_to_limit sub_80877C0
#define runtime_resolve_reflected_interval sub_8087878
#define runtime_object_start_timed_motion sub_808842C
#define runtime_object_visual_apply_transform sub_8083E84
#define runtime_object_begin_owner_vector_motion sub_80874B4
#define object_start_owner_position_effect_and_continue sub_810F6D4
#define object_start_owner_position_effect_variant_and_continue sub_810F5E4
#define object_finish_paired_owner_effect sub_810F824
#define object_start_owner_position_effect_with_auxiliary sub_810F904
#define object_start_owner_position_effect_to_visual_reset sub_810F9FC
#define object_start_fixed_position_effect_with_auxiliary sub_810FA8C
#define object_reset_owner_position_visual_when_ready sub_810FC34
#define object_finish_owner_position_effect_with_delayed_spawn sub_810FC70
#define object_start_animation_2_then_owner_offset_effect sub_810FEC8
#define object_start_far_owner_position_effect sub_810FFB0
#define object_countdown_then_start_paired_owner_effect sub_8110034
#define object_start_far_owner_position_effect_variant sub_81100B0
#define object_return_to_auxiliary_owner_effect_when_ready sub_8110134
#define object_return_to_variant_owner_effect_when_ready sub_8110178
#define object_stop_when_visual_complete sub_8110948
#define object_prepare_vector_setup_from_owner_state sub_81109F4
#define object_start_owner_variant_animation_11_or_12 sub_811104C
#define object_continue_owner_variant_animation_10_or_11 sub_8111174
#define object_finish_owner_variant_animation_4_or_7 sub_81111C0
#define object_on_visual_complete_spawn_effect_2669 sub_8111234
#define object_on_visual_complete_countdown_effect_2700 sub_81116C0
#define object_on_visual_complete_start_animation_4_timer_32 sub_8112030
#define object_when_timer_active_start_animation_13 sub_811213C
#define object_on_visual_complete_start_animation_13 sub_81122D0
#define object_start_state_variant_animation_1 sub_811230C
#define object_continue_when_motion_helper_clear sub_8112394
#define object_start_profile_position_animation_2 sub_8112578
#define object_complete_profile_position_animation_2 sub_81127FC
#define object_stop_animation_and_sound_11b_when_ready_variant_b sub_8112984
#define object_finish_owner_position_effect_with_spawn sub_810FD94
#define object_finish_owner_position_effect_when_ready sub_810FD54
void runtime_object_when_value80_clear_prepare_state_motion(
    struct RuntimeObject* object);
void runtime_object_clear_behavior(struct RuntimeObject* object);
u32 runtime_object_advance_vertical_to_limit(struct RuntimeObject* object);
s32 runtime_resolve_reflected_interval(s32* total, s32* lowerDistance,
                                       s32 lower, s32 upper, s32 position);
void runtime_object_start_timed_motion(struct RuntimeObject* object, s32 value, s32 duration);
void runtime_object_visual_apply_transform(
    struct RuntimeObjectVisual* visual, s32 transform);
void runtime_object_begin_owner_vector_motion(struct RuntimeObject* object);
void object_start_owner_position_effect_and_continue(
    struct RuntimeObject* object);
void object_start_owner_position_effect_variant_and_continue(
    struct RuntimeObject* object);
void object_finish_paired_owner_effect(struct RuntimeObject* object);
void object_start_owner_position_effect_with_auxiliary(
    struct RuntimeObject* object);
void object_start_owner_position_effect_to_visual_reset(
    struct RuntimeObject* object);
void object_start_fixed_position_effect_with_auxiliary(
    struct RuntimeObject* object);
void object_reset_owner_position_visual_when_ready(
    struct RuntimeObject* object);
void object_finish_owner_position_effect_with_delayed_spawn(
    struct RuntimeObject* object);
void object_start_animation_2_then_owner_offset_effect(
    struct RuntimeObject* object);
void object_start_far_owner_position_effect(struct RuntimeObject* object);
void object_countdown_then_start_paired_owner_effect(
    struct RuntimeObject* object);
void object_start_far_owner_position_effect_variant(
    struct RuntimeObject* object);
void object_return_to_auxiliary_owner_effect_when_ready(
    struct RuntimeObject* object);
void object_return_to_variant_owner_effect_when_ready(
    struct RuntimeObject* object);
void object_stop_when_visual_complete(struct RuntimeObject* object);
void object_prepare_vector_setup_from_owner_state(
    struct RuntimeObject* object);
void object_start_owner_variant_animation_11_or_12(
    struct RuntimeObject* object);
void object_continue_owner_variant_animation_10_or_11(
    struct RuntimeObject* object);
void object_finish_owner_variant_animation_4_or_7(
    struct RuntimeObject* object);
void object_on_visual_complete_spawn_effect_2669(
    struct RuntimeObject* object);
void object_on_visual_complete_countdown_effect_2700(
    struct RuntimeObject* object);
void object_on_visual_complete_start_animation_4_timer_32(
    struct RuntimeObject* object);
void object_when_timer_active_start_animation_13(
    struct RuntimeObject* object);
void object_on_visual_complete_start_animation_13(
    struct RuntimeObject* object);
void object_start_state_variant_animation_1(struct RuntimeObject* object);
s32 object_continue_when_motion_helper_clear(struct RuntimeObject* object);
void object_start_profile_position_animation_2(struct RuntimeObject* object);
void object_complete_profile_position_animation_2(struct RuntimeObject* object);
void object_stop_animation_and_sound_11b_when_ready_variant_b(
    struct RuntimeObject* object);
void object_finish_owner_position_effect_with_spawn(
    struct RuntimeObject* object);
void object_finish_owner_position_effect_when_ready(
    struct RuntimeObject* object);
s32 object_when_motion_complete_begin_downward_exit(
    struct RuntimeObject* object);
void object_clear_behavior_on_visual_complete_variant_b(
    struct RuntimeObject* object);
void object_integrate_downward_exit_until_offscreen(
    struct RuntimeObject* object);
void object_update_motion_then_notify_owner_on_flag_20(
    struct RuntimeObject* object);
void object_cleanup_state_when_unlinked(
    struct RuntimeObject* object);
s32 object_emit_effect_2adb_then_notify_owner(
    struct RuntimeObject* object, void* owner, s32 command);
s32 object_when_pair_query_clear_emit_effect_2661_and_continue(
    struct RuntimeObject* object, struct RuntimeObject* comparedObject);
s32 object_notify_owner_emit_effect_2651_and_destroy(
    struct RuntimeObject* object, void* owner, s32 command);
void object_when_value80_clear_start_owner_variant_animation_and_followup(
    struct RuntimeObject* object);
void object_select_animation_20_or_21_from_owner_variant_and_continue(
    struct RuntimeObject* object);

#endif
