#include "global.h"
#include "audio/sound_effects.h"
#include "field/actor.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.large_actor_state_machines." #name)))

typedef s32 (*SoundFunction)(s32 sample, s32 duration);

int loc_8198220(void);
int loc_819832C(void);
void sub_8082E1C(void* object, s32 animation, s32 command, s32 argument);
void sub_80884AC(void* object);
void sub_8087EFC(void* object);
void sub_80DF024(s32 effect, s32 x, s32 y, s32 z,
                 struct RuntimeObject* object);
void sub_80C110C(void);
void sub_80C9BA8(void);
void sub_80D27DC(void);
void sub_80D782C(void);

#define field_complete_actor_b_command_2063_and_arm_sound sub_80C1054
SEC(sub_80C1054)
void field_complete_actor_b_command_2063_and_arm_sound(
    struct FieldAction* process)
{
    struct FieldActor* actor = gFieldRuntime->actorB;
    struct RuntimeObject* action = (struct RuntimeObject*)&actor->action;
    s32 state;
    s8* flags;

    if (action->visual->flags & 8) {
        state = actor->stateFlags & 6;
        if (state == 2 || state == 4) {
            sub_8082E1C(action, 10, 0x2063, 0);
            flags = (s8*)&action->visual->flags;
            *flags &= -7;
        }
        state = action->flags76 & 6;
        if (state == 2 || state == 4) {
            action->unknown7A =
                ((SoundFunction)(*(u32*)0x03001038
                    + ((u32)loc_819832C - (u32)loc_8198220)))(0x4000, 20);
            *(u16*)&action->unknown7E[0] = 0;
            flags = (s8*)&action->flags79;
            *flags &= -0x21;
        }
        action->secondaryTimer &= 0x0FFF;
        process->update = sub_80C110C;
    }
}

#define field_emit_actor_a_effect_2fe6_and_arm_sound sub_80C9AEC
SEC(sub_80C9AEC)
void field_emit_actor_a_effect_2fe6_and_arm_sound(struct FieldAction* process)
{
    struct FieldRuntime* runtime = gFieldRuntime;
    struct FieldActor* actorA = runtime->actorA;
    struct RuntimeObject* actionA = (struct RuntimeObject*)&actorA->action;
    struct FieldActor* actorB = runtime->actorB;
    s32 state;
    s8* flags;

    sub_80884AC(&actorB->action);
    if (actorB->flags81 & 0x20) {
        sub_80DF024(0x2FE6, actionA->currentPositionX / 0x100,
                    actionA->currentPositionY / 0x100,
                    actionA->verticalPosition / 0x100, actionA);
        sound_effect_play(0x7C, SOUND_VOLUME_UNCHANGED);
        state = actorA->stateFlags & 6;
        if (state == 2 || state == 4) {
            actorA->soundHandle =
                ((SoundFunction)(*(u32*)0x03001038
                    + ((u32)loc_819832C - (u32)loc_8198220)))(0x4000, 24);
            actorA->value86 = 0;
            flags = (s8*)&actorA->flags81;
            *flags &= -0x21;
        }
        process->update = sub_80C9BA8;
    }
}

#define field_emit_actor_a_effect_1e_then_animation_8 sub_80D2724
SEC(sub_80D2724)
void field_emit_actor_a_effect_1e_then_animation_8(struct FieldAction* process)
{
    struct FieldActor* actor = gFieldRuntime->actorA;
    struct RuntimeObject* action = (struct RuntimeObject*)&actor->action;
    s32 state;
    s8* flags;

    sub_8087EFC(action);
    if (actor->flags81 & 0x20) {
        sound_effect_play(0x65, SOUND_VOLUME_UNCHANGED);
        sub_80DF024(0x1E, action->currentPositionX / 0x100,
                    action->currentPositionY / 0x100,
                    action->verticalPosition / 0x100, action);
        state = actor->stateFlags & 6;
        if (state == 2 || state == 4) {
            if (action->state->variant == -1)
                sub_8082E1C(action, 8, 0x2000, 0);
            else
                sub_8082E1C(action, 8, 0x204D, 0);
            flags = (s8*)&action->visual->flags;
            *flags = (*flags & -7) | 2;
        }
        process->update = sub_80D27DC;
    }
}

#define field_finish_actor_a_and_arm_actor_b_sound sub_80D7774
SEC(sub_80D7774)
void field_finish_actor_a_and_arm_actor_b_sound(struct FieldAction* process)
{
    struct FieldRuntime* runtime = gFieldRuntime;
    struct FieldActor* actorA = runtime->actorA;
    struct RuntimeObject* actionA = (struct RuntimeObject*)&actorA->action;
    struct RuntimeObject* actionB =
        (struct RuntimeObject*)&runtime->actorB->action;
    s32 state;
    s8* flags;

    if (actionA->visual->flags & 8) {
        state = actorA->stateFlags & 6;
        if (state == 2 || state == 4) {
            sub_8082E1C(actionA, 0, -1, 0);
            flags = (s8*)&actionA->visual->flags11;
            *flags &= -0x41;
            flags = (s8*)&actionA->visual->flags;
            *flags &= -7;
        }
        state = actionB->flags76 & 6;
        if (state == 2 || state == 4) {
            actionB->unknown7A =
                ((SoundFunction)(*(u32*)0x03001038
                    + ((u32)loc_819832C - (u32)loc_8198220)))(0x4000, 10);
            *(u16*)&actionB->unknown7E[0] = 0;
            flags = (s8*)&actionB->flags79;
            *flags &= -0x21;
        }
        process->update = sub_80D782C;
    }
}
