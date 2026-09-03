#include "global.h"
#include "field/actor.h"

#define SEC(name) __attribute__((section(".text.actor_activation_transitions." #name)))

typedef s32 (*SoundFunction)(s32, s32);

extern int loc_8198220();
extern int loc_819832C();
extern void sub_8087CE4(void *);

#define DEFINE_ACTOR_ACTIVATION_TRANSITION(name, actor_offset, kind, next) \
    extern void next(void);                                               \
    SEC(name) void name(struct FieldAction *action)                       \
    {                                                                     \
        s32 mask;                                                         \
        s32 flag_value;                                                   \
        s32 state;                                                        \
        s32 result;                                                       \
        s32 zero;                                                         \
        volatile s16 *result_field;                                      \
        volatile s16 *zero_field;                                        \
        struct FieldRuntime *runtime = gFieldRuntime;                     \
        struct FieldActor *actor = runtime->actor_offset;                 \
        volatile u8 *flags;                                               \
        sub_8087CE4(&actor->action);                                      \
        flags = &actor->flags81;                                         \
        if (*flags & 0x20) {                                              \
            state = actor->stateFlags & 6;                               \
            if (state == 2 || state == 4) {                              \
                result = ((SoundFunction)(*(u32 *)0x03001038             \
                    + ((u32)loc_819832C - (u32)loc_8198220)))(0x4000, kind); \
                result_field = &actor->soundHandle;                      \
                zero = 0;                                                \
                *result_field = result;                                  \
                zero_field = &actor->value86;                            \
                *zero_field = zero;                                      \
                flag_value = *flags;                                     \
                mask = -0x21;                                            \
                flag_value &= mask;                                      \
                *flags = flag_value;                                     \
            }                                                             \
            action->update = next;                                       \
        }                                                                 \
    }

DEFINE_ACTOR_ACTIVATION_TRANSITION(sub_80A0AF4, actorA, 2, sub_80A0B74)
DEFINE_ACTOR_ACTIVATION_TRANSITION(sub_80A1CC4, actorB, 2, sub_80A1D44)
DEFINE_ACTOR_ACTIVATION_TRANSITION(sub_80A2E7C, actorA, 8, sub_80A3B24)
DEFINE_ACTOR_ACTIVATION_TRANSITION(sub_80A3D70, actorB, 11, sub_80A4A10)
