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

struct FieldScriptCommandState {
    u32 cursor;
    u8 unknown04[0x10];
    u32 retryCursor;
};

#define field_branch_if_script_block_active sub_80F8900
#define field_activate_script_block sub_80F8940
#define field_reset_selected_script_block sub_80F8A08
#define field_set_selected_script_block_flag_4 sub_80F8A90
#define field_get_indexed_script_halfword_1a0 sub_80F8DA4
#define field_set_script_runtime_count sub_80F8DE0
#define field_start_root_script_block sub_80F8EB0

s32 field_branch_if_script_block_active(
    struct FieldScriptBlockOwner* owner, struct FieldScriptCommandState* caller,
    const s32* arguments);
s32 field_activate_script_block(
    struct FieldScriptBlockOwner* owner, void* state, const s32* arguments);
s32 field_reset_selected_script_block(
    struct FieldScriptBlockOwner* owner, void* state, const s32* arguments);
s32 field_set_selected_script_block_flag_4(
    struct FieldScriptBlockOwner* owner, void* state, const s32* arguments);
u16 field_get_indexed_script_halfword_1a0(
    struct FieldScriptBlockOwner* owner, u8 index);
void field_set_script_runtime_count(
    struct FieldScriptBlockOwner* owner, u8 count);
void field_start_root_script_block(
    struct FieldScriptBlockOwner* owner, u32 cursor);

#endif
