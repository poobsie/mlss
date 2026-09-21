#include "global.h"
#include "audio/sound_effects.h"
#include "field/actor.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.large_actor_state_machines." #name)))

void sub_807C298(struct RuntimeObject* object);
void sub_8082E1C(void* object, s32 animation, s32 command, s32 argument);
void sub_8088274(struct RuntimeObject* object, s32 first, s32 second);
void sub_808843C(struct RuntimeObject* object, s32 x, s32 y, s32 z, s32 scale);
void sub_8087EFC(void* object);
void sub_80D405C(void);
void sub_80D086C(struct FieldAction* process);
void sub_80D08F8(struct FieldAction* process);
void sub_80D0AF8(struct RuntimeObject* object);

#define field_on_actor_b_complete_place_actor_a_linked_object sub_80D0790
SEC(sub_80D0790)
void field_on_actor_b_complete_place_actor_a_linked_object(
    struct FieldAction* process)
{
    struct FieldRuntime* runtime = gFieldRuntime;
    struct RuntimeObject* actionA =
        (struct RuntimeObject*)&runtime->actorA->action;
    struct FieldActor* actorB = runtime->actorB;
    struct RuntimeObject* actionB = (struct RuntimeObject*)&actorB->action;
    struct RuntimeObject* linked;
    s32 state;
    s8* flags;

    if (actionB->visual->flags & 8) {
        sound_effect_play(0x11F, SOUND_VOLUME_UNCHANGED);
        state = actorB->stateFlags & 6;
        if (state == 2 || state == 4) {
            sub_8082E1C(actionB, 0, 0x204D, 0);
            flags = (s8*)&actionB->visual->flags;
            *flags &= -7;
        }
        sub_807C298(actionA->linkedObject);
        linked = actionA->linkedObject;
        state = linked->stateFlags & 6;
        if (state == 2 || state == 4) {
            sub_808843C(linked,
                        actionA->positionX / 0x100 + actionA->displayOffsetX,
                        actionA->positionY / 0x100 + actionA->displayOffsetY,
                        actionA->positionZBase / 0x100 + 8, -1);
            sub_8088274(actionA->linkedObject, 0, 0x66);
        }
        process->update = (void (*)(void))sub_80D086C;
    }
}

#define field_on_linked_actor_ready_set_visual_and_continue sub_80D086C
SEC(sub_80D086C)
void field_on_linked_actor_ready_set_visual_and_continue(
    struct FieldAction* process)
{
    struct FieldRuntime* runtime = gFieldRuntime;
    struct FieldActor* actorA = runtime->actorA;
    struct RuntimeObject* actionA = (struct RuntimeObject*)&actorA->action;
    s32 state;
    s8* flags;

    sub_8087EFC(actionA->linkedObject);
    if ((actionA->linkedObject->motionFlags & 0x20) != 0) {
        sound_effect_play(0x9C, SOUND_VOLUME_UNCHANGED);
        state = actorA->stateFlags & 6;
        if (state == 2 || state == 4) {
            sub_8082E1C(actionA, 5, 0x2036, 0);
            flags = (s8*)&actionA->visual->flags;
            *flags = (*flags & -7) | 2;
        }
        state = actionA->linkedObject->stateFlags & 6;
        if (state == 2 || state == 4)
            actionA->linkedObject->update = sub_80D0AF8;
        process->update = (void (*)(void))sub_80D08F8;
    }
}

/* Synchronize actor B's attached object before the following launch phase. */
#define field_prepare_actor_b_linked_object_then_continue sub_80D3FD4
SEC(sub_80D3FD4)
void field_prepare_actor_b_linked_object_then_continue(
    struct FieldAction* process)
{
    struct FieldActor* actorB = gFieldRuntime->actorB;
    struct RuntimeObject* actionB = (struct RuntimeObject*)&actorB->action;
    struct RuntimeObject* linked;
    s32 state;
    s8* flags;

    sub_807C298(actionB->linkedObject->linkedObject);
    linked = actionB->linkedObject;
    linked->currentPositionX = actionB->currentPositionX;
    linked->currentPositionY = actionB->currentPositionY;
    linked->verticalPosition = actionB->verticalPosition;

    state = actorB->stateFlags & 6;
    if (state == 2 || state == 4) {
        sub_8082E1C(actionB, 1, 0x2066, 0);
        flags = (s8*)&actionB->visual->flags;
        *flags = (*flags & -7) | 2;
    }
    if (actionB->linkedObject != 0) {
        sub_8082E1C(actionB->linkedObject, 1, 0x2095, 0);
        flags = (s8*)&actionB->linkedObject->visual->flags;
        *flags &= -7;
    }
    process->update = sub_80D405C;
}
