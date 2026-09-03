#include "global.h"

#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.actor_interaction_transitions." #name)))

extern void sub_80884AC(void *);
extern void sub_8082E1C(void *, s32, s32, s32);

#define DEFINE_ACTOR_INTERACTION_TRANSITION(name, actor_offset, kind, command, next) \
    extern void next(void);                                              \
    SEC(name) void name(void *object)                                    \
    {                                                                    \
        void *global = *(void **)0x03000FD8;                             \
        void *actor = FIELD(global, void *, actor_offset);               \
        void *part = (u8 *)actor + 8;                                   \
        s32 state;                                                       \
        s32 mask;                                                        \
        s32 flag_value;                                                  \
        volatile u8 *flags;                                              \
        sub_80884AC(part);                                               \
        if (FIELD(actor, u8, 0x81) & 0x20) {                            \
            state = FIELD(actor, u8, 0x7E) & 6;                         \
            if (state == 2 || state == 4) {                             \
                sub_8082E1C(part, kind, command, 0);                    \
                flags = (u8 *)FIELD(part, void *, 8) + 0x12;           \
                flag_value = *flags;                                    \
                mask = -7;                                              \
                flag_value &= mask;                                     \
                flag_value |= 2;                                        \
                *flags = flag_value;                                    \
            }                                                            \
            FIELD(object, void *, 0x4C) = next;                         \
        }                                                                \
    }

DEFINE_ACTOR_INTERACTION_TRANSITION(sub_80A3ABC, 0x70, 5, 0x2024, sub_80A3810)
DEFINE_ACTOR_INTERACTION_TRANSITION(sub_80A49A8, 0x74, 5, 0x2053, sub_80A46FC)
DEFINE_ACTOR_INTERACTION_TRANSITION(sub_80A4A10, 0x74, 0, 0x2053, sub_80A3DF0)
DEFINE_ACTOR_INTERACTION_TRANSITION(sub_80B9504, 0x74, 0, 0x205E, sub_80B363C)
