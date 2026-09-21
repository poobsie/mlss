#include "battle/functions.h"
#include "battle/object.h"
#include "field/resource_loader.h"
#include "field/selection_sequence.h"
#include "script/command_handlers.h"
#include "command_handlers_internal.h"
#include "script/command_context.h"
#include "script/execution_state.h"

#define SEC(name) __attribute__((section(".text.script_command_handlers." #name)))
#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define MISC3_SEC(name) \
    __attribute__((section(".text.misc_helpers_03." STRINGIFY(name))))
#define FIELD_RUNTIME (*(struct FieldSelectionRuntime**)0x03000FD8)

struct ScriptBattleReturnContext {
    u8 unknown00[0x1C];
};

/* The command stream supplies a position descriptor followed by effect data.
 * Only the flag word and effect value are identified by this handler. */
struct ScriptBattleCommandArguments {
    s32 positionMode;
    s32 unknown04;
    s32 unknown08;
    s32 effectFlags;
    s32 effectValue;
};

extern void sub_80EA6D4(
    void* context, const void* arguments, s32* value0, s32* value1,
    s32* value2);
extern void sub_80F6AC0(void* context, u8 playerIndex, s32 value, s32 mirror);
extern void sub_80F76FC(
    u8 playerIndex, s32 x, s32 y, s32 z, s32 copyPosition);
extern void sub_80F7644(u8 playerIndex, s32 copyPosition);
extern u8 sub_8027378(void* objectRegistry);

MISC3_SEC(script_command_return_from_battle)
u8 script_command_return_from_battle(
    struct ScriptBattleReturnContext* context,
    struct ScriptExecutionState* state,
    s32* shouldMarkReturn)
{
    struct FieldSelectionRuntime* runtime;
    u8 flags;
    s32 battleReturnMask;

    if (*shouldMarkReturn != 0) {
        runtime = FIELD_RUNTIME;
        flags = runtime->flags2BF;
        battleReturnMask = 2;
        runtime->flags2BF = (u8)(flags | battleReturnMask);
    }
    return script_cmd_return((u8*)context + sizeof(*context), state);
}

SEC(sub_80F087C)
s32 script_wait_for_battle_flag_208_10(
    struct ScriptCommandContext* context,
    struct ScriptExecutionState* state)
{
    s32 result;

    if (((u8*)context->objectRegistry)[0x208] & 0x10) {
        result = 1;
    } else {
        state->cursor = state->resumeCursor;
        result = 0;
    }
    return result;
}

SEC(sub_80F0914)
s32 script_command_set_battle_flag_12d(
    struct ScriptCommandContext* context, void* state,
    const u32* operation)
{
    switch (*operation) {
    case 0:
        battle_set_flag_12d_10(
            (struct BattleControlObject*)context->objectRegistry);
        break;
    case 1:
        battle_set_flag_12d_20(
            (struct BattleControlObject*)context->objectRegistry);
        break;
    }
    return 1;
}
SEC(sub_80F0914) const u16 sub_80F0914_padding = 0;

SEC(sub_80F0938)
s32 script_command_set_battle_flags_12c(
    struct ScriptCommandContext* context, void* state,
    const s32* mode)
{
    if (*mode != -32)
        battle_set_flags_12c_mode(
            (struct BattleControlObject*)context->objectRegistry, *mode);
    else
        battle_set_flag_12c_01(
            (struct BattleControlObject*)context->objectRegistry);
    return 0;
}
SEC(sub_80F0938) const u16 sub_80F0938_padding = 0;

SEC(sub_80F0984)
s32 script_wait_for_battle_control_ready(
    struct ScriptCommandContext* context,
    struct ScriptExecutionState* state)
{
    u8 result = sub_8027378(context->objectRegistry);
    if (result == 1) {
        state->cursor = state->resumeCursor;
        return 0;
    }
    return 1;
}
SEC(sub_80F0984) const u16 sub_80F0984_padding = 0;

SEC(sub_80F095C)
s32 script_command_control_battle_registry(
    struct ScriptCommandContext* context, void* state, const s32* operation)
{
    switch (*operation) {
    case 0:
    case 1:
        field_apply_value_transfer_operation_and_advance_phase(
            (struct FieldObjectResourceRuntime*)context->objectRegistry,
            *operation);
        break;
    case 2:
        field_advance_value_transfer_for_mode_1_or_2(
            (struct FieldObjectResourceRuntime*)context->objectRegistry);
        break;
    }
    return 1;
}
SEC(sub_80F095C) const u16 sub_80F095C_padding = 0;

SEC(sub_80F8740)
s32 script_command_start_battle_command_effect(
    struct ScriptObjectSelectionContext* context,
    struct ScriptExecutionState* state,
    const struct ScriptBattleCommandArguments* arguments)
{
    s32 value0;
    s32 value1;
    s32 value2;
    s32 effectValue;
    s32 mirror;
    u8 temp_r0;
    u8 temp_r5;
    u8 var_r0;

    temp_r0 = context->fieldState2C[0x179C];
    if (temp_r0 <= 6)
        var_r0 = temp_r0 - 1;
    else
        var_r0 = temp_r0 - 7;
    temp_r5 = var_r0;

    sub_80EA6D4(
        (u8*)context + 0x1C, arguments, &value0, &value1, &value2);
    effectValue = arguments->effectValue;
    mirror = 0;
    if ((arguments->effectFlags & 3) == 1)
        mirror = 1;
    sub_80F6AC0(context, temp_r5, effectValue, mirror);
    sub_80F76FC(temp_r5, value0, value1, value2, 0);
    sub_80F7644(temp_r5, 1);
    state->primaryFlags |= 2;
    return 0;
}
SEC(sub_80F8740) const u16 sub_80F8740_padding = 0;
