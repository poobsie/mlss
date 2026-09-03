#include "field/runtime_flags.h"

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

SEC(sub_80F7590) void field_clear_nested_flags_1788(u32 mask)
{
    struct FieldNestedFlagTarget* target;

    target = FIELD_NESTED_FLAG_RUNTIME->container244->target2C;
    target->flags1788 &= ~mask;
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
