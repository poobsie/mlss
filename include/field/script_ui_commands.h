#ifndef GUARD_FIELD_SCRIPT_UI_COMMANDS_H
#define GUARD_FIELD_SCRIPT_UI_COMMANDS_H

#include "global.h"

struct ScriptExecutionState;

struct FieldScriptUiSharedState {
    u8 unknown000[0x9A1];
    u8 returnPending9A1;
};

struct FieldScriptUiRuntime {
    u8 unknown00[0x14];
    void* displayOwner14;
    u8 unknown18[0x0C];
    struct FieldScriptUiSharedState* sharedState24;
};

#define field_script_configure_screen_layer sub_80FA6DC
#define field_script_set_owned_sprite_visibility sub_80FA7A0
#define field_script_mark_return_pending sub_80FA7C4

s32 field_script_configure_screen_layer(
    struct FieldScriptUiRuntime* runtime, void* state, const u32* arguments);
s32 field_script_set_owned_sprite_visibility(
    struct FieldScriptUiRuntime* runtime, void* state, const s32* arguments);
u8 field_script_mark_return_pending(
    struct FieldScriptUiRuntime* runtime, struct ScriptExecutionState* state);

#endif
