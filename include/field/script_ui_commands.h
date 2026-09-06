#ifndef GUARD_FIELD_SCRIPT_UI_COMMANDS_H
#define GUARD_FIELD_SCRIPT_UI_COMMANDS_H

#include "global.h"
#include "object/runtime_object.h"

struct ScriptExecutionState;

struct FieldScriptUiSharedState {
    u8 unknown000[0x9A1];
    u8 channelState9A1;
    u8 unknown9A2;
    u8 channelFlags9A3;
};

struct FieldScriptUiSpriteRecord {
    struct RuntimeObjectVisual* visual;
    u8 unknown04[0x3C];
};

struct FieldScriptUiDisplayOwner {
    u8 unknown000[0x158];
    struct FieldScriptUiSpriteRecord* records158;
};

struct FieldScriptUiRuntime {
    u8 unknown00[0x14];
    struct FieldScriptUiDisplayOwner* displayOwner14;
    u8 unknown18[0x0C];
    struct FieldScriptUiSharedState* sharedState24;
};

#define field_script_configure_screen_layer sub_80FA6DC
#define field_script_set_owned_sprite_visibility sub_80FA7A0
#define field_script_mark_return_pending sub_80FA7C4
#define field_script_start_global_script_channel sub_80FAC30
#define field_script_set_indexed_channel_flag_4 sub_80FAD2C
#define field_script_start_root_channel_and_mark_running sub_80FAF8C
#define field_script_clear_channel_records sub_80FAE34
#define field_script_update_indexed_visual_channel sub_80FAE64
#define field_script_update_channels sub_80F940C
#define field_script_clear_channel_sprites_and_records sub_80FAF28

s32 field_script_configure_screen_layer(
    struct FieldScriptUiRuntime* runtime, void* state, const u32* arguments);
s32 field_script_set_owned_sprite_visibility(
    struct FieldScriptUiRuntime* runtime, void* state, const s32* arguments);
u8 field_script_mark_return_pending(
    struct FieldScriptUiRuntime* runtime, struct ScriptExecutionState* state);
s32 field_script_start_global_script_channel(
    struct FieldScriptUiRuntime* runtime, void* state, const u32* arguments);
s32 field_script_set_indexed_channel_flag_4(
    struct FieldScriptUiRuntime* runtime, void* state, const s32* arguments);
void field_script_start_root_channel_and_mark_running(
    struct FieldScriptUiRuntime* runtime, u32 cursor);
void field_script_clear_channel_records(struct FieldScriptUiRuntime* runtime);
void field_script_update_indexed_visual_channel(
    struct FieldScriptUiRuntime* runtime, struct ScriptExecutionState* channel,
    u8 index);
void field_script_update_channels(struct FieldScriptUiRuntime* runtime);
void field_script_clear_channel_sprites_and_records(
    struct FieldScriptUiRuntime* runtime);

#endif
