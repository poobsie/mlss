#include "field/script_block_commands.h"
#include "script/execution_state.h"

#define SEC(symbol) \
    __attribute__((section(".text.small_functions_01." #symbol)))

SEC(sub_80F8900)
s32 field_branch_if_script_block_active(
    struct FieldScriptBlockOwner* owner, struct FieldScriptCommandState* caller,
    const s32* arguments)
{
    struct FieldScriptBlockState* block;
    s32 selection = *arguments++;

    switch (selection) {
    case 0:
        block = (struct FieldScriptBlockState*)owner->scriptRegion2C;
        break;
    case 1:
        block = (struct FieldScriptBlockState*)(owner->scriptRegion2C +
                                                0x100 + (arguments[1] << 8));
        break;
    }

    if (block->flagsA0 & 1)
        caller->cursor = arguments[0];
    return 1;
}

SEC(sub_80F8900)
const u16 field_branch_if_script_block_active_padding = 0;

SEC(sub_80F8940)
s32 field_activate_script_block(
    struct FieldScriptBlockOwner* owner, void* state, const s32* arguments)
{
    struct FieldScriptBlockState* block;
    s32 selection = *arguments++;
    s16 delay;

    switch (selection) {
    case 0:
        block = (struct FieldScriptBlockState*)owner->scriptRegion2C;
        break;
    case 1:
        block = (struct FieldScriptBlockState*)(owner->scriptRegion2C +
                                                ((u8)(arguments[0] + 1) << 8));
        break;
    }

    block->nextCursor = block->cursor;
    block->flagsA0 = 1;
    delay = 23;
    do {
        delay--;
    } while (delay > 0);
    return 1;
}

SEC(sub_80F8A08)
s32 field_reset_selected_script_block(
    struct FieldScriptBlockOwner* owner, void* state, const s32* arguments)
{
    s32 offset = arguments[0] << 8;
    u8* selected = owner->scriptRegion2C + offset;
    struct FieldScriptBlockState* block =
        (struct FieldScriptBlockState*)(selected + 0x700);

    block->flagsA0 = 0;
    block->cursor = block->nextCursor;
    return 1;
}

SEC(sub_80F8A08)
const u16 field_reset_selected_script_block_padding = 0;

SEC(sub_80F8A90)
s32 field_set_selected_script_block_flag_4(
    struct FieldScriptBlockOwner* owner, void* state, const s32* arguments)
{
    s32 offset = arguments[1] << 8;
    u8* selected = owner->scriptRegion2C + offset;
    struct FieldScriptBlockState* block =
        (struct FieldScriptBlockState*)(selected + 0x700);

    switch (arguments[0]) {
    case 0:
        block->flagsA0 |= 4;
        break;
    case 1:
        block->flagsA0 &= ~4;
        break;
    }
    return 1;
}

SEC(sub_80F8DA4)
u16 field_get_indexed_script_halfword_1a0(
    struct FieldScriptBlockOwner* owner, u8 index)
{
    return *(u16*)(owner->scriptRegion2C + ((u8)index << 8) + 0x1A0);
}

SEC(sub_80F8DA4)
const u16 field_get_indexed_script_halfword_1a0_padding = 0;

SEC(sub_80F8DE0)
void field_set_script_runtime_count(
    struct FieldScriptBlockOwner* owner, u8 count)
{
    *(u32*)(owner->scriptRegion2C + 0x1780) = count;
}

SEC(sub_80F8EB0)
void field_start_root_script_block(
    struct FieldScriptBlockOwner* owner, u32 cursor)
{
    script_state_replace_primary_channel(
        (u8*)owner + 0x1C,
        (struct ScriptExecutionState*)owner->scriptRegion2C,
        cursor, 0, 1, 0xFF);
}

SEC(sub_80F8EB0)
const u16 field_start_root_script_block_padding = 0;
