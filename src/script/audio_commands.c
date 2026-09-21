#include "audio/music.h"
#include "audio/sound_effects.h"
#include "script/command_handlers.h"
#include "script/execution_state.h"

#define SEC(name) __attribute__((section(".text.script_command_handlers." #name)))

struct ScriptSoundVolumeArguments {
    u8 duration;
    u8 padding01[3];
    u8 volume;
};

SEC(sub_80EAEF8)
s32 script_command_control_sound_effect(
    void* context, struct ScriptExecutionState* state,
    const s32* arguments)
{
    s32 operation = *arguments++;

    switch (operation) {
    case 0:
        sound_effect_play(*arguments, SOUND_VOLUME_UNCHANGED);
        break;
    case 1:
        if (*arguments != 0)
            sound_effect_stop(*arguments);
        else
            sound_effects_stop_all();
        break;
    case 2:
        if ((u8)sound_effect_is_playing(*arguments)) {
            state->cursor = state->resumeCursor;
            return 0;
        }
        break;
    }
    return 1;
}

SEC(sub_80EAEE0)
s32 script_command_set_sound_effect_volume(
    void* context, void* state, const u32* arguments)
{
    u32 operation = *arguments++;

    if (operation == 0) {
        const struct ScriptSoundVolumeArguments* parameters =
            (const struct ScriptSoundVolumeArguments*)arguments;
        sound_effects_set_volume(parameters->volume, parameters->duration);
    }
    return 1;
}
SEC(sub_80EAEE0) const u16 sub_80EAEE0_padding = 0;

SEC(sub_80EAF4C)
s32 script_command_control_music(
    void* context, void* state,
    s32* arguments)
{
    s32 operation = *arguments++;

    switch (operation) {
    case 0:
        if (arguments[2] == 2)
            arguments[2] = MUSIC_VOLUME_UNCHANGED;
        music_play(arguments[0], arguments[1], arguments[2]);
        break;
    case 1:
        if (arguments[2] == 2)
            arguments[2] = MUSIC_VOLUME_UNCHANGED;
        music_resume(arguments[0], arguments[2], (u8)arguments[1]);
        break;
    case 2:
        music_set_volume(arguments[0], (u8)arguments[2], (u8)arguments[1]);
        break;
    case 3:
        music_set_tempo(arguments[0], (u8)arguments[2], (u8)arguments[1]);
        break;
    }
    return 1;
}
