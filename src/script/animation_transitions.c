#include "global.h"
#include "script/animation_script.h"

#define SEC(name) __attribute__((section(".text.script_transitions." #name)))

#define DEFINE_SCRIPT_TRANSITION(name, next)                \
    SEC(name) void name(struct AnimationScriptState* state) \
    {                                                        \
        const u8* script = state->cursor;                    \
        state->waitTimer = *(u16*)script;                    \
        state->cursor = script + 2;                          \
        state->update = next;                                \
        state->update(state);                                \
    }

DEFINE_SCRIPT_TRANSITION(
    animation_script_enter_10_byte_stream, animation_script_update_10_byte_stream)
DEFINE_SCRIPT_TRANSITION(
    animation_script_enter_4_byte_stream, animation_script_update_4_byte_stream)
DEFINE_SCRIPT_TRANSITION(
    animation_script_enter_command_stream, animation_script_update_command_stream)
