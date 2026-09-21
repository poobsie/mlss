#include "global.h"
#include "audio/sound_effects.h"
#include "field/actor.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.large_actor_state_machines." #name)))

void sub_8082E1C(void* object, s32 animation, s32 command, s32 argument);
void sub_8088164(struct RuntimeObject* object, s32 value);
void sub_80880C4(struct RuntimeObject* object, s32 value);
void sub_808843C(struct RuntimeObject* object, s32 x, s32 y, s32 z, s32 scale);
void sub_80884AC(void* object);
u8 sub_8087CE4(struct RuntimeObject* object);
void sub_80C751C(struct RuntimeObject* object);
void sub_80A2918(void);
void sub_80BC408(struct RuntimeObject* object);
void sub_80C1BB8(struct RuntimeObject* object);
void sub_80C1CE4(struct RuntimeObject* object);
void sub_80C971C(struct RuntimeObject* object);
void sub_80C9854(struct RuntimeObject* object);
void sub_80A2428(struct RuntimeObject* object);

SEC(sub_80A2374)
void sub_80A2374(struct RuntimeObject* object)
{
    struct FieldRuntime* runtime = gFieldRuntime;
    struct FieldActor* actorB = runtime->actorB;
    struct RuntimeObject* actionB = (struct RuntimeObject*)&actorB->action;
    s32 positionX;
    s32 positionY;
    s32 positionZ;
    s32 adjustedX;

    sub_80884AC(actionB);
    if (actorB->flags81 & 0x20) {
        s32 state = actorB->stateFlags & 6;

        if (state == 2 || state == 4) {
            positionX = actionB->positionX;
            if (positionX < 0)
                positionX += 0xFF;
            adjustedX = (positionX >> 8) + actorB->displayOffsetX - 0x38;
            positionY = actionB->positionY;
            if (positionY < 0)
                positionY += 0xFF;
            sub_808843C(actionB, adjustedX,
                (positionY >> 8) + actorB->displayOffsetY, 0, -1);
            positionZ = actionB->positionZBase;
            if (positionZ < 0)
                positionZ += 0xFF;
            actorB->value9A = (positionZ >> 8) + 0x10;
            sub_8088164(actionB, 0x600);
        }
        actionB->secondaryTimer &= 0x0FFF;
        object->update = sub_80A2428;
    }
}

#define field_prepare_actor_a_offset_motion_or_idle sub_80C1AE8
SEC(sub_80C1AE8)
void field_prepare_actor_a_offset_motion_or_idle(
    struct RuntimeObject* caller)
{
    struct FieldActor* actorA = gFieldRuntime->actorA;
    struct RuntimeObject* action = (struct RuntimeObject*)&actorA->action;
    s32 idleState;
    s32 motionState;

    /* value9A remains a neutral actor field; current evidence only proves that
     * it tracks the action's display-relative height for this transition. */
    if (action->visual->flags & OBJECT_VISUAL_COMPLETE) {
        if (action->positionZBase == 0) {
            idleState = actorA->stateFlags & 6;
            if (idleState == 2 || idleState == 4)
                action->update = sub_80C1CE4;
        } else {
            motionState = actorA->stateFlags & 6;
            if (motionState == 2 || motionState == 4) {
                sub_808843C(action,
                    action->positionX / 256 + actorA->displayOffsetX - 0x3A,
                    action->positionY / 256 + actorA->displayOffsetY,
                    0, -1);
                actorA->value9A = action->positionZBase / 256 + 8;
                sub_8088164(action, 0x500);
            }
            action->secondaryTimer &= 0xFFF;
            caller->update = sub_80C1BB8;
        }
    }
}

#define field_prepare_actor_a_offset_motion_or_idle_variant sub_80C964C
SEC(sub_80C964C)
void field_prepare_actor_a_offset_motion_or_idle_variant(
    struct RuntimeObject* caller)
{
    struct FieldActor* actorA = gFieldRuntime->actorA;
    struct RuntimeObject* action = (struct RuntimeObject*)&actorA->action;
    s32 idleState;
    s32 motionState;

    if (action->visual->flags & OBJECT_VISUAL_COMPLETE) {
        if (action->positionZBase == 0) {
            idleState = actorA->stateFlags & 6;
            if (idleState == 2 || idleState == 4)
                action->update = sub_80C9854;
        } else {
            motionState = actorA->stateFlags & 6;
            if (motionState == 2 || motionState == 4) {
                sub_808843C(action,
                    action->positionX / 256 + actorA->displayOffsetX - 0x3A,
                    action->positionY / 256 + actorA->displayOffsetY,
                    0, -1);
                actorA->value9A = action->positionZBase / 256 + 8;
                sub_8088164(action, 0x500);
            }
            action->secondaryTimer &= 0xFFF;
            caller->update = sub_80C971C;
        }
    }
}

SEC(sub_80BC37C)
void sub_80BC37C(struct RuntimeObject* caller)
{
    struct FieldRuntime* runtime = gFieldRuntime;
    struct FieldActor* actorA;
    struct RuntimeObject* action;
    s16* actorValue;
    s32 value;
    u8 runtimeFlags;

    /* Explicit temporaries retain the original byte and halfword store order. */
    runtimeFlags = runtime->flags0A;
    runtimeFlags |= 0xC0;
    runtime->flags0A = runtimeFlags;
    actorA = gFieldRuntime->actorA;
    action = (struct RuntimeObject*)&actorA->action;
    if ((actorA->stateFlags & 6) == 2 ||
        (actorA->stateFlags & 6) == 4) {
        sub_808843C(action,
            action->positionX / 256 + actorA->displayOffsetX,
            action->positionY / 256 + actorA->displayOffsetY,
            0x17, -1);
        value = 0x18;
        actorValue = &actorA->value9A;
        *actorValue = value;
        sub_8088164(action, 0x300);
    }
    caller->update = sub_80BC408;
}

#define field_place_actor_b_from_state_then_animation_4 sub_80A2868
SEC(sub_80A2868)
void field_place_actor_b_from_state_then_animation_4(
    struct FieldAction* process)
{
    struct FieldRuntime* runtime = gFieldRuntime;
    struct FieldActor* actorB = runtime->actorB;
    struct RuntimeObject* actionB = (struct RuntimeObject*)&actorB->action;
    struct RuntimeObjectState* state;
    s32 rawX;
    s32 rawY;
    s32 rawZ;
    s32 x;
    s32 y;
    s32 z;
    s32 sourceZ;
    s16 actorHeight;

    sub_80884AC(actionB);
    if ((actorB->flags81 & 0x20) != 0) {
        if ((actorB->stateFlags & 6) == 2 ||
            (actorB->stateFlags & 6) == 4) {
            state = actionB->state;
            rawX = state->worldPositionX;
            if (rawX < 0)
                rawX += 0xFF;
            x = rawX >> 8;
            rawY = state->worldPositionY;
            if (rawY < 0)
                rawY += 0xFF;
            y = rawY >> 8;
            rawZ = state->floorHeight;
            if (rawZ < 0)
                rawZ += 0xFF;
            z = rawZ >> 8;
            sub_808843C(actionB, x, y, z, -1);
            sourceZ = actionB->positionZBase;
            if (sourceZ < 0)
                sourceZ += 0xFF;
            sourceZ >>= 8;
            actorHeight = (s16)(sourceZ + 0x1A);
            actorB->value9A = actorHeight;
            sub_8088164(actionB, 0x880);
        }
        actionB->secondaryTimer &= 0x0FFF;
        process->update = sub_80A2918;
    }
}

#define field_place_actor_a_from_process_state_then_animation_4 sub_80C741C
SEC(sub_80C741C)
void field_place_actor_a_from_process_state_then_animation_4(
    struct RuntimeObject* process)
{
    struct FieldRuntime* runtime = gFieldRuntime;
    struct FieldActor* actorA = runtime->actorA;
    struct RuntimeObject* actionA = (struct RuntimeObject*)&actorA->action;
    struct FieldActor* actorB = runtime->actorB;
    struct RuntimeObject* actionB;
    struct RuntimeObjectState* state;
    s32 actorState;
    s8* flags;

    actionB = (struct RuntimeObject*)&actorB->action;
    state = (struct RuntimeObjectState*)process->positionOwner;
    sub_80884AC(actionB);
    sub_8087CE4(actionA);
    if (actorB->flags81 & 0x20) {
        actorState = actorA->stateFlags & 6;
        if (actorState == 2 || actorState == 4) {
            sub_808843C(actionA,
                        state->value38 / 0x100 + state->displayOffsetX - 10,
                        state->value3C / 0x100 + state->displayOffsetY + 3,
                        state->value40 / 0x100 + state->displayOffsetZ - 21,
                        -1);
            sub_80880C4(actionA, 0x600);
        }
        actorState = actionA->stateFlags & 6;
        if (actorState == 2 || actorState == 4) {
            sub_8082E1C(actionA, 4, 0x2034, 0);
            flags = (s8*)&actionA->visual->flags;
            *flags &= -7;
        }
        actionA->secondaryTimer &= 0x0FFF;
        process->update = sub_80C751C;
    }
}
