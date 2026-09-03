#include "global.h"
#include "script/execution_state.h"

#define SEC(symbol) __attribute__((section(".text.middle." #symbol)))
#define U32AT(pointer, offset) (*(u32*)((u8*)(pointer) + (offset)))

extern void sub_8047E50(void*, int);
extern void sub_807C1C8(int, int);

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
