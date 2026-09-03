#include "global.h"
#include "field/actor.h"

#define SEC(name) __attribute__((section(".text.actor_interaction_transitions." #name)))

extern void sub_80884AC(void *);
extern void sub_8082E1C(void *, s32, s32, s32);

#define DEFINE_ACTOR_INTERACTION_TRANSITION(name, actor_offset, kind, command, next) \
    extern void next(void);                                              \
    SEC(name) void name(struct FieldAction *action)                      \
    {                                                                    \
        struct FieldActor *actor = gFieldRuntime->actor_offset;          \
        struct FieldAction *part = &actor->action;                       \
        s32 state;                                                       \
        s32 mask;                                                        \
        s32 flag_value;                                                  \
        volatile u8 *flags;                                              \
        sub_80884AC(part);                                               \
        if (actor->flags81 & 0x20) {                                    \
            state = actor->stateFlags & 6;                              \
            if (state == 2 || state == 4) {                             \
                sub_8082E1C(part, kind, command, 0);                    \
                flags = &part->visual->flags;                            \
                flag_value = *flags;                                    \
                mask = -7;                                              \
                flag_value &= mask;                                     \
                flag_value |= 2;                                        \
                *flags = flag_value;                                    \
            }                                                            \
            action->update = next;                                      \
        }                                                                \
    }

DEFINE_ACTOR_INTERACTION_TRANSITION(sub_80A3ABC, actorA, 5, 0x2024, sub_80A3810)
DEFINE_ACTOR_INTERACTION_TRANSITION(sub_80A49A8, actorB, 5, 0x2053, sub_80A46FC)
DEFINE_ACTOR_INTERACTION_TRANSITION(sub_80A4A10, actorB, 0, 0x2053, sub_80A3DF0)
DEFINE_ACTOR_INTERACTION_TRANSITION(sub_80B9504, actorB, 0, 0x205E, sub_80B363C)
