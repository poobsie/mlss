#include "graphics/process_state.h"
#include "script/command_handlers.h"
#include "script/execution_state.h"

#define SEC(name) __attribute__((section(".text.script_command_handlers." #name)))
#define FIELD_COMMAND_RUNTIME (*(struct ScriptCommandFieldRuntime**)0x03000FD8)
#define SCRIPT_GLOBAL_FB8 (*(void**)0x03000FB8)
#define U8AT(pointer, offset) (*(u8*)((u8*)(pointer) + (offset)))
#define field_value_transfer_status sub_8116620

struct FieldValueTransfer;

struct ScriptCommandFieldRuntime {
    u8 unknown000[0x248];
    struct FieldValueTransfer* valueTransfer;
    u8 unknown24C[0x73];
    u8 flags2BF;
    u8 unknown2C0[0x30];
    void* resource2F0;
};

struct ScriptValueTransferArguments {
    s32 selector;
    s32 duration;
    u16 flags;
    u8 padding0A[2];
    u16 dispatchValue;
};

struct ScriptDisplayValueTransferArguments {
    s32 selector;
    s32 dispatchValue;
};

struct ScriptVisualResourceRecord {
    struct GraphicsLinkedVisual* visual;
    u8 unknown04[8];
    u8 identifier;
    u8 unknown0D[2];
    u8 active;
};

struct ScriptVisualResourceTable {
    struct ScriptVisualResourceRecord* records;
};

struct ScriptVisualResourceContext {
    u8 unknown00[0x28];
    struct ScriptVisualResourceTable* resourceTable;
};

struct ScriptResourceEntry {
    u8 unknown00[0x42];
    u8 flags42;
    u8 unknown43[9];
};

struct ScriptResourceOwner {
    u8 unknown00[4];
    struct ScriptResourceEntry* resources04;
};

extern void sub_807F6EC(s32, s32);
extern void sub_807F6D0(void);
extern u8 sub_8116620(struct FieldValueTransfer* state);
extern u8 sub_80E3CF4(void);
extern void sub_807F708(
    s32 kind, s32 value, s32 duration, s32 flags, s32 dispatchValue);
extern void sub_807F754(s32 kind, s32 value, s32 dispatchValue);
extern void sub_80E9330(void* owner, u16 value);
extern void sub_80E6FB8(void* resource, s32 layer);
extern void sub_80E7118(void* resource, u8 mask);
extern void sub_80E6E68(void* resource);

SEC(sub_80EAEBC)
s32 script_command_branch_on_resource_flag(
    void* context, struct ScriptResourceOwner* owner,
    struct ScriptExecutionState* state, const u32* arguments)
{
    if ((U8AT(owner->resources04, 0x1B2) >> *arguments++) & 1)
        state->cursor = *arguments;
    return 1;
}
SEC(sub_80EAEBC) const u16 script_command_branch_on_resource_flag_padding = 0;

SEC(sub_80F7C3C)
s32 script_command_control_value_transfer(
    void* context, void* state, const s32* operation)
{
    switch (*operation) {
    case 0:
        sub_807F6EC(0, -1);
        break;
    case 1:
        sub_807F6EC(1, -1);
        break;
    case 2:
        sub_807F6D0();
        break;
    }
    return 1;
}
SEC(sub_80F7C3C) const u16 script_command_control_value_transfer_padding = 0;

SEC(sub_80F7BB4)
s32 script_command_wait_for_matching_visual(
    struct ScriptVisualResourceContext* context,
    struct ScriptExecutionState* state, const u32* identifier)
{
    s16 i = 0;
    struct ScriptVisualResourceRecord* record = context->resourceTable->records;

    do {
        if (record->active &&
            (record->identifier == *identifier || *identifier == 0x3F)) {
            state->cursor = state->resumeCursor;
            return 0;
        }
        i++;
        record++;
    } while (i <= 3);
    return 1;
}

SEC(sub_80F7C78)
s32 script_command_wait_for_value_transfer(
    void* context, struct ScriptExecutionState* state)
{
    if (field_value_transfer_status(FIELD_COMMAND_RUNTIME->valueTransfer) != 0 ||
        sub_80E3CF4() != 0 || (FIELD_COMMAND_RUNTIME->flags2BF & 0x20) ||
        FIELD_COMMAND_RUNTIME->resource2F0 != NULL) {
        state->cursor = state->resumeCursor;
        return 0;
    }
    return 1;
}

SEC(sub_80F7CD0)
s32 script_command_start_value_transfer(
    void* context, void* state,
    const struct ScriptValueTransferArguments* arguments)
{
    s32 kind = (arguments->selector & 1) ? 4 : 0;
    s32 value = 0;

    if (arguments->selector > 1)
        value = 0x7FFF;
    sub_807F708(kind, value, arguments->duration, arguments->flags,
                arguments->dispatchValue);
    return 1;
}

SEC(sub_80F7D0C)
s32 script_command_start_display_value_transfer(
    void* context, void* state,
    const struct ScriptDisplayValueTransferArguments* arguments)
{
    s32 kind = (arguments->selector & 1) ? 4 : 0;
    s32 value = 0;

    if (arguments->selector > 1)
        value = 0x7FFF;
    sub_807F754(kind, value, arguments->dispatchValue);
    return 1;
}

SEC(sub_80EB05C)
s32 script_command_control_resource_wait(
    void* context, void* owner, struct ScriptExecutionState* state,
    const u32* arguments)
{
    u32 operation = *arguments++;

    switch (operation) {
    case 0:
        sub_80E9330(owner, *(const u16*)arguments);
        break;
    case 1: {
        register struct ScriptResourceEntry* resources asm("r0") =
            ((struct ScriptResourceOwner*)owner)->resources04;
        register u32 index asm("r2") = *arguments;

        // Preserve the original register allocation around the scaled lookup.
        asm("" : "+r"(resources), "+r"(index));
        resources += index;
        asm("" : "+r"(resources));
        if ((s32)((u32)resources->flags42 << 29) >= 0) {
            state->cursor = state->resumeCursor;
            return 0;
        }
        break;
    }
    }
    return 1;
}
SEC(sub_80EB05C) const u16 sub_80EB05C_padding = 0;

SEC(sub_80EB09C)
s32 script_command_configure_graphics_resource(
    void* context, void* resource, void* state, const s32* mode)
{
    if (*mode <= 4) {
        sub_80E6FB8(resource, (u16)*mode);
        sub_80E7118(resource, (u8)(1 << *mode));
    } else {
        sub_80E6E68(resource);
        sub_80E7118(resource, U8AT(*(void**)((u8*)resource + 4), 0x1B3));
    }
    U8AT(SCRIPT_GLOBAL_FB8, 0x31) = 0;
    return 1;
}
