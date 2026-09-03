#include "global.h"

#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.landing_transitions." #name)))

extern void sub_8082E1C(void *, s32, s32, s32);

#define DEFINE_LANDING_TRANSITION(name, next)                            \
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
            sub_8082E1C(object, 8, 0x204D, 0);                          \
            FIELD(object, void *, 0x4C) = next;                         \
        }                                                                \
    }

DEFINE_LANDING_TRANSITION(sub_808EFFC, sub_808F0AC)
DEFINE_LANDING_TRANSITION(sub_808FFF8, sub_80900A8)
DEFINE_LANDING_TRANSITION(sub_8090608, sub_80906B8)
DEFINE_LANDING_TRANSITION(sub_8090974, sub_8090A24)
DEFINE_LANDING_TRANSITION(sub_8090D70, sub_8090E20)
