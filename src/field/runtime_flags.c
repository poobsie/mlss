#include "field/runtime_flags.h"

#define SEC(symbol) __attribute__((section(".text.small_functions_01." #symbol)))

struct FieldNestedFlagTarget {
    u8 unknown0000[0x1788];
    u32 flags1788;
};

struct FieldNestedFlagContainer {
    u8 unknown00[0x2C];
    struct FieldNestedFlagTarget* target2C;
};

struct FieldNestedFlagRuntime {
    u8 unknown000[0x244];
    struct FieldNestedFlagContainer* container244;
};

struct FieldModeRuntime {
    u8 unknown000[0x0B];
    u8 flags00B;
    u8 unknown00C[0x399];
    s8 mode3A5;
};

#define FIELD_NESTED_FLAG_RUNTIME (*(struct FieldNestedFlagRuntime**)0x03000FD8)
#define FIELD_MODE_RUNTIME (*(struct FieldModeRuntime**)0x03000FD8)

SEC(sub_80F7590) void field_clear_nested_flags_1788(u32 mask)
{
    struct FieldNestedFlagTarget* target;

    target = FIELD_NESTED_FLAG_RUNTIME->container244->target2C;
    target->flags1788 &= ~mask;
}

SEC(sub_81069B4) void field_set_mode_3a5_and_mark_pending(s8 mode)
{
    void* runtime;

    FIELD_MODE_RUNTIME->mode3A5 = mode;
    runtime = *(void**)0x03000FD8;
    *(u8*)((u8*)runtime + 0x0B) =
        (u8)(*(u8*)((u8*)runtime + 0x0B) | 0x40);
}
