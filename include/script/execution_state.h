#ifndef GUARD_SCRIPT_EXECUTION_STATE_H
#define GUARD_SCRIPT_EXECUTION_STATE_H

#include "global.h"

enum {
    SCRIPT_VALUE_STACK_CAPACITY = 16,
};

/*
 * State shared by the command handlers around 0x080EA514-0x080EB248.
 * The two value channels are structurally proven, but their gameplay units are not.
 */
struct ScriptExecutionState {
    u32 cursor;
    u32 endCursor;
    u32 secondaryValue0;
    u32 secondaryValue1;
    u32 returnCursor;
    u32 resumeCursor;
    u8 unknown18[0x40];
    u32 valueStack[SCRIPT_VALUE_STACK_CAPACITY];
    u32 storedValue;
    u32 waitTimer;
    u16 primaryFlags;
    u16 secondaryFlags;
    u8 primaryMode;
    u8 secondaryMode;
    u8 valueStackDepth;
    u8 unknownA7;
};

struct ScriptConditionBranchArguments {
    u8 condition;
    u8 padding01[3];
    u32 operand;
    u32 targetCursor;
};

#define script_state_set_secondary_channel sub_80EA514
#define script_state_set_primary_channel sub_80EA530
#define script_command_pop_value sub_80EA904
#define script_command_store_value sub_80EA91C
#define script_command_push_value sub_80EA928
#define script_command_branch_if_condition sub_80EA8DC
#define script_wait_for_primary_actor_height sub_80F0704
#define script_wait_for_field_flag_291 sub_80F0724
#define script_wait_for_context_operation sub_80FA6BC
#define script_command_call script_cmd_call
#define script_command_end script_cmd_end
#define script_command_set_current_object_configuration sub_80F14C4
#define script_command_copy_word sub_80F1AE4
#define script_command_noop sub_80F7E80
#define script_command_forward_pair sub_80F80B4

#endif
