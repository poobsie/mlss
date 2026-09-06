#include "field/script_block_commands.h"

#define SEC(symbol) \
    __attribute__((section(".text.small_functions_01." #symbol)))

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
