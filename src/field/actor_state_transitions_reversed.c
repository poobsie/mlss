#include "global.h"
#include "field/actor.h"

#define SEC(name) __attribute__((section(".text.actor_state_transitions_reversed." #name)))

typedef s32 (*SoundFunction)(s32, s32);

extern int loc_8198220();
extern int loc_819832C();

#define DEFINE_REVERSED_ACTOR_STATE(name, next)                          \
    extern void next(void);                                               \
    SEC(name) void name(struct FieldAction *action)                       \
    {                                                                     \
        s32 inactive;                                                     \
        s32 mask;                                                         \
        s32 flag_value;                                                   \
        s32 state;                                                        \
        struct FieldRuntime *runtime = gFieldRuntime;                     \
        struct FieldActor *other = *(struct FieldActor * volatile *)&runtime->actorA; \
        struct FieldActor *actor = *(struct FieldActor * volatile *)&runtime->actorB; \
        volatile u8 *flags;                                               \
        inactive = (s32)other->action.update;                            \
        if (inactive == 0) {                                              \
            state = actor->stateFlags & 6;                               \
            if (state == 2 || state == 4) {                              \
                actor->soundHandle =                                     \
                    ((SoundFunction)(*(u32 *)0x03001038                   \
                        + ((u32)loc_819832C - (u32)loc_8198220)))(0x4000, 16); \
                actor->value86 = inactive;                               \
                flags = &actor->flags81;                                 \
                flag_value = *flags;                                     \
                mask = -0x21;                                            \
                flag_value &= mask;                                      \
                *flags = flag_value;                                     \
            }                                                             \
            action->update = next;                                       \
        }                                                                 \
    }

DEFINE_REVERSED_ACTOR_STATE(sub_80B35C8, sub_80B9504)
DEFINE_REVERSED_ACTOR_STATE(sub_80C0F30, sub_80C0FA4)
DEFINE_REVERSED_ACTOR_STATE(sub_80C8A7C, sub_80C8AF0)
