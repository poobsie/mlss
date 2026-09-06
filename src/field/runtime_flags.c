#include "field/runtime_flags.h"
#include "script/execution_state.h"

#define SEC(symbol) __attribute__((section(".text.small_functions_01." #symbol)))
#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define MISC3_SEC(symbol) \
    __attribute__((section(".text.misc_helpers_03." STRINGIFY(symbol))))

struct FieldNestedFlagTarget {
    u8 unknown0000[0x1788];
    u32 flags1788;
    u8 unknown178C[0x0C];
    u32 flags1798;
    u8 unknown179C;
    u8 state179D;
};

struct FieldNestedFlagContainer {
    u8 unknown00[0x2C];
    struct FieldNestedFlagTarget* target2C;
};

struct FieldNestedFlagRuntime {
    u8 unknown000[0x244];
    struct FieldNestedFlagContainer* container244;
    u8 unknown248[0x77];
    u8 flags2BF;
};

struct FieldNestedFlagRequest {
    u8 unknown000[0xE8];
    s32 valueE8;
    u8 unknown0EC[8];
    u8 selectorF4;
};

struct FieldNestedFlagRecord {
    u8 unknown00[0xA0];
    u16 flagsA0;
};

struct FieldModeRuntime {
    u8 unknown000[0x0B];
    u8 flags00B;
    u8 unknown00C[0x399];
    s8 mode3A5;
};


#define FIELD_NESTED_FLAG_RUNTIME (*(struct FieldNestedFlagRuntime**)0x03000FD8)
#define FIELD_MODE_RUNTIME (*(struct FieldModeRuntime**)0x03000FD8)

void sub_80F2524(
    struct FieldNestedFlagContainer* container, u8 selector, s32 value);

SEC(sub_8082B00)
s32 field_runtime_test_flag_10(void)
{
    s32 result = FIELD_MODE_RUNTIME->flags00B & 0x10;
    if (result != 0)
        return 1;
    return 0;
}

static const u16 sub_8082B00_padding SEC(sub_8082B00) = 0;

SEC(sub_80F7590) void field_clear_nested_flags_1788(u32 mask)
{
    struct FieldNestedFlagTarget* target;

    target = FIELD_NESTED_FLAG_RUNTIME->container244->target2C;
    target->flags1788 &= ~mask;
}

SEC(sub_80F75B4) void field_set_nested_flags_1788(u32 mask)
{
    struct FieldNestedFlagTarget* target;

    target = FIELD_NESTED_FLAG_RUNTIME->container244->target2C;
    target->flags1788 |= mask;
}

SEC(sub_80F7D3C)
s32 field_wait_for_nested_state_179d_clear(
    struct FieldNestedFlagContainer* container,
    struct ScriptExecutionState* state)
{
    s32 result;

    if ((container->target2C->state179D & 0x7F) == 0) {
        result = 1;
    } else {
        state->cursor = state->resumeCursor;
        result = 0;
    }
    return result;
}
SEC(sub_80F7D3C) const u16 field_wait_for_nested_state_179d_clear_padding = 0;

SEC(sub_80F7E84)
s32 field_wait_for_runtime_flag_10_clear(
    void* context, struct ScriptExecutionState* state)
{
    s32 result;

    if ((field_runtime_test_flag_10() << 24) == 0) {
        result = 1;
    } else {
        state->cursor = state->resumeCursor;
        result = 0;
    }
    return result;
}
SEC(sub_80F7E84) const u16 field_wait_for_runtime_flag_10_clear_padding = 0;

SEC(sub_80F7EA4)
s32 field_set_indexed_runtime_byte_350(
    void* context, void* state, const s32* arguments)
{
    u16 index = *arguments++ - 6;
    s32 operation = *arguments++;

    if (operation == 0) {
        u8* indexedBytes = (u8*)FIELD_NESTED_FLAG_RUNTIME + 0x350;
        indexedBytes[index] = arguments[0];
    }
    return 1;
}



MISC3_SEC(field_set_nested_flags_1788_and_1798)
void field_set_nested_flags_1788_and_1798(u32 mask)
{
    struct FieldNestedFlagTarget* target;

    target = FIELD_NESTED_FLAG_RUNTIME->container244->target2C;
    target->flags1788 |= mask;
    target->flags1798 |= mask;
}

MISC3_SEC(field_clear_record_flag_0200_when_nested_flag_4000)
void field_clear_record_flag_0200_when_nested_flag_4000(
    struct FieldNestedFlagContainer* container,
    struct FieldNestedFlagRecord* record)
{
    if (container->target2C->flags1788 & 0x4000)
        record->flagsA0 &= ~0x0200;
}

MISC3_SEC(field_submit_nested_request_and_mark_pending)
void field_submit_nested_request_and_mark_pending(
    struct FieldNestedFlagRequest* request)
{
    struct FieldNestedFlagRuntime* runtime;
    u8 flags;
    s32 pendingMask;

    sub_80F2524(FIELD_NESTED_FLAG_RUNTIME->container244,
                request->selectorF4, request->valueE8);
    runtime = FIELD_NESTED_FLAG_RUNTIME;
    flags = runtime->flags2BF;
    pendingMask = 4;
    runtime->flags2BF = (u8)(flags | pendingMask);
}

SEC(sub_81069B4) void field_set_mode_3a5_and_mark_pending(s8 mode)
{
    void* runtime;

    FIELD_MODE_RUNTIME->mode3A5 = mode;
    runtime = *(void**)0x03000FD8;
    *(u8*)((u8*)runtime + 0x0B) =
        (u8)(*(u8*)((u8*)runtime + 0x0B) | 0x40);
}
