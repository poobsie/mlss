#include "battle/functions.h"
#include "battle/object.h"
#include "field/linked_object.h"
#include "field/resource_loader.h"
#include "script/command_handlers.h"
#include "command_handlers_internal.h"
#include "script/command_context.h"
#include "script/execution_state.h"

#define SEC(name) __attribute__((section(".text.script_command_handlers." #name)))
#define SCRIPT_FIELD_RUNTIME (*(u8**)0x03000FD0)

extern void sub_801B0AC(u16);
extern void sub_803C898(void *, s32);
extern u8 sub_8116B48(s32, s32, s32);
extern u8 sub_811795C(s32, s32, s32);
extern void sub_8029A0C(void*, void*, s32);
extern void sub_803AC8C(void*);
extern void sub_803AAE4(void*);
extern void sub_803AE38(void*);
extern void sub_803ADA8(void*, s32);
extern void sub_802F834(void*);
extern void sub_803C638(void*);
extern void sub_803C424(void*);
extern void sub_80326F4(void*);
extern u8 sub_803C4A0(void*);
extern void sub_80328B4(void*);
extern void sub_803C8A4(void*, s32, s32);
extern void sub_8029788(void*);

struct ScriptInputRuntimePrefix {
    u8 unknown00[0x28];
    u16 mask28;
    u16 mask2A;
    u8 unknown2C[2];
    u16 activeMask;
    u8 unknown30[0x48];
    u16 keyControl;
};

extern struct ScriptInputRuntimePrefix gScriptInputRuntime;

struct ScriptInputOwner {
    u8 unknown00[4];
    u8* inputState04;
};

enum ScriptMaskMatchMode {
    SCRIPT_MASK_MATCH_MODE_MIN = -11,
    SCRIPT_MASK_MATCH_CLEAR_EXPECTED = 0,
    SCRIPT_MASK_MATCH_INVERT_EXPECTED = 1,
};

struct ScriptMaskBranchArguments {
    s32 options;
    enum ScriptMaskMatchMode matchMode;
    u32 mask;
    u32 targetCursor;
};

struct ScriptSelectedInputMaskArguments {
    s16 value;
    u16 padding02;
    u16 selector;
};

SEC(sub_80EA9B8)
s32 script_command_branch_on_active_mask(
    void* context, struct ScriptExecutionState* state,
    const struct ScriptMaskBranchArguments* arguments)
{
    register struct ScriptExecutionState* executionState asm("r6") = state;
    register const struct ScriptMaskBranchArguments* packet asm("r4") = arguments;
    register u32 activeMask asm("r5") = gScriptInputRuntime.activeMask;
    register u32 expected asm("r2") = packet->mask;
    register u32 testMask asm("r3") = expected;
    s32 normalizedMode = packet->matchMode + 11;

    switch (normalizedMode) {
    case 11:
        expected = 0;
        break;
    case 12:
        expected = ~expected;
        testMask = expected;
        break;
    }

    if (packet->options & 1) {
        testMask &= activeMask;
        if (testMask != expected)
            executionState->cursor = packet->targetCursor;
    } else {
        testMask &= activeMask;
        if (testMask == expected)
            executionState->cursor = packet->targetCursor;
    }
    return 1;
}

SEC(sub_80EAA04)
s32 script_command_branch_on_selected_mask(
    void* context, struct ScriptExecutionState* state,
    const struct ScriptMaskBranchArguments* arguments)
{
    register struct ScriptExecutionState* executionState asm("r6") = state;
    register const struct ScriptMaskBranchArguments* packet asm("r4") = arguments;
    register struct ScriptInputRuntimePrefix* inputRuntime asm("r1") =
        &gScriptInputRuntime;
    register u32 inputMask asm("r5") = inputRuntime->mask28;
    register u32 expected asm("r2");
    register u32 testMask asm("r3");
    s32 normalizedMode;

    if ((packet->options >> 1) == 0)
        inputMask = inputRuntime->mask2A;

    expected = packet->mask;
    testMask = expected;
    normalizedMode = packet->matchMode + 11;
    switch (normalizedMode) {
    case 11:
        expected = 0;
        break;
    case 12:
        expected = ~expected;
        testMask = expected;
        break;
    }

    if (packet->options & 1) {
        testMask &= inputMask;
        if (testMask != expected)
            executionState->cursor = packet->targetCursor;
    } else {
        testMask &= inputMask;
        if (testMask == expected)
            executionState->cursor = packet->targetCursor;
    }
    return 1;
}


SEC(sub_80EAA5C)
s32 script_command_forward_input_mask(
    void* context, u8* owner, const s16* argument, void* commandContext)
{
    sub_80E9C4C(commandContext, owner + 0x18, 0, 0,
                *argument, gScriptInputRuntime.activeMask);
    return 1;
}

SEC(sub_80EAA84)
s32 script_command_forward_selected_input_mask(
    void* context, u8* owner,
    const struct ScriptSelectedInputMaskArguments* arguments,
    void* commandContext)
{
    u16 mask = arguments->selector;

    if (mask == 0)
        mask = gScriptInputRuntime.mask2A;
    else if (mask == 1)
        mask = gScriptInputRuntime.mask28;
    else
        mask = 0;
    sub_80E9C4C(commandContext, owner + 0x18, 0, 0,
                arguments->value, mask);
    return 1;
}

SEC(script_cmd_wait_for_user_input)
s32 script_command_wait_for_user_input(
    void* context, struct ScriptInputOwner* owner,
    struct ScriptExecutionState* state, const u32* bit)
{
    if ((owner->inputState04[0x1B4] >> *bit) & 1) {
        state->cursor = state->resumeCursor;
        return 0;
    }
    return 1;
}
SEC(script_cmd_wait_for_user_input)
const u16 script_cmd_wait_for_user_input_padding = 0;
SEC(script_command_set_input_mask) s32 script_command_set_input_mask(
    struct ScriptCommandContext* context, void* state, u16* arguments)
{
    sub_801B0AC(*arguments);
    return 1;
}
SEC(script_command_set_input_mask) const u16 script_command_set_input_mask_padding = 0;

SEC(sub_80F0540)
s32 script_command_clear_field_runtime_flag(
    void* context, void* owner, void* state, const u32* arguments)
{
    u32 operation = *arguments++;

    if (operation == 0) {
        /* The owner and meaning of this 16-bit field flag bank remain unknown. */
        u16* flags = (u16*)(SCRIPT_FIELD_RUNTIME + 0x54A);
        *flags &= ~(1 << *arguments);
    }
    return 1;
}

SEC(sub_80F0780) s32 sub_80F0780(struct ScriptCommandContext* context, void* state, s32* arguments)
{
    s32 index = *arguments;
    if (index != 5)
        sub_803C898(context->objectRegistry, index);
    return 1;
}

SEC(sub_80F0794)
s32 script_command_dispatch_field_object_operation(
    struct ScriptCommandContext* context, void* state, const s32* argument)
{
    /* Values 5 through 11 select object-registry operations. Their meanings remain unknown. */
    s32 command = *argument;

    switch (command) {
    case 5:
        sub_803AC8C(context->objectRegistry);
        break;
    case 6:
        sub_803AAE4(context->objectRegistry);
        break;
    case 7:
        sub_803AE38(context->objectRegistry);
        break;
    case 8:
        sub_803ADA8(context->objectRegistry, 1);
        break;
    case 9:
        sub_802F834(context->objectRegistry);
        break;
    case 10:
        sub_803C638(context->objectRegistry);
        break;
    case 11:
        sub_803C424(context->objectRegistry);
        break;
    default:
        sub_8029A0C(context->objectRegistry, (void*)command, 0);
        break;
    }
    return 1;
}

SEC(sub_80F0814)
s32 script_command_dispatch_field_object_control(
    struct ScriptCommandContext* context, struct ScriptExecutionState* state,
    const s32* argument)
{
    /* The packed low-bit/group command encoding is proven; operation names are not. */
    s32 command = *argument;
    s32 group = (command >> 1) & 0xF;
    s32 result;

    switch (group) {
    case 0:
        switch (command & 1) {
        case 0:
            sub_80326F4(context->objectRegistry);
            break;
        case 1:
            result = sub_803C4A0(context->objectRegistry);
            if ((result << 24) != 0) {
                state->cursor = state->resumeCursor;
                return 0;
            }
            break;
        }
        break;
    case 1:
        switch (group & command) {
        case 0:
            sub_80328B4(context->objectRegistry);
            break;
        case 1:
            result = field_linked_object_check_state_2a_2b(
                (struct FieldLinkedObjectOwner*)context->objectRegistry);
            if ((result << 24) != 0) {
                state->cursor = state->resumeCursor;
                return 0;
            }
            break;
        }
        break;
    }
    return 1;
}
SEC(sub_80F0814) const u16 sub_80F0814_padding = 0;

SEC(sub_80F08C0)
s32 script_command_branch_on_field_queries(
    void* context, struct ScriptExecutionState* state,
    const u32* arguments)
{
    u8 result = sub_8116B48(0, 3, 0);

    if (result == 0) {
        result = sub_811795C(0, 0, 1);
        if (result == 0)
            result = sub_811795C(1, 0, 1);
    }

    if ((result == 0) == *arguments++)
        state->cursor = *arguments;
    return 1;
}
SEC(sub_80F08C0) const u16 sub_80F08C0_padding = 0;

SEC(sub_80F06EC)
s32 script_command_initialize_field_registry(
    struct ScriptCommandContext* context, void* state, const s32* operation)
{
    if (*operation == 0)
        field_release_inline_resource_objects(
            (struct FieldObjectResourceRuntime*)context->objectRegistry);
    return 1;
}
SEC(sub_80F06EC) const u16 sub_80F06EC_padding = 0;

SEC(sub_80F0744)
s32 script_command_control_field_registry(
    struct ScriptCommandContext* context, void* state, const s32* arguments)
{
    s32 operation = *arguments++;

    switch (operation) {
    case 0:
        sub_803C8A4(context->objectRegistry, *arguments, 0);
        break;
    case 1:
        battle_release_resource_when_mode_zero(
            (struct BattleResourceControlObject*)context->objectRegistry, 0);
        break;
    case 2:
        sub_8029788(context->objectRegistry);
        break;
    }
    return 1;
}
SEC(sub_80F0744) const u16 sub_80F0744_padding = 0;
