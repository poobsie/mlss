#include "global.h"
#include "field/display_scale_transition.h"
#include "script/animation_runtime.h"
#include "script/animation_script.h"

#define SEC(name) __attribute__((section(".text.script_transitions." #name)))

SEC(sub_80E18D8)
void animation_script_create_display_scale_from_record(
    struct AnimationScriptState* state)
{
    const u16* record = (const u16*)state->cursor;
    struct FieldDisplayScale* resource =
        sub_8084338(record[0], (s16)record[1], 2, 1);

    sub_807BC90(resource);
    state->owner = resource;
    state->update = sub_80E1AB0;
    state->update(state);
}

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
