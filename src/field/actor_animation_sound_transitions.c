#include "global.h"
#include "audio/sound_effects.h"
#include "field/actor.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.large_actor_state_machines." #name)))

typedef s32 (*SoundFunction)(s32 sample, s32 duration);

int loc_8198220(void);
int loc_819832C(void);
void sub_8082E1C(void* object, s32 animation, s32 command, s32 argument);
void sub_8088164(struct RuntimeObject* object, s32 value);
void sub_808843C(struct RuntimeObject* object, s32 x, s32 y, s32 z, s32 scale);
void sub_80C110C(void);
void sub_80C18E4(void);
void sub_80C27B0(void);
void sub_80C347C(void);
void sub_80C8C64(void);
void sub_80C943C(void);
void sub_80CBF64(void);
void sub_80CCA38(void);
void sub_80D53F8(void);
void sub_80D6AA8(void);
void sub_80D782C(void);

#define field_on_actor_b_complete_animation_7_and_sound_35_a sub_80C182C
SEC(sub_80C182C)
void field_on_actor_b_complete_animation_7_and_sound_35_a(
    struct FieldAction* process)
{
    struct FieldActor* actorB = gFieldRuntime->actorB;
    struct RuntimeObject* actionB = (struct RuntimeObject*)&actorB->action;
    s32 state;
    s8* flags;

    if (actionB->visual->flags & 8) {
        sound_effect_play(0xAF, SOUND_VOLUME_UNCHANGED);
        state = actorB->stateFlags & 6;
        if (state == 2 || state == 4) {
            sub_8082E1C(actionB, 7, 0x2063, 0);
            flags = (s8*)&actionB->visual->flags;
            *flags = (*flags & -7) | 2;
        }
        state = actionB->stateFlags & 6;
        if (state == 2 || state == 4) {
            actionB->motionDurationOverride =
                ((SoundFunction)(*(u32*)0x03001038
                    + ((u32)loc_819832C - (u32)loc_8198220)))(0x4000, 35);
            *(u16*)&actionB->unknown7E[0] = 0;
            flags = (s8*)&actionB->motionFlags;
            *flags &= -0x21;
        }
        process->update = sub_80C18E4;
    }
}

#define field_on_actor_b_complete_animation_11_and_actor_a_sound_a sub_80C26E4
SEC(sub_80C26E4)
void field_on_actor_b_complete_animation_11_and_actor_a_sound_a(
    struct FieldAction* process)
{
    struct FieldRuntime* runtime = gFieldRuntime;
    struct RuntimeObject* actionA =
        (struct RuntimeObject*)&runtime->actorA->action;
    struct FieldActor* actorB = runtime->actorB;
    struct RuntimeObject* actionB = (struct RuntimeObject*)&actorB->action;
    s32 state;
    s8* flags;

    if (actionB->visual->flags & 8) {
        sound_effect_play(0xAF, SOUND_VOLUME_UNCHANGED);
        state = actorB->stateFlags & 6;
        if (state == 2 || state == 4) {
            sub_8082E1C(actionB, 11, 0x2063, 0);
            flags = (s8*)&actionB->visual->flags;
            *flags = (*flags & -7) | 2;
        }
        state = actionA->stateFlags & 6;
        if (state == 2 || state == 4) {
            actionA->motionDurationOverride =
                ((SoundFunction)(*(u32*)0x03001038
                    + ((u32)loc_819832C - (u32)loc_8198220)))(0x4000, 10);
            *(u16*)&actionA->unknown7E[0] = 0;
            flags = (s8*)&actionA->motionFlags;
            *flags &= -0x21;
        }
        actionA->secondaryTimer &= 0x0FFF;
        process->update = sub_80C27B0;
    }
}

#define field_on_actor_b_complete_animation_11_and_actor_a_sound_b sub_80C33B0
SEC(sub_80C33B0)
void field_on_actor_b_complete_animation_11_and_actor_a_sound_b(
    struct FieldAction* process)
{
    struct FieldRuntime* runtime = gFieldRuntime;
    struct RuntimeObject* actionA =
        (struct RuntimeObject*)&runtime->actorA->action;
    struct FieldActor* actorB = runtime->actorB;
    struct RuntimeObject* actionB = (struct RuntimeObject*)&actorB->action;
    s32 state;
    s8* flags;

    if (actionB->visual->flags & 8) {
        sound_effect_play(0xAF, SOUND_VOLUME_UNCHANGED);
        state = actorB->stateFlags & 6;
        if (state == 2 || state == 4) {
            sub_8082E1C(actionB, 11, 0x2063, 0);
            flags = (s8*)&actionB->visual->flags;
            *flags = (*flags & -7) | 2;
        }
        state = actionA->stateFlags & 6;
        if (state == 2 || state == 4) {
            actionA->motionDurationOverride =
                ((SoundFunction)(*(u32*)0x03001038
                    + ((u32)loc_819832C - (u32)loc_8198220)))(0x4000, 10);
            *(u16*)&actionA->unknown7E[0] = 0;
            flags = (s8*)&actionA->motionFlags;
            *flags &= -0x21;
        }
        actionA->secondaryTimer &= 0x0FFF;
        process->update = sub_80C347C;
    }
}

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
        state = action->stateFlags & 6;
        if (state == 2 || state == 4) {
            action->motionDurationOverride =
                ((SoundFunction)(*(u32*)0x03001038
                    + ((u32)loc_819832C - (u32)loc_8198220)))(0x4000, 20);
            *(u16*)&action->unknown7E[0] = 0;
            flags = (s8*)&action->motionFlags;
            *flags &= -0x21;
        }
        action->secondaryTimer &= 0x0FFF;
        process->update = sub_80C110C;
    }
}

#define field_on_actor_b_complete_animation_10_and_sound_20 sub_80C8BA0
SEC(sub_80C8BA0)
void field_on_actor_b_complete_animation_10_and_sound_20(
    struct FieldAction* process)
{
    struct FieldActor* actorB = gFieldRuntime->actorB;
    struct RuntimeObject* actionB = (struct RuntimeObject*)&actorB->action;
    s32 state;
    s8* flags;

    if (actionB->visual->flags & 8) {
        sound_effect_play(0x88, SOUND_VOLUME_UNCHANGED);
        state = actorB->stateFlags & 6;
        if (state == 2 || state == 4) {
            sub_8082E1C(actionB, 10, 0x2063, 0);
            flags = (s8*)&actionB->visual->flags;
            *flags &= -7;
        }
        state = actionB->stateFlags & 6;
        if (state == 2 || state == 4) {
            actionB->motionDurationOverride =
                ((SoundFunction)(*(u32*)0x03001038
                    + ((u32)loc_819832C - (u32)loc_8198220)))(0x4000, 20);
            *(u16*)&actionB->unknown7E[0] = 0;
            flags = (s8*)&actionB->motionFlags;
            *flags &= -0x21;
        }
        actionB->secondaryTimer &= 0x0FFF;
        process->update = sub_80C8C64;
    }
}

#define field_on_actor_b_complete_animation_7_and_sound_35_b sub_80C9384
SEC(sub_80C9384)
void field_on_actor_b_complete_animation_7_and_sound_35_b(
    struct FieldAction* process)
{
    struct FieldActor* actorB = gFieldRuntime->actorB;
    struct RuntimeObject* actionB = (struct RuntimeObject*)&actorB->action;
    s32 state;
    s8* flags;

    if (actionB->visual->flags & 8) {
        sound_effect_play(0xAF, SOUND_VOLUME_UNCHANGED);
        state = actorB->stateFlags & 6;
        if (state == 2 || state == 4) {
            sub_8082E1C(actionB, 7, 0x2063, 0);
            flags = (s8*)&actionB->visual->flags;
            *flags = (*flags & -7) | 2;
        }
        state = actionB->stateFlags & 6;
        if (state == 2 || state == 4) {
            actionB->motionDurationOverride =
                ((SoundFunction)(*(u32*)0x03001038
                    + ((u32)loc_819832C - (u32)loc_8198220)))(0x4000, 35);
            *(u16*)&actionB->unknown7E[0] = 0;
            flags = (s8*)&actionB->motionFlags;
            *flags &= -0x21;
        }
        process->update = sub_80C943C;
    }
}

#define field_set_both_actor_animation_7_and_arm_actor_b_sound sub_80CC964
SEC(sub_80CC964)
void field_set_both_actor_animation_7_and_arm_actor_b_sound(
    struct FieldAction* process)
{
    struct FieldRuntime* runtime = gFieldRuntime;
    struct RuntimeObject* actionA =
        (struct RuntimeObject*)&runtime->actorA->action;
    struct RuntimeObject* actionB =
        (struct RuntimeObject*)&runtime->actorB->action;
    s32 state;
    s8* flags;

    if ((actionA->stateFlags & 6) == 2 || (actionA->stateFlags & 6) == 4) {
        sub_8082E1C(actionA, 7, 0x2035, 0);
        flags = (s8*)&actionA->visual->flags;
        *flags = (*flags & -7) | 2;
    }
    state = actionB->stateFlags & 6;
    if (state == 2 || state == 4) {
        sub_8082E1C(actionB, 7, 0x2064, 0);
        flags = (s8*)&actionB->visual->flags;
        *flags = (*flags & -7) | 2;
    }
    state = actionB->stateFlags & 6;
    if (state == 2 || state == 4) {
        actionB->motionDurationOverride =
            ((SoundFunction)(*(u32*)0x03001038
                + ((u32)loc_819832C - (u32)loc_8198220)))(0x4000, 8);
        *(u16*)&actionB->unknown7E[0] = 0;
        flags = (s8*)&actionB->motionFlags;
        *flags &= -0x21;
    }
    process->update = sub_80CCA38;
}

#define field_on_actor_b_complete_set_animation_6_and_arm_sound sub_80CBE70
SEC(sub_80CBE70)
void field_on_actor_b_complete_set_animation_6_and_arm_sound(
    struct FieldAction* process)
{
    struct FieldRuntime* runtime = gFieldRuntime;
    struct FieldActor* actorA = runtime->actorA;
    struct RuntimeObject* actionA = (struct RuntimeObject*)&actorA->action;
    struct RuntimeObject* actionB =
        (struct RuntimeObject*)&runtime->actorB->action;
    s32 state;
    s8* flags;

    if (actionB->visual->flags & 8) {
        sound_effect_play(0x88, SOUND_VOLUME_UNCHANGED);
        if ((actorA->stateFlags & 6) == 2 ||
            (actorA->stateFlags & 6) == 4) {
            sub_8082E1C(actionA, 6, 0x2035, 0);
            flags = (s8*)&actionA->visual->flags;
            *flags &= -7;
        }
        state = actionB->stateFlags & 6;
        if (state == 2 || state == 4) {
            sub_8082E1C(actionB, 6, 0x2064, 0);
            flags = (s8*)&actionB->visual->flags;
            *flags &= -7;
        }
        state = actionB->stateFlags & 6;
        if (state == 2 || state == 4) {
            actionB->motionDurationOverride =
                ((SoundFunction)(*(u32*)0x03001038
                    + ((u32)loc_819832C - (u32)loc_8198220)))(0x4000, 10);
            *(u16*)&actionB->unknown7E[0] = 0;
            flags = (s8*)&actionB->motionFlags;
            *flags &= -0x21;
        }
        actionB->secondaryTimer &= 0x0FFF;
        process->update = sub_80CBF64;
    }
}

#define field_when_actor_a_idle_finish_actor_b_and_arm_sound sub_80D69D8
SEC(sub_80D69D8)
void field_when_actor_a_idle_finish_actor_b_and_arm_sound(
    struct FieldAction* process)
{
    struct FieldRuntime* runtime = gFieldRuntime;
    struct RuntimeObject* actionA =
        (struct RuntimeObject*)&runtime->actorA->action;
    struct FieldActor* actorB = runtime->actorB;
    struct RuntimeObject* actionB = (struct RuntimeObject*)&actorB->action;
    s32 state;
    s8* flags;

    if (actionA->update == 0) {
        sound_effect_play(0x2E, SOUND_VOLUME_UNCHANGED);
        state = actorB->stateFlags & 6;
        if (state == 2 || state == 4) {
            actorB->soundHandle =
                ((SoundFunction)(*(u32*)0x03001038
                    + ((u32)loc_819832C - (u32)loc_8198220)))(0x4000, 32);
            actorB->value86 = 0;
            flags = (s8*)&actorB->flags81;
            *flags &= -0x21;
        }
        state = actionA->stateFlags & 6;
        if (state == 2 || state == 4) {
            sub_8082E1C(actionA, 0, 0x2024, 0);
            flags = (s8*)&actionA->visual->flags;
            *flags = (*flags & -7) | 2;
        }
        actionB->secondaryTimer &= 0x0FFF;
        process->update = sub_80D6AA8;
    }
}

#define field_on_actor_b_complete_place_and_launch_action sub_80D52F4
SEC(sub_80D52F4)
void field_on_actor_b_complete_place_and_launch_action(
    struct FieldAction* process)
{
    struct FieldActor* actorB = gFieldRuntime->actorB;
    struct RuntimeObject* actionB = (struct RuntimeObject*)&actorB->action;
    s32 state;
    s8* flags;

    if (actionB->visual->flags & 8) {
        sound_effect_play(0x2B, SOUND_VOLUME_UNCHANGED);
        state = actorB->stateFlags & 6;
        if (state == 2 || state == 4) {
            sub_8082E1C(actionB, 6, 0x2066, 0);
            flags = (s8*)&actionB->visual->flags;
            *flags = (*flags & -7) | 2;
        }
        if (actionB->linkedObject != 0) {
            sub_8082E1C(actionB->linkedObject, 6, 0x2095, 0);
            flags = (s8*)&actionB->linkedObject->visual->flags;
            *flags &= -7;
        }
        state = actionB->stateFlags & 6;
        if (state == 2 || state == 4) {
            sub_808843C(actionB,
                        actionB->positionX / 0x100 + actionB->displayOffsetX - 24,
                        actionB->positionY / 0x100 + actionB->displayOffsetY,
                        0, -1);
            actionB->motionDuration92 = actionB->positionZBase / 0x100 + 12;
            sub_8088164(actionB, 0x400);
        }
        actionB->motionDurationOverride = 0x2E8;
        process->update = sub_80D53F8;
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
        state = actionB->stateFlags & 6;
        if (state == 2 || state == 4) {
            actionB->motionDurationOverride =
                ((SoundFunction)(*(u32*)0x03001038
                    + ((u32)loc_819832C - (u32)loc_8198220)))(0x4000, 10);
            *(u16*)&actionB->unknown7E[0] = 0;
            flags = (s8*)&actionB->motionFlags;
            *flags &= -0x21;
        }
        process->update = sub_80D782C;
    }
}
