#ifndef GUARD_SCRIPT_COMMAND_HANDLERS_H
#define GUARD_SCRIPT_COMMAND_HANDLERS_H

#include "global.h"

struct ScriptBattleReturnContext;
struct ScriptExecutionState;
struct ScriptCommandContext;

#define script_command_return_from_battle script_cmd_btl_return
#define script_wait_for_battle_flag_208_10 sub_80F087C
#define script_command_set_battle_flag_12d sub_80F0914
#define script_command_set_battle_flags_12c sub_80F0938
#define script_wait_for_battle_control_ready sub_80F0984
#define script_command_configure_object_slot_183 sub_80F0BA4

u8 script_command_return_from_battle(
    struct ScriptBattleReturnContext* context,
    struct ScriptExecutionState* state,
    s32* shouldMarkReturn);

s32 script_wait_for_battle_flag_208_10(
    struct ScriptCommandContext* context,
    struct ScriptExecutionState* state);
s32 script_command_set_battle_flag_12d(
    struct ScriptCommandContext* context, void* state,
    const u32* operation);
s32 script_command_set_battle_flags_12c(
    struct ScriptCommandContext* context, void* state,
    const s32* mode);
s32 script_wait_for_battle_control_ready(
    struct ScriptCommandContext* context,
    struct ScriptExecutionState* state);

#endif
