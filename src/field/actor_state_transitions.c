#include "global.h"
#include "field/actor.h"
#include "field/functions.h"

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
