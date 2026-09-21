#include "runtime/random.h"
#include "script/command_handlers.h"
#include "command_handlers_internal.h"
#include "script/execution_state.h"
#include "script/runtime_slots.h"

#define SEC(name) __attribute__((section(".text.script_command_handlers." #name)))
#define SCRIPT_GLOBAL_D44 (*(void**)0x03000D44)
#define SCRIPT_GLOBAL_FB8 (*(void**)0x03000FB8)
#define U8AT(pointer, offset) (*(u8*)((u8*)(pointer) + (offset)))

extern void sub_801BBE4(void*, s8, s8, s8);

struct ScriptBridgeOwner {
    u8 unknown00[0x18];
    u8 bridgeDestination18;
};

struct ScriptRandomForwardArguments {
    s16 bridgeValue;
    u16 padding02;
    u32 upperBound;
};

struct ScriptRuntimeSignedTripletArguments {
    s8 value0;
    u8 padding01[3];
    s8 value1;
    u8 padding05[3];
    s8 value2;
};

struct ScriptSelectedRuntimeByteArguments {
    s16 value;
    u16 padding02;
    s32 byteSelector;
};

struct ScriptArithmeticBridgeArguments {
    s16 value;
    u16 padding02;
    u32 operation;
    s32 result;
    s32 operand;
};

SEC(sub_80EA968)
s32 script_command_forward_bounded_random(
    void* context, struct ScriptBridgeOwner* owner,
    const struct ScriptRandomForwardArguments* arguments,
    void* commandContext)
{
    s32 value = runtime_scale_random_u32(
        arguments->upperBound, runtime_random_u32());

    sub_80E9C4C(
        commandContext, &owner->bridgeDestination18, 0, 0,
        arguments->bridgeValue, value);
    return 1;
}

SEC(sub_80EAB98)
s32 script_command_apply_arithmetic_and_forward(
    void* context, u8* owner,
    struct ScriptArithmeticBridgeArguments* arguments,
    void* commandContext, void* bridgeArgument2, s32 bridgeArgument3)
{
    switch (arguments->operation) {
    case 0: break;
    case 1: arguments->result += arguments->operand; break;
    case 2: arguments->result -= arguments->operand; break;
    case 3: arguments->result *= arguments->operand; break;
    case 4: arguments->result /= arguments->operand; break;
    case 5: arguments->result %= arguments->operand; break;
    case 6: arguments->result <<= arguments->operand; break;
    case 7: arguments->result >>= arguments->operand; break;
    case 8: arguments->result &= arguments->operand; break;
    case 9: arguments->result |= arguments->operand; break;
    case 10: arguments->result ^= arguments->operand; break;
    case 11: arguments->result = !arguments->result; break;
    case 12: arguments->result = ~arguments->result; break;
    }
    sub_80E9C4C(commandContext, owner + 0x18,
                bridgeArgument2, bridgeArgument3,
                arguments->value, arguments->result);
    return 1;
}
SEC(sub_80EAB98) const u16 script_command_apply_arithmetic_and_forward_padding = 0;

SEC(sub_80EACDC)
s32 script_command_forward_selected_runtime_byte(
    void* context, u8* owner,
    const struct ScriptSelectedRuntimeByteArguments* arguments,
    void* commandContext)
{
    switch (arguments->byteSelector) {
    case 0:
        sub_80E9C4C(commandContext, owner + 0x18, 0, 0,
                    arguments->value, (s8)U8AT(SCRIPT_GLOBAL_D44, 0x22));
        break;
    case 1:
        sub_80E9C4C(commandContext, owner + 0x18, 0, 0,
                    arguments->value, (s8)U8AT(SCRIPT_GLOBAL_D44, 0x23));
        break;
    case 2:
        sub_80E9C4C(commandContext, owner + 0x18, 0, 0,
                    arguments->value, (s8)U8AT(SCRIPT_GLOBAL_D44, 0x25));
        break;
    case 3:
        sub_80E9C4C(commandContext, owner + 0x18, 0, 0,
                    arguments->value, (s8)U8AT(SCRIPT_GLOBAL_D44, 0x24));
        break;
    }
    return 1;
}

SEC(sub_80EADC4)
s32 script_command_apply_runtime_signed_triplet(
    void* context, void* state,
    const struct ScriptRuntimeSignedTripletArguments* arguments)
{
    sub_801BBE4(SCRIPT_GLOBAL_D44,
                arguments->value0, arguments->value1, arguments->value2);
    return 1;
}

SEC(sub_80EADEC)
s32 script_command_wait_for_runtime_slot(
    void* context, struct ScriptRuntimeSlotOwner* owner,
    struct ScriptExecutionState* state, const u32* identifier)
{
    s16 slot = 0;
    struct ScriptRuntimeSlot* entry = owner->slots;

    while (slot <= 3) {
        if (entry->active &&
            (entry->identifier == *identifier || *identifier == 0x3F)) {
            state->cursor = state->resumeCursor;
            return 0;
        }
        slot++;
        entry++;
    }
    return 1;
}
SEC(sub_80EADEC) const u16 script_command_wait_for_runtime_slot_padding = 0;

SEC(sub_80EAE30)
s32 script_command_dispatch_runtime_slot(
    void* context, struct ScriptRuntimeSlotOwner* owner,
    void* state, const u32* identifier)
{
    s16 slot = 0;
    struct ScriptRuntimeSlot* entry = owner->slots;

    while (slot <= 3) {
        if (entry->active && entry->identifier == *identifier) {
            script_runtime_slot_hide(owner, (u8)slot);
            break;
        }
        slot++;
        entry++;
    }
    return 1;
}

SEC(sub_80EAE70)
s32 script_command_forward_runtime_byte_30(
    void* context, u8* owner, const s16* argument, void* commandContext)
{
    sub_80E9C4C(commandContext, owner + 0x18, 0, 0,
                *argument, U8AT(SCRIPT_GLOBAL_FB8, 0x30));
    return 1;
}

SEC(sub_80EAD98)
s32 script_command_set_runtime_direction_sign(
    void* context, void* state, const u32* argument)
{
    if (*argument == 0)
        U8AT(SCRIPT_GLOBAL_D44, 0x29) = 1;
    else
        U8AT(SCRIPT_GLOBAL_D44, 0x29) = 0xFF;
    return 1;
}

SEC(sub_80EAE9C)
s32 script_command_branch_if_runtime_byte_30_equals(
    void* context, struct ScriptExecutionState* state,
    const u32* arguments)
{
    if (U8AT(SCRIPT_GLOBAL_FB8, 0x30) == arguments[0])
        state->cursor = arguments[1];
    return 1;
}

SEC(sub_80EB048)
s32 script_command_set_runtime_byte_32(
    void* context, void* state, const u32* argument)
{
    u8* runtime = SCRIPT_GLOBAL_FB8;
    u32 value = *argument;

    U8AT(runtime, 0x32) = value;
    return 1;
}
