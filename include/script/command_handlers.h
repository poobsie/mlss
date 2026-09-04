#ifndef GUARD_SCRIPT_COMMAND_HANDLERS_H
#define GUARD_SCRIPT_COMMAND_HANDLERS_H

#include "global.h"

struct ScriptBattleReturnContext;
struct ScriptExecutionState;
struct ScriptCommandContext;
struct ScriptInputOwner;
struct ScriptEffectArguments;
struct ScriptSelectedRuntimeArguments;

#define script_command_return_from_battle script_cmd_btl_return
#define script_command_set_runtime_direction_sign sub_80EAD98
#define script_command_branch_if_runtime_byte_30_equals sub_80EAE9C
#define script_command_set_runtime_byte_32 sub_80EB048
#define script_command_control_sound_effect sub_80EAEF8
#define script_command_set_sound_effect_volume sub_80EAEE0
#define script_command_control_music sub_80EAF4C
#define script_command_control_resource_wait sub_80EB05C
#define script_command_configure_graphics_resource sub_80EB09C
#define script_command_wait_for_user_input script_cmd_wait_for_user_input
#define script_command_clear_field_runtime_flag sub_80F0540
#define script_command_initialize_field_registry sub_80F06EC
#define script_command_control_field_registry sub_80F0744
#define script_command_dispatch_field_object_operation sub_80F0794
#define script_command_dispatch_field_object_control sub_80F0814
#define script_command_branch_on_field_queries sub_80F08C0
#define script_wait_for_battle_flag_208_10 sub_80F087C
#define script_command_set_battle_flag_12d sub_80F0914
#define script_command_set_battle_flags_12c sub_80F0938
#define script_command_control_battle_registry sub_80F095C
#define script_wait_for_battle_control_ready sub_80F0984
#define script_command_apply_flagged_effects sub_80F1088
#define script_command_branch_on_indexed_object_state sub_80F10E0
#define script_command_branch_on_object_state sub_80F110C
#define script_command_control_object_motion sub_80F112C
#define script_command_control_indexed_object_runtime sub_80F143C
#define script_command_control_object_runtime sub_80F1490
#define script_command_control_object_pair sub_80F1A1C
#define script_command_branch_on_field_value_54c sub_80F1AEC
#define script_command_dispatch_selected_runtime sub_80F1B14
#define script_command_branch_on_selected_runtime_flag sub_80F1BA4
#define script_command_configure_object_slot_183 sub_80F0BA4

u8 script_command_return_from_battle(
    struct ScriptBattleReturnContext* context,
    struct ScriptExecutionState* state,
    s32* shouldMarkReturn);

s32 script_command_set_runtime_direction_sign(
    void* context, void* state, const u32* argument);
s32 script_command_branch_if_runtime_byte_30_equals(
    void* context, struct ScriptExecutionState* state,
    const u32* arguments);
s32 script_command_set_runtime_byte_32(
    void* context, void* state, const u32* argument);
s32 script_command_set_sound_effect_volume(
    void* context, void* state, const u32* arguments);
s32 script_command_wait_for_user_input(
    void* context, struct ScriptInputOwner* owner,
    struct ScriptExecutionState* state,
    const u32* bit);
s32 script_command_clear_field_runtime_flag(
    void* context, void* owner, void* state, const u32* arguments);
s32 script_command_initialize_field_registry(
    struct ScriptCommandContext* context, void* state,
    const s32* operation);
s32 script_command_control_field_registry(
    struct ScriptCommandContext* context, void* state,
    const s32* arguments);
s32 script_command_dispatch_field_object_operation(
    struct ScriptCommandContext* context, void* state,
    const s32* argument);
s32 script_command_dispatch_field_object_control(
    struct ScriptCommandContext* context,
    struct ScriptExecutionState* state, const s32* argument);
s32 script_command_branch_on_field_queries(
    void* context, struct ScriptExecutionState* state,
    const u32* arguments);

s32 script_wait_for_battle_flag_208_10(
    struct ScriptCommandContext* context,
    struct ScriptExecutionState* state);
s32 script_command_set_battle_flag_12d(
    struct ScriptCommandContext* context, void* state,
    const u32* operation);
s32 script_command_set_battle_flags_12c(
    struct ScriptCommandContext* context, void* state,
    const s32* mode);
s32 script_command_control_battle_registry(
    struct ScriptCommandContext* context, void* state,
    const s32* operation);
s32 script_wait_for_battle_control_ready(
    struct ScriptCommandContext* context,
    struct ScriptExecutionState* state);
s32 script_command_apply_flagged_effects(
    void* context, void* object, void* state,
    const struct ScriptEffectArguments* arguments);
s32 script_command_branch_on_indexed_object_state(
    struct ScriptCommandContext* context,
    struct ScriptExecutionState* state, const u32* arguments);
s32 script_command_branch_on_object_state(
    void* context, void* object, struct ScriptExecutionState* state,
    const u32* arguments);
s32 script_command_control_object_motion(
    void* context, void* object, struct ScriptExecutionState* state,
    s32* arguments);
s32 script_command_control_indexed_object_runtime(
    struct ScriptCommandContext* context, void* state,
    const s32* arguments);
s32 script_command_control_object_runtime(
    void* context, void* runtime, void* state,
    const s32* operation);
s32 script_command_control_object_pair(
    void* context, void* object, void* state,
    const s32* operation);
s32 script_command_branch_on_field_value_54c(
    void* context, struct ScriptExecutionState* state,
    const u32* arguments);
s32 script_command_dispatch_selected_runtime(
    void* context, u8* object,
    const struct ScriptSelectedRuntimeArguments* packet,
    void* commandContext);
s32 script_command_branch_on_selected_runtime_flag(
    void* context, struct ScriptExecutionState* state,
    const s32* arguments);

#endif
