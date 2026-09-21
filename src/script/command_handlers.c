#include "global.h"
#include "field/global_object_transitions.h"
#include "graphics/process_state.h"
#include "script/command_handlers.h"
#include "command_handlers_internal.h"
#include "script/command_context.h"
#include "script/execution_state.h"

#define SEC(name) __attribute__((section(".text.script_command_handlers." #name)))
#define SCRIPT_FIELD_RUNTIME (*(u8**)0x03000FD0)
#define SCRIPT_GLOBAL_FC0 (*(u8**)0x03000FC0)
struct ScriptFieldRuntimeModeState {
    u8 unknown000[0x55F];
    u8 modeFlags55F;
};
#define SCRIPT_FIELD_MODE_RUNTIME \
    (*(struct ScriptFieldRuntimeModeState**)0x03000FD0)

SEC(sub_80F0B80)
s32 script_command_select_runtime_mode_20(
    struct ScriptCommandContext* context, void* state, const void* arguments)
{
    u8 flags = SCRIPT_FIELD_MODE_RUNTIME->modeFlags55F;
    s32 clearMask = 0x61;

    (void)context;
    (void)state;
    (void)arguments;
    clearMask = -clearMask;
    clearMask &= flags;
    clearMask |= 0x20;
    SCRIPT_FIELD_MODE_RUNTIME->modeFlags55F = clearMask;
    return 1;
}

struct ScriptObjectSelectionArguments {
    s16 bridgeValue;
    u16 padding02;
    s32 selectionMode;
    s32 threshold;
};

struct ScriptObjectPropertyArguments {
    s16 bridgeValue;
    s16 padding02;
    s16 objectIndex;
    s16 padding06;
    s32 propertySelector;
};

/* The command stream supplies a position descriptor followed by effect data.
 * Only the flag word and effect value are identified by this handler. */

extern void sub_805B490(void *, u16);
extern void sub_805B618(void *, u16);
extern void sub_8047E50(void *, u16);
extern void sub_8047364(void *, u8);
extern void sub_80473DC(void *);
extern void sub_8046A90(void*, s32, s32, s16, u16);
extern void sub_8046B30(void*, s32, s32, s16, u16);
extern void sub_8047D84(void*, s32);
extern void sub_8047D64(void*);
extern void sub_8047D44(void*);
extern void sub_805113C(void*);
extern void sub_8050FD0(void*);
extern s32 sub_80F7868(void* context, s32 threshold);
extern s32 sub_80F78C4(void* context, s32 threshold);
extern s32 sub_80F6B44(void* context, s16 objectIndex, s32 propertySelector);
extern void sub_8047B08(void*, s32, s32);
extern void sub_8047B5C(void*, s16);
extern void sub_8046A10(void*);

struct ScriptObjectBytePairArguments {
    u8 value0;
    u8 padding01[3];
    u8 value1;
};

struct ScriptEffectArguments {
    /* Bits 0-3 select direction, mode, and the two operations; higher bits are unknown. */
    s32 flags;
    s16 value04;
    u16 padding06;
    u16 value08;
};

struct ScriptSelectedRuntimeArguments {
    s16 value00;
    u16 padding02;
    s32 runtimeSelector;
};

SEC(sub_80F0BA4)
s32 script_command_configure_object_slot_183(
    struct ScriptCommandContext* context, void* state,
    const struct ScriptObjectBytePairArguments* arguments)
{
    sub_805C78C(
        context->objectRegistry->objects[SCRIPT_OBJECT_SLOT_183],
        arguments->value0, arguments->value1);
    return 1;
}
SEC(sub_80F0BA4) const u16 sub_80F0BA4_padding = 0;

#define DEFINE_OBJECT_COMMAND(name, argument_type, action, result)      \
    SEC(name) s32 name(struct ScriptCommandContext* context, void* state, argument_type* arguments) \
    {                                                                    \
        void* object = context->objectRegistry->objects[SCRIPT_OBJECT_SLOT_183]; \
        action(object, *arguments);                                     \
        return result;                                                   \
    }

DEFINE_OBJECT_COMMAND(
    sub_80F0BC0, u8, graphics_initialize_resource_entry_index, 1)
DEFINE_OBJECT_COMMAND(sub_80F0BD8, u16, sub_805B490, 0)
DEFINE_OBJECT_COMMAND(sub_80F0BF0, u16, sub_805B618, 0)

#define DEFINE_INDEXED_COMMAND(name, argument_type, action)             \
    SEC(name) s32 name(struct ScriptCommandContext* context, void* state, u32* arguments) \
    {                                                                    \
        u32 index = *arguments++;                                       \
        void* object = SCRIPT_OBJECT_AT(context->objectRegistry, index); \
        action(object, *(argument_type *)arguments);                    \
        return 1;                                                        \
    }

DEFINE_INDEXED_COMMAND(script_command_set_object_configuration, u16, sub_8047E50)
DEFINE_INDEXED_COMMAND(script_command_set_object_mode, u8, sub_8047364)

SEC(script_command_advance_object_mode) s32 script_command_advance_object_mode(
    struct ScriptCommandContext* context, void* state, u32* arguments)
{
    u32 index = *arguments;
    void* object = SCRIPT_OBJECT_AT(context->objectRegistry, index);
    sub_80473DC(object);
    return 1;
}
SEC(script_command_advance_object_mode) const u16 script_command_advance_object_mode_padding = 0;

SEC(sub_80F1088)
s32 script_command_apply_flagged_effects(
    void* context, void* object, void* state,
    const struct ScriptEffectArguments* arguments)
{
    if (arguments->flags & 4)
        sub_8046A90(
            object, ((arguments->flags >> 1) & 1) + 1,
            arguments->flags & 1, arguments->value04, arguments->value08);
    if (arguments->flags & 8)
        sub_8046B30(
            object, ((arguments->flags >> 1) & 1) + 1,
            arguments->flags & 1, arguments->value04, arguments->value08);
    return 1;
}
SEC(sub_80F1088) const u16 sub_80F1088_padding = 0;

SEC(sub_80F10E0)
s32 script_command_branch_on_indexed_object_state(
    struct ScriptCommandContext* context, struct ScriptExecutionState* state,
    const u32* arguments)
{
    u32 index = *arguments++;
    void* object = SCRIPT_OBJECT_AT(context->objectRegistry, index);
    u32 result = (u32)~*(s32*)((u8*)object + 0x25C) >> 31;
    u32 expected = *arguments++;

    if (result == expected)
        state->cursor = *arguments;
    return 1;
}
SEC(sub_80F10E0) const u16 sub_80F10E0_padding = 0;

SEC(sub_80F110C)
s32 script_command_branch_on_object_state(
    void* context, void* object, struct ScriptExecutionState* state,
    const u32* arguments)
{
    u32 result = (u32)~*(s32*)((u8*)object + 0x25C) >> 31;
    u32 expected = *arguments++;

    if (result == expected)
        state->cursor = *arguments;
    return 1;
}
SEC(sub_80F110C) const u16 sub_80F110C_padding = 0;

SEC(sub_80F143C)
s32 script_command_control_indexed_object_runtime(
    struct ScriptCommandContext* context, void* state, const s32* arguments)
{
    s32 index = *arguments++;
    void* runtime = SCRIPT_OBJECT_AT(context->objectRegistry, index);

    switch (*arguments) {
    case 0:
        sub_8047D84(runtime, 1);
        break;
    case 1:
        sub_8047D64(runtime);
        break;
    case 2:
        sub_8047D44(runtime);
        break;
    }
    return 1;
}
SEC(sub_80F143C) const u16 sub_80F143C_padding = 0;

SEC(sub_80F1490)
s32 script_command_control_object_runtime(
    void* context, void* runtime, void* state, const s32* operation)
{
    switch (*operation) {
    case 0:
        sub_8047D84(runtime, 1);
        break;
    case 1:
        sub_8047D64(runtime);
        break;
    case 2:
        sub_8047D44(runtime);
        break;
    }
    return 1;
}
SEC(sub_80F1490) const u16 sub_80F1490_padding = 0;

SEC(sub_80F1A1C)
s32 script_command_control_object_pair(
    void* context, void* object, void* state, const s32* operation)
{
    switch (*operation) {
    case 0:
        sub_805113C(object);
        break;
    case 1:
        sub_8050FD0(object);
        break;
    }
    return 1;
}

SEC(sub_80F1AEC)
s32 script_command_branch_on_field_value_54c(
    void* context, struct ScriptExecutionState* state,
    const u32* arguments)
{
    u16 fieldValue = *(u16*)(SCRIPT_FIELD_RUNTIME + 0x54C);
    u32 expected = *arguments++;

    if (fieldValue == expected)
        state->cursor = *arguments;
    return 1;
}

SEC(sub_80F1B14)
s32 script_command_dispatch_selected_runtime(
    void* context, u8* object, const struct ScriptSelectedRuntimeArguments* packet,
    void* commandContext)
{
    u8* runtime;

    /* Selector identities are unknown; their field-runtime offsets are proven. */
    switch (packet->runtimeSelector) {
    case 0:
        runtime = SCRIPT_FIELD_RUNTIME;
        break;
    case 1:
        runtime = SCRIPT_FIELD_RUNTIME + 0x1F8;
        break;
    case 2:
        runtime = SCRIPT_FIELD_RUNTIME + 0xA8;
        break;
    case 3:
        runtime = SCRIPT_FIELD_RUNTIME + 0x150;
        break;
    }
    sub_80E9C4C(
        commandContext, object + 0x18, SCRIPT_GLOBAL_FC0 + 0x38C, 0,
        packet->value00, *(u16*)(runtime + 0xA0) & 1);
    return 1;
}

SEC(sub_80F1BA4)
s32 script_command_branch_on_selected_runtime_flag(
    void* context, struct ScriptExecutionState* state, const s32* arguments)
{
    s32 runtimeSelector = *arguments++;
    u8* runtime;

    /* Uses the same four field-runtime regions as sub_80F1B14. */
    switch (runtimeSelector) {
    case 0:
        runtime = SCRIPT_FIELD_RUNTIME;
        break;
    case 1:
        runtime = SCRIPT_FIELD_RUNTIME + 0x1F8;
        break;
    case 2:
        runtime = SCRIPT_FIELD_RUNTIME + 0xA8;
        break;
    case 3:
        runtime = SCRIPT_FIELD_RUNTIME + 0x150;
        break;
    }
    if (*(u16*)(runtime + 0xA0) & 1)
        state->cursor = *arguments;
    return 1;
}

SEC(sub_80F8438)
s32 script_command_forward_selected_object_index(
    struct ScriptObjectSelectionContext* context, u8* owner,
    const struct ScriptObjectSelectionArguments* arguments,
    void* commandContext)
{
    s32 selectedIndex;

    switch (arguments->selectionMode) {
    case 0:
        selectedIndex = sub_80F78C4(context, arguments->threshold);
        break;
    case 1:
        selectedIndex = sub_80F7868(context, arguments->threshold);
        break;
    case 2:
        selectedIndex = field_find_object_with_largest_value_span(
            context, arguments->threshold);
        break;
    }

    sub_80E9C4C(
        commandContext, owner + 0x18, context->fieldState2C + 0x1794,
        (s32)(owner + 0xA8), arguments->bridgeValue, selectedIndex);
    return 1;
}

SEC(sub_80F84AC)
s32 script_command_forward_object_property(
    struct ScriptObjectSelectionContext* context, u8* owner,
    const struct ScriptObjectPropertyArguments* arguments,
    void* commandContext)
{
    s32 propertyValue = sub_80F6B44(
        context, arguments->objectIndex, arguments->propertySelector);

    sub_80E9C4C(
        commandContext, owner + 0x18, context->fieldState2C + 0x1794,
        (s32)(owner + 0xA8), arguments->bridgeValue, propertyValue);
    return 1;
}

SEC(sub_80F112C)
s32 script_command_control_object_motion(
    void* context, void* object, struct ScriptExecutionState* state,
    s32* arguments)
{
    /* Operation bits are proven; the gameplay names of the three modes are not. */
    s32 operation = *arguments++;

    if (!(operation & 2)) {
        sub_8047B08(object, operation, *arguments);
        state->primaryFlags |= 0x42;
    } else if (operation == 2) {
        sub_8047B5C(object, *(s16*)arguments);
    } else {
        sub_8046A10(object);
    }
    return 1;
}
