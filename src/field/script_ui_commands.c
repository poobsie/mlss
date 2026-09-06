#include "field/script_ui_commands.h"
#include "field/entry_toggle.h"
#include "screens/runtime_helpers.h"
#include "script/execution_state.h"
#include "ui/visibility.h"

#define SCRIPT_FIELD_RUNTIME (*(u8**)0x03000FD0)
typedef void (*FieldScriptMemoryFill)(u32 value, void* destination, u32 size);
#define FIELD_SCRIPT_MEMORY_FILL (*(volatile FieldScriptMemoryFill*)0x03001034)

#define SEC(symbol) \
    __attribute__((section(".text.small_functions_01." #symbol)))

SEC(sub_80FA6DC)
s32 field_script_configure_screen_layer(
    struct FieldScriptUiRuntime* runtime, void* state, const u32* arguments)
{
    if (arguments[0] & 1) {
        screen_configure_layer20_default_and_mark_156((void*)runtime->displayOwner14);
    } else {
        screen_reset_layer20_and_copy_control((void*)runtime->displayOwner14);
    }
    return 1;
}

SEC(sub_80FA6DC)
const u16 field_script_configure_screen_layer_padding = 0;

SEC(sub_80F940C)
void field_script_update_channels(struct FieldScriptUiRuntime* runtime)
{
    s16 index = 1;
    struct ScriptExecutionState* channel =
        (struct ScriptExecutionState*)runtime->sharedState24;

    do {
        if (channel->primaryFlags & 0x10) {
            script_state_tick_wait_timer((u8*)runtime + 0x1C, channel);
        }
        index--;
        channel++;
    } while (index > 0);

    {
        u16* flags;

        index = 0;
        flags = &channel->primaryFlags;

        do {
            if (!(*flags & 0x84)) {
                if (*flags & 2) {
                    field_toggle_target_flag_a0_02_if_entry_matches(
                        (struct FieldEntryMatchOwner*)runtime,
                        (struct FieldEntryToggleTarget*)channel, index);
                }
                if (*flags & 0x20) {
                    field_script_update_indexed_visual_channel(
                        runtime, channel, index);
                }
                if (*flags & 0x10) {
                    script_state_tick_wait_timer(
                        (u8*)runtime + 0x1C, channel);
                }
            }
            index++;
            flags = (u16*)((u8*)flags + 0xA8);
            channel++;
        } while (index <= 11);
    }
}

SEC(sub_80FA7A0)
s32 field_script_set_owned_sprite_visibility(
    struct FieldScriptUiRuntime* runtime, void* state, const s32* arguments)
{
    switch (arguments[0]) {
    case 0:
        ui_hide_owned_sprite((void*)runtime->displayOwner14);
        break;
    case 1:
        ui_show_owned_sprite((void*)runtime->displayOwner14);
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

SEC(sub_80FAE34)
void field_script_clear_channel_records(struct FieldScriptUiRuntime* runtime)
{
    s16 remaining = 13;
    u8* record = (u8*)runtime->sharedState24;

    do {
        FIELD_SCRIPT_MEMORY_FILL(0, record, 0xA8);
        record += 0xA8;
        remaining--;
    } while (remaining > 0);
}

SEC(sub_80FAE64)
void field_script_update_indexed_visual_channel(
    struct FieldScriptUiRuntime* runtime, struct ScriptExecutionState* channel,
    u8 index)
{
    struct RuntimeObjectVisual* visual =
        runtime->displayOwner14->records158[index].visual;
    s8* flags = (s8*)&visual->flags;
    u8 updatedFlags = (*flags & -7) | 2;

    *flags = updatedFlags;
    if (updatedFlags & 8) {
        channel->waitTimer--;
        if (channel->waitTimer == 0) {
            *flags |= 0x10;
            channel->primaryFlags ^= 0x20;
        }
        *flags &= -7;
    }
}

SEC(sub_80FAE64)
const u16 field_script_update_indexed_visual_channel_padding = 0;

SEC(sub_80FAF28)
void field_script_clear_channel_sprites_and_records(
    struct FieldScriptUiRuntime* runtime)
{
    if (runtime->sharedState24->channelFlags9A3 & 1) {
        s16 remaining = 12;
        struct FieldScriptUiSpriteRecord* record =
            runtime->displayOwner14->records158;

        do {
            if (record->visual != NULL) {
                record->visual->parameter20 = 0;
            }
            record++;
            remaining--;
        } while (remaining > 0);
    }

    field_script_clear_channel_records(runtime);
}
