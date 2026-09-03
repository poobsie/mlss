#include "global.h"

#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.landing_transitions_alternate." #name)))

extern void sub_8082E1C(void *, s32, s32, s32);

#define DEFINE_LANDING_ALT(name, next)                                   \
    extern void next(void);                                              \
    SEC(name) void name(void *object)                                    \
    {                                                                    \
        s16 *velocity = (s16 *)((u8 *)object + 0xB2);                    \
        u16 current;                                                     \
        s32 step;                                                        \
        s32 position;                                                    \
        s32 floor;                                                       \
        volatile u8 *flags;                                              \
        s32 flag_value;                                                  \
        s32 mask;                                                        \
        step = FIELD(object, s32, 0x94);                                \
        current = *velocity;                                             \
        current += step;                                                 \
        *velocity = current;                                             \
        position = FIELD(object, s32, 0x40) + *velocity;                \
        FIELD(object, s32, 0x18) = position;                            \
        floor = FIELD(FIELD(object, void *, 0x28), s32, 0xE0);          \
        if (position <= floor) {                                         \
            flags = (u8 *)object + 0x77;                                \
            flag_value = *flags;                                        \
            mask = -8;                                                   \
            flag_value &= mask;                                         \
            *flags = flag_value;                                        \
            FIELD(object, s32, 0x18) =                                  \
                FIELD(FIELD(object, void *, 0x28), s32, 0xE0);          \
            sub_8082E1C(object, 8, 0x2000, 0);                          \
            FIELD(object, void *, 0x4C) = next;                         \
        }                                                                \
    }

DEFINE_LANDING_ALT(sub_808F054, sub_808F0D8)
DEFINE_LANDING_ALT(sub_8090660, sub_80906E4)
DEFINE_LANDING_ALT(sub_80909CC, sub_8090A50)
DEFINE_LANDING_ALT(sub_8090DC8, sub_8090E4C)
