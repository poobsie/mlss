#include "field/script_ui_commands.h"
#include "screens/runtime_helpers.h"
#include "script/execution_state.h"
#include "ui/visibility.h"

#define SCRIPT_FIELD_RUNTIME (*(u8**)0x03000FD0)

#define SEC(symbol) \
    __attribute__((section(".text.small_functions_01." #symbol)))

SEC(sub_80FA6DC)
s32 field_script_configure_screen_layer(
    struct FieldScriptUiRuntime* runtime, void* state, const u32* arguments)
{
    if (arguments[0] & 1) {
        screen_configure_layer20_default_and_mark_156(runtime->displayOwner14);
    } else {
        screen_reset_layer20_and_copy_control(runtime->displayOwner14);
    }
    return 1;
}

SEC(sub_80FA6DC)
const u16 field_script_configure_screen_layer_padding = 0;

SEC(sub_80FA7A0)
s32 field_script_set_owned_sprite_visibility(
    struct FieldScriptUiRuntime* runtime, void* state, const s32* arguments)
{
    switch (arguments[0]) {
    case 0:
        ui_hide_owned_sprite(runtime->displayOwner14);
        break;
    case 1:
        ui_show_owned_sprite(runtime->displayOwner14);
        break;
    }
    return 1;
}

SEC(sub_80FA7A0)
const u16 field_script_set_owned_sprite_visibility_padding = 0;

SEC(sub_80FA7C4)
u8 field_script_mark_return_pending(
    struct FieldScriptUiRuntime* runtime, struct ScriptExecutionState* state)
{
    runtime->sharedState24->channelState9A1 = 1;
    return script_command_return((u8*)runtime + 0x1C, state);
}

SEC(sub_80FAC30)
s32 field_script_start_global_script_channel(
    struct FieldScriptUiRuntime* runtime, void* state, const u32* arguments)
{
    script_state_replace_primary_channel(
        (u8*)runtime + 0x1C,
        (struct ScriptExecutionState*)(SCRIPT_FIELD_RUNTIME + 0x1F8),
        arguments[1], 0, 1, 0xFF);
    return 1;
}

SEC(sub_80FAD2C)
s32 field_script_set_indexed_channel_flag_4(
    struct FieldScriptUiRuntime* runtime, void* state, const s32* arguments)
{
    struct ScriptExecutionState* channel =
        (struct ScriptExecutionState*)runtime->sharedState24 + arguments[1] + 1;

    switch (arguments[0]) {
    case 0:
        channel->primaryFlags |= 4;
        break;
    case 1:
        channel->primaryFlags &= ~4;
        break;
    }
    return 1;
}

SEC(sub_80FAF8C)
void field_script_start_root_channel_and_mark_running(
    struct FieldScriptUiRuntime* runtime, u32 cursor)
{
    script_state_replace_primary_channel(
        (u8*)runtime + 0x1C,
        (struct ScriptExecutionState*)runtime->sharedState24,
        cursor, 0, 1, 0xFF);
    runtime->sharedState24->channelState9A1 = 2;
}
