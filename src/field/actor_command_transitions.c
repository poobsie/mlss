#include "global.h"
#include "field/actor.h"
#include "field/functions.h"

#define SEC(name) __attribute__((section(".text.actor_command_transitions." #name)))

extern void sub_8082E1C(void *, s32, s32, s32);

#define DEFINE_ACTOR_COMMAND(name, actor_offset, kind, command, next)     \
    extern void next(void);                                              \
    SEC(name) void name(struct FieldAction *action)                      \
    {                                                                    \
        struct FieldActor *actor = gFieldRuntime->actor_offset;          \
        struct FieldAction *part = &actor->action;                       \
        s32 state;                                                       \
        s32 mask;                                                        \
        s32 flag_value;                                                  \
        volatile u8 *flags;                                              \
        if (part->visual->flags & 8) {                                   \
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

DEFINE_ACTOR_COMMAND(field_actor_a_command_2024_kind_4, actorA, 4, 0x2024, sub_80BA6F8)
DEFINE_ACTOR_COMMAND(field_actor_b_command_2063_kind_3_a, actorB, 3, 0x2063, sub_80C33B0)
DEFINE_ACTOR_COMMAND(field_actor_b_command_2063_kind_3_b, actorB, 3, 0x2063, sub_80C26E4)
DEFINE_ACTOR_COMMAND(field_actor_a_command_2034_kind_8_a, actorA, 8, 0x2034, sub_80C1CE4)
DEFINE_ACTOR_COMMAND(field_actor_a_command_2034_kind_8_b, actorA, 8, 0x2034, sub_80C9854)
