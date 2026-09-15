#include "global.h"
#include "audio/sound_effects.h"
#include "field/actor.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.actor_runtime_callbacks." #name)))

void sub_8082E1C(void* object, s32 animation, s32 command, s32 argument);
void sub_80884AC(void* object);
void sub_80BE8D0(void);
void sub_80B99A0(void);
void sub_80BCF60(struct RuntimeObject* object);

#define field_prepare_actor_b_command_2062_and_continue sub_80C0930
SEC(sub_80C0930)
void field_prepare_actor_b_command_2062_and_continue(struct FieldAction* process)
{
    struct FieldActor* actor = gFieldRuntime->actorB;
    struct FieldAction* action = &actor->action;
    s32 state = actor->stateFlags & 6;
    s32 flagValue;
    s32 mask;
    volatile u8* flags;

    if (state == 2 || state == 4) {
        sub_8082E1C(action, 15, 0x2062, 0);
        flags = &action->visual->flags;
        flagValue = *flags;
        mask = -7;
        flagValue &= mask;
        flagValue |= 2;
        *flags = flagValue;
    }
    process->update = sub_80BE8D0;
}

#define field_on_actor_b_visual_complete_start_command_2062 sub_80C09AC
SEC(sub_80C09AC)
void field_on_actor_b_visual_complete_start_command_2062(
    struct RuntimeObject* object)
{
    struct FieldActor* actor = gFieldRuntime->actorB;
    struct RuntimeObject* action = (struct RuntimeObject*)&actor->action;
    s32 state;
    s32 flagValue;
    s32 mask;
    volatile u8* flags;

    if (action->visual->flags & OBJECT_VISUAL_COMPLETE) {
        state = actor->stateFlags & 6;
        if (state == 2 || state == 4) {
            sub_8082E1C(action, 14, 0x2062, 0);
            flags = &action->visual->flags;
            flagValue = *flags;
            mask = -7;
            flagValue &= mask;
            *flags = flagValue;
        }
        object->update = sub_80BCF60;
    }
}

#define field_poll_actor_a_then_command_2024 sub_80C0BE4
SEC(sub_80C0BE4)
void field_poll_actor_a_then_command_2024(struct FieldAction* process)
{
    struct FieldActor* actor = gFieldRuntime->actorA;
    struct FieldAction* action = &actor->action;
    s32 state;
    s32 flagValue;
    s32 mask;
    volatile u8* flags;

    sub_80884AC(action);
    if (actor->flags81 & 0x20) {
        sound_effect_play(0xAF, SOUND_VOLUME_UNCHANGED);
        state = actor->stateFlags & 6;
        if (state == 2 || state == 4) {
            sub_8082E1C(action, 0, 0x2024, 0);
            flags = &action->visual->flags;
            flagValue = *flags;
            mask = -7;
            flagValue &= mask;
            flagValue |= 2;
            *flags = flagValue;
        }
        process->update = sub_80B99A0;
    }
}
