#include "global.h"
#include "mario_bros/functions.h"
#include "mario_bros/object.h"

#define SECTION(name) __attribute__((section(".text.mariobros_small_" #name)))

struct MarioBrosEffectState {
    u8 unknown00[0x3F];
    u8 pendingUpdate;
    u8 unknown40[4];
    u16 activeEffect;
};

void sub_8F66490(struct MarioBrosEffectState* state);
void sub_8F5CC20(struct MarioBrosObject* object);

SECTION(sub_8F6118C)
void mario_bros_tick_action_countdown(struct MarioBrosObject* object)
{
    u16 remaining = object->value24 - 1;

    object->value24 = remaining;
    if (remaining == 0)
        sub_8F5CC20(object);
}

SECTION(sub_8F64B84)
void mario_bros_begin_enabled_fall(struct MarioBrosObject* object)
{
    u8 flags;

    object->value1C = -0x200;
    flags = object->flags0A;
    flags |= 4;
    /* Keep the two original flag updates separate for the matching compiler. */
    asm volatile("" : "+r"(flags));
    flags |= 0x80;
    object->flags0A = flags;
    if (object->value26 != 0)
        object->value26 = 0;
}

SECTION(sub_8F69E2C)
void mario_bros_clear_pending_effect_update(struct MarioBrosEffectState* state)
{
    if (state->activeEffect != 0)
        sub_8F66490(state);
    if (state->pendingUpdate != 0)
        state->pendingUpdate = 0;
}
SECTION(sub_8F69E2C) const u16 mario_bros_clear_pending_effect_update_padding = 0;
