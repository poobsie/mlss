#include "global.h"
#include "script/command_context.h"
#include "script/execution_state.h"

#define SEC(symbol) __attribute__((section(".text.middle." #symbol)))
#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define MISC2_SEC(symbol) \
    __attribute__((section(".text.misc_helpers_02." STRINGIFY(symbol))))
#define U32AT(pointer, offset) (*(u32*)((u8*)(pointer) + (offset)))

#define SCRIPT_STATE_SEC(symbol) \
    __attribute__((section(".text.script.state_commands." #symbol)))

extern void sub_8047E50(void*, int);
extern void sub_807C1C8(int, int);
extern s32 script_test_condition(void* context, u8 condition, u32 operand,
                                 u32 storedValue);
extern s32 sub_803C508(void* registry);
extern s32 sub_803E9F0(void* registry);
extern s32 sub_81219C4(void* registry);
extern void reset_game_80189C4(void);
extern void sub_801ADC0(void);
extern void sub_801AD80(void);
extern void sub_801AD3C(void);
extern void sub_801ABE8(u16, u16, s32);

struct ScriptSystemServiceParameters {
    u16 value00;
    u16 padding02;
    u16 value04;
    u16 padding06;
    s32 value08;
};

struct ScriptConditionalJumpArguments {
    u8 condition;
    u8 padding01[3];
    u32 operand;
    u32 storedValue;
    u32 expected;
    u32 targetCursor;
};

struct ScriptInputRuntime {
    u8 unknown00[0x78];
    u16 keyControl;
    u16 keyMaskB;
    u16 keyMaskA;
};

extern struct ScriptInputRuntime gScriptInputRuntime;

SCRIPT_STATE_SEC(script_enable_flag_2)
void script_state_enable_primary_flag_2(
    void* context, void* object, struct ScriptExecutionState* state,
    const void* arguments)
{
    state->primaryFlags |= 2;
}

#define DEFINE_SCRIPT_WAIT_HANDLER(name, predicate)                         \
    MISC2_SEC(name) s32 name(struct ScriptCommandContext* context,          \
                             struct ScriptExecutionState* state)            \
    {                                                                       \
        if ((predicate(context->objectRegistry) << 24) != 0) {              \
            state->cursor = state->resumeCursor;                            \
            return 0;                                                       \
        }                                                                   \
        return 1;                                                           \
    }

DEFINE_SCRIPT_WAIT_HANDLER(script_wait_for_primary_actor_height, sub_803C508)
DEFINE_SCRIPT_WAIT_HANDLER(script_wait_for_field_flag_291, sub_803E9F0)
DEFINE_SCRIPT_WAIT_HANDLER(script_wait_for_context_operation, sub_81219C4)

MISC2_SEC(script_command_branch_if_condition)
s32 script_command_branch_if_condition(
    void* context, struct ScriptExecutionState* state,
    const struct ScriptConditionBranchArguments* arguments)
{
    if ((script_test_condition(context, arguments->condition,
                               arguments->operand, state->storedValue)
         << 24)
        != 0) {
        state->cursor = arguments->targetCursor;
    }
    return 1;
}
MISC2_SEC(script_command_branch_if_condition)
const u16 script_command_branch_if_condition_padding = 0;

SEC(sub_80EA514) void script_state_set_secondary_channel(
    void* context, struct ScriptExecutionState* state,
    u32 value0, u32 value1, u16 flags, u8 mode)
{
    state->secondaryValue0 = value0;
    state->secondaryValue1 = value1;
    state->secondaryFlags = flags;
    state->secondaryMode = mode;
}
SEC(sub_80EA514) const u16 sub_80EA514_padding = 0;

SEC(sub_80EA530) void script_state_set_primary_channel(
    void* context, struct ScriptExecutionState* state,
    u32 value0, u32 value1, u16 flags, u8 mode)
{
    state->cursor = value0;
    state->endCursor = value1;
    state->returnCursor = 0;
    state->primaryFlags = flags;
    state->primaryMode = mode;
}
SEC(sub_80EA530) const u16 sub_80EA530_padding = 0;

SEC(sub_80EA550) void script_state_clear_secondary_channel(
    void* context, struct ScriptExecutionState* state, u32 linkedState)
{
    if (state->primaryFlags & 8)
        ((struct ScriptExecutionState*)linkedState)->primaryFlags &= ~4;
    state->secondaryValue1 = 0;
    state->secondaryValue0 = 0;
    state->secondaryMode = 0;
    state->secondaryFlags = 0;
}

SEC(sub_80EA584) void script_state_replace_secondary_channel(
    void* context, struct ScriptExecutionState* state,
    u32 value0, u32 value1, u16 flags, u8 mode)
{
    script_state_clear_secondary_channel(context, state, value0);
    script_state_set_secondary_channel(
        context, state, value0, value1, flags, mode);
}

SEC(sub_80EA5C8) void script_state_replace_primary_channel(
    void* context, struct ScriptExecutionState* state,
    u32 value0, u32 value1, u16 flags, u8 mode)
{
    script_state_clear_secondary_channel(context, state, value0);
    script_state_set_primary_channel(
        context, state, value0, value1, flags, mode);
}

SEC(sub_80EA778) void script_state_tick_wait_timer(
    void* context, struct ScriptExecutionState* state)
{
    --state->waitTimer;
    if (state->waitTimer == 0)
        state->primaryFlags &= ~0x10;
}

SEC(sub_80EA88C)
s32 script_command_call_system_service(
    void* context, void* state, const u32* arguments)
{
    u32 operation = *arguments++;

    if (operation == 0) {
        const struct ScriptSystemServiceParameters* parameters =
            (const struct ScriptSystemServiceParameters*)arguments;
        sub_801ABE8(
            parameters->value00, parameters->value04, parameters->value08);
    }
    return 1;
}

SEC(sub_80EA8A4)
s32 script_command_control_system(void* context, void* state, const s32* operation)
{
    switch (*operation) {
    case 0:
        reset_game_80189C4();
        break;
    case 1:
        sub_801ADC0();
        break;
    case 2:
        sub_801AD80();
        break;
    case 3:
        sub_801AD3C();
        break;
    }
    return 1;
}

SEC(sub_80EAB20)
s32 script_command_update_key_masks(
    void* context, void* state, const s32* arguments)
{
    s32 operation = *arguments++;

    switch (operation) {
    case 0:
        gScriptInputRuntime.keyMaskA |= *arguments;
        break;
    case 1:
        gScriptInputRuntime.keyMaskB |= *arguments;
        break;
    case 2:
        gScriptInputRuntime.keyMaskB &= ~*arguments;
        break;
    }
    return 1;
}

SEC(script_cmd_conditional_jump)
s32 script_command_conditional_jump(
    void* context, struct ScriptExecutionState* state,
    const struct ScriptConditionalJumpArguments* arguments)
{
    u8 result = script_test_condition(
        context, arguments->condition, arguments->operand, arguments->storedValue);

    if (result == arguments->expected)
        state->cursor = arguments->targetCursor;
    return 1;
}
SEC(script_cmd_conditional_jump) const u16 script_cmd_conditional_jump_padding = 0;

SEC(sub_80EA904) int script_command_pop_value(
    void* context, struct ScriptExecutionState* state)
{
    u8* depth = &state->valueStackDepth;
    --*depth;
    U32AT(state, 0x58 + *depth * sizeof(u32)) = 0;
    return 1;
}

SEC(sub_80EA91C) int script_command_store_value(
    void* context, struct ScriptExecutionState* state, const u32* argument)
{
    state->storedValue = *argument;
    return 1;
}
SEC(sub_80EA91C) const u16 sub_80EA91C_padding = 0;

SEC(sub_80EA928) int script_command_push_value(
    void* context, struct ScriptExecutionState* state, const u32* argument)
{
    u8* depth = &state->valueStackDepth;
    U32AT(state, 0x58 + *depth * sizeof(u32)) = *argument;
    ++*depth;
    return 1;
}

SEC(script_cmd_call) int script_command_call(
    void* context, struct ScriptExecutionState* state, const u32* arguments)
{
    if (arguments[0] == 1)
        state->returnCursor = state->cursor;
    state->cursor = arguments[1];
    return 1;
}
SEC(script_cmd_call) const u16 script_cmd_call_padding = 0;

SEC(script_cmd_wait_frames) int script_command_wait_frames(
    void* context, struct ScriptExecutionState* state, const u32* argument)
{
    int result;

    state->waitTimer = *argument;
    if (state->waitTimer != 0) {
        state->primaryFlags |= 0x10;
        result = 0;
    } else {
        result = 1;
    }
    return result;
}

SEC(script_cmd_end) int script_command_end(
    void* context, struct ScriptExecutionState* state)
{
    state->endCursor = state->cursor;
    state->returnCursor = 0;
    return 1;
}

SEC(sub_80F14C4) int script_command_set_current_object_configuration(
    void* context, void* object, void* state, const u16* argument)
{
    sub_8047E50(object, *argument);
    return 1;
}

SEC(sub_80F1AE4) int script_command_copy_word(
    void* context, u32* destination, const u32* argument)
{
    *destination = *argument;
    return 1;
}

SEC(sub_80F7E80) int script_command_noop(void)
{
    return 1;
}

SEC(sub_80F80B4) int script_command_forward_pair(
    void* context, void* state, const int* arguments)
{
    sub_807C1C8(arguments[0], arguments[1]);
    return 1;
}
