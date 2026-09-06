#ifndef GUARD_FIELD_SCRIPT_BLOCK_COMMANDS_H
#define GUARD_FIELD_SCRIPT_BLOCK_COMMANDS_H

#include "global.h"

struct FieldScriptBlockOwner {
    u8 unknown00[0x2C];
    u8* scriptRegion2C;
};

struct FieldScriptBlockState {
    u32 cursor;
    u32 nextCursor;
    u8 unknown08[0x98];
    u16 flagsA0;
};

#define field_reset_selected_script_block sub_80F8A08
#define field_set_selected_script_block_flag_4 sub_80F8A90

s32 field_reset_selected_script_block(
    struct FieldScriptBlockOwner* owner, void* state, const s32* arguments);
s32 field_set_selected_script_block_flag_4(
    struct FieldScriptBlockOwner* owner, void* state, const s32* arguments);

#endif
