#include "global.h"

#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.actor_command_transitions." #name)))

extern void sub_8082E1C(void *, s32, s32, s32);

#define DEFINE_ACTOR_COMMAND(name, actor_offset, kind, command, next)     \
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
        if (FIELD(FIELD(part, void *, 8), u8, 0x12) & 8) {              \
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

DEFINE_ACTOR_COMMAND(sub_80C0B1C, 0x70, 4, 0x2024, sub_80BA6F8)
DEFINE_ACTOR_COMMAND(sub_80C8684, 0x74, 3, 0x2063, sub_80C33B0)
DEFINE_ACTOR_COMMAND(sub_80C8744, 0x74, 3, 0x2063, sub_80C26E4)
DEFINE_ACTOR_COMMAND(sub_80C87A4, 0x70, 8, 0x2034, sub_80C1CE4)
DEFINE_ACTOR_COMMAND(sub_80CCDEC, 0x70, 8, 0x2034, sub_80C9854)
