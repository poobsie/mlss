#include "global.h"
#include "audio/sound_effects.h"
#include "field/actor.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.large_actor_state_machines." #name)))

typedef s32 (*SoundFunction)(s32 sample, s32 duration);

int loc_8198220(void);
int loc_819832C(void);
void sub_8082E1C(void* object, s32 animation, s32 command, s32 argument);
void sub_8088274(struct RuntimeObject* object, s32 first, s32 second);
void sub_808843C(struct RuntimeObject* object, s32 x, s32 y, s32 z, s32 scale);
void sub_80884AC(void* object);
u8 sub_8087CE4(struct RuntimeObject* object);
void sub_8087EFC(void* object);
void sub_80DF024(s32 effect, s32 x, s32 y, s32 z,
                 struct RuntimeObject* object);
void sub_80C9BA8(void);
void sub_80D27DC(void);
void sub_80D205C(void);
void sub_80C8418(void);
void sub_80C63CC(struct RuntimeObject* object);

SEC(sub_80C6330)
void sub_80C6330(struct RuntimeObject* caller)
{
    struct FieldActor* actorA = gFieldRuntime->actorA;
    struct RuntimeObject* action = (struct RuntimeObject*)&actorA->action;
    s32 positionX;
    s32 positionY;
    s32 positionZ;
    s32 state;
    s8* visualFlags;

    sub_8087CE4(action);
    if (actorA->flags81 & 0x20) {
        sound_effect_play(0x2E, SOUND_VOLUME_UNCHANGED);
        positionX = action->currentPositionX;
        if (positionX < 0)
            positionX += 0xFF;
        positionX >>= 8;
        positionY = action->currentPositionY;
        if (positionY < 0)
            positionY += 0xFF;
        positionY >>= 8;
        positionZ = action->verticalPosition;
        if (positionZ < 0)
            positionZ += 0xFF;
        positionZ >>= 8;
        sub_80DF024(0x1E, positionX, positionY, positionZ, action);

        state = actorA->stateFlags & 6;
        if (state == 2 || state == 4) {
            sub_8082E1C(action, 7, 0x2034, 0);
            visualFlags = (s8*)&action->visual->flags;
            *visualFlags = (*visualFlags & -7) | 2;
        }
        caller->update = sub_80C63CC;
    }
}

#define field_emit_actor_a_effect_1e_and_animation_7 sub_80C837C
SEC(sub_80C837C)
void field_emit_actor_a_effect_1e_and_animation_7(
    struct FieldAction* process)
{
    struct FieldRuntime* runtime = gFieldRuntime;
    struct FieldActor* actorA = runtime->actorA;
    struct RuntimeObject* actionA = (struct RuntimeObject*)&actorA->action;
    s32 x;
    s32 y;
    s32 z;
    s32 state;
    s32 visualMask;

    sub_8087CE4(actionA);
    if ((actorA->flags81 & 0x20) != 0) {
        sound_effect_play(0x2E, SOUND_VOLUME_UNCHANGED);
        x = actionA->currentPositionX;
        if (x < 0)
            x += 0xFF;
        x >>= 8;
        y = actionA->currentPositionY;
        if (y < 0)
            y += 0xFF;
        y >>= 8;
        z = actionA->verticalPosition;
        visualMask = -7;
        if (z < 0)
            z += 0xFF;
        z >>= 8;
        sub_80DF024(0x1E, x, y, z, actionA);
        state = actorA->stateFlags & 6;
        if (state == 2 || state == 4) {
            sub_8082E1C(actionA, 7, 0x2034, 0);
            actionA->visual->flags = (actionA->visual->flags & visualMask) | 2;
        }
        process->update = (void (*)(void))sub_80C8418;
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

#define field_on_actor_a_complete_place_animation_11 sub_80D1FA4
SEC(sub_80D1FA4)
void field_on_actor_a_complete_place_animation_11(struct FieldAction* process)
{
    struct FieldActor* actorA = gFieldRuntime->actorA;
    struct RuntimeObject* actionA = (struct RuntimeObject*)&actorA->action;
    s32 state;
    s8* flags;

    if (actionA->visual->flags & 8) {
        state = actorA->stateFlags & 6;
        if (state == 2 || state == 4) {
            sub_808843C(actionA,
                        actionA->positionX / 0x100
                            + actorA->displayOffsetX,
                        actionA->positionY / 0x100
                            + actorA->displayOffsetY,
                        0, -1);
            sub_8088274(actionA, 0, 0x66);
        }
        state = actionA->stateFlags & 6;
        if (state == 2 || state == 4) {
            sub_8082E1C(actionA, 11, 0x2036, 0);
            flags = (s8*)&actionA->visual->flags;
            *flags = (*flags & -7) | 2;
        }
        process->update = sub_80D205C;
    }
}

#define field_on_actor_a_complete_place_animation_10 sub_80D266C
SEC(sub_80D266C)
void field_on_actor_a_complete_place_animation_10(struct FieldAction* process)
{
    struct FieldActor* actorA = gFieldRuntime->actorA;
    struct RuntimeObject* actionA = (struct RuntimeObject*)&actorA->action;
    s32 state;
    s8* flags;

    if (actionA->visual->flags & 8) {
        state = actorA->stateFlags & 6;
        if (state == 2 || state == 4) {
            sub_808843C(actionA,
                        actionA->positionX / 0x100
                            + actorA->displayOffsetX,
                        actionA->positionY / 0x100
                            + actorA->displayOffsetY,
                        0, -1);
            sub_8088274(actionA, 0, 0x66);
        }
        state = actionA->stateFlags & 6;
        if (state == 2 || state == 4) {
            sub_8082E1C(actionA, 10, 0x2036, 0);
            flags = (s8*)&actionA->visual->flags;
            *flags = (*flags & -7) | 2;
        }
        process->update = (void (*)(void))sub_80D2724;
    }
}
