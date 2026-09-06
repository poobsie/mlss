#include "global.h"
#include "audio/sound_effects.h"
#include "field/actor.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.late_actor_runtime_callbacks." #name)))

void sub_8082E1C(void* object, s32 animation, s32 command, s32 argument);
void sub_80D29D4(struct RuntimeObject* object);
void sub_80D266C(void);

#define field_prepare_actor_a_command_2036_and_continue sub_80D25F8
SEC(sub_80D25F8)
void field_prepare_actor_a_command_2036_and_continue(struct FieldAction* process)
{
    struct RuntimeObject* action =
        (struct RuntimeObject*)&gFieldRuntime->actorA->action;
    struct RuntimeObject* linked;
    s32 state;
    s8* flags;

    sound_effect_play(0x85, SOUND_VOLUME_UNCHANGED);
    linked = action->linkedObject;
    state = linked->flags76 & 6;
    if (state == 2 || state == 4)
        linked->update = sub_80D29D4;
    state = action->flags76 & 6;
    if (state == 2 || state == 4) {
        sub_8082E1C(action, 9, 0x2036, 0);
        flags = (s8*)&action->visual->flags;
        *flags &= -7;
    }
    process->update = sub_80D266C;
}
