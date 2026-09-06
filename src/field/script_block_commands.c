#include "field/script_block_commands.h"

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
