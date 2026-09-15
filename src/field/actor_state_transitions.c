#include "global.h"
#include "audio/sound_effects.h"
#include "field/actor.h"
#include "field/functions.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.actor_state_transitions." #name)))

typedef s32 (*SoundFunction)(s32, s32);

extern int loc_8198220();
extern int loc_819832C();

#define DEFINE_ACTOR_STATE(name, primary, secondary, next)                \
    extern void next(void);                                               \
    SEC(name) void name(struct FieldAction *action)                       \
    {                                                                     \
        s32 inactive;                                                     \
        s32 mask;                                                         \
        s32 flag_value;                                                   \
        s32 state;                                                        \
        struct FieldRuntime *runtime = gFieldRuntime;                     \
        struct FieldActor *actor = runtime->primary;                     \
        volatile u8 *flags;                                               \
        inactive = (s32)runtime->secondary->action.update;                \
        if (inactive == 0) {                                              \
            state = actor->stateFlags & 6;                                \
            if (state == 2 || state == 4) {                              \
                actor->soundHandle =                                     \
                    ((SoundFunction)(*(u32 *)0x03001038                   \
                        + ((u32)loc_819832C - (u32)loc_8198220)))(0x4000, 16); \
                actor->value86 = inactive;                               \
                flags = &actor->flags81;                                 \
                flag_value = *flags;                                     \
                mask = -0x21;                                           \
                flag_value &= mask;                                      \
                *flags = flag_value;                                     \
            }                                                             \
            action->update = next;                                       \
        }                                                                 \
    }

DEFINE_ACTOR_STATE(field_wait_actor_b_then_prepare_actor_a_a, actorA, actorB, sub_80A6FEC)
DEFINE_ACTOR_STATE(field_wait_actor_b_then_prepare_actor_a_b, actorA, actorB, sub_80AC9C4)
DEFINE_ACTOR_STATE(field_wait_actor_b_then_prepare_actor_a_c, actorA, actorB, sub_80C0BE4)
DEFINE_ACTOR_STATE(field_wait_actor_b_then_prepare_actor_a_d, actorA, actorB, sub_80CD200)

extern void sub_80884AC(struct FieldAction* action);
extern void sub_80A99A8(void);
extern void sub_80AB404(void);
extern void sub_80AC610(struct RuntimeObject* object);
extern u8 sub_8087CE4(struct RuntimeObject* object);
extern void sub_8082E1C(struct RuntimeObject* object, s32 animation,
                        s32 command, s32 argument);
extern void sub_80DF024(s32 effect, s32 x, s32 y, s32 z,
                        struct RuntimeObject* object);

#define field_runtime_object_noop_update sub_80AC684
SEC(sub_80AC684)
void field_runtime_object_noop_update(struct RuntimeObject* object)
{
    (void)object;
}
SEC(sub_80AC684) const u16 field_runtime_object_noop_update_padding = 0;

#define field_emit_actor_a_effect_1e_and_animation_8 sub_80AB360
SEC(sub_80AB360)
void field_emit_actor_a_effect_1e_and_animation_8(
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
        visualMask = -7;
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
        if (z < 0)
            z += 0xFF;
        z >>= 8;
        sub_80DF024(0x1E, x, y, z, actionA);
        state = actorA->stateFlags & 6;
        if (state == 2 || state == 4) {
            sub_8082E1C(actionA, 8, 0x2034, 0);
            actionA->visual->flags = (actionA->visual->flags & visualMask) | 2;
        }
        {
            u8 visualFlags = actionA->visual->flags11;
            visualFlags |= 0x40;
            actionA->visual->flags11 = visualFlags;
        }
        process->update = (void (*)(void))sub_80AB404;
    }
}

SEC(sub_80AC4AC) void sub_80AC4AC(void)
{
    s32 state;
    struct FieldRuntime* runtime = gFieldRuntime;
    struct FieldActor* actorA = runtime->actorA;
    struct FieldAction* actionA = &actorA->action;
    struct FieldActor* actorB = runtime->actorB;
    struct FieldAction* actionB = &actorB->action;

    sub_80884AC(actionB);
    if (actorB->flags81 & 0x20) {
        state = actorA->stateFlags & 6;
        if (state == 2 || state == 4)
            actionA->update = sub_80A99A8;
        actionB->update = 0;
    }
}

#define field_set_actor_b_and_object_continuations sub_80AC4F8
SEC(sub_80AC4F8)
void field_set_actor_b_and_object_continuations(struct RuntimeObject* object)
{
    struct FieldActor* actor = gFieldRuntime->actorB;
    struct RuntimeObject* action = (struct RuntimeObject*)&actor->action;
    s32 state = actor->stateFlags & 6;

    if (state == 2 || state == 4)
        action->update = sub_80AC610;
    object->update = sub_80AC684;
}

SEC(sub_8112350) void sub_8112350(void (*update)(void))
{
    struct FieldActor* actor;
    struct FieldActor* optionalActor;

    actor = gFieldRuntime->actorC;
    if ((actor->stateFlags & 6) == 2)
        actor->action.update = update;
    optionalActor = gFieldRuntime->actorD;
    if (optionalActor != 0 && (optionalActor->stateFlags & 6) == 2)
        optionalActor->action.update = update;
}
