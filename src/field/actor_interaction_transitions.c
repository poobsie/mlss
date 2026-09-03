#include "global.h"
#include "field/actor.h"
#include "field/functions.h"

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

DEFINE_ACTOR_INTERACTION_TRANSITION(field_activate_actor_a_command_2024_kind_5, actorA, 5, 0x2024, sub_80A3810)
DEFINE_ACTOR_INTERACTION_TRANSITION(field_activate_actor_b_command_2053_kind_5, actorB, 5, 0x2053, sub_80A46FC)
DEFINE_ACTOR_INTERACTION_TRANSITION(field_activate_actor_b_command_2053_kind_0, actorB, 0, 0x2053, sub_80A3DF0)
DEFINE_ACTOR_INTERACTION_TRANSITION(field_activate_actor_b_command_205E_kind_0, actorB, 0, 0x205E, sub_80B363C)
