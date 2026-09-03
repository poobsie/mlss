#include "global.h"

#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.countdown_transitions." #name)))

extern void sub_8082E1C(void *, s32, s32, s32);

#define DEFINE_COUNTDOWN_TRANSITION(name, kind, next)                   \
    extern void next(void);                                              \
    SEC(name) void name(void *object)                                    \
    {                                                                    \
        s32 current;                                                     \
        if (FIELD(FIELD(object, void *, 8), u8, 0x12) & 8) {            \
            current = FIELD(object, u16, 0xAC) - 1;                     \
            FIELD(object, u16, 0xAC) = current;                         \
            if ((s32)(current << 16) <= 0) {                            \
                sub_8082E1C(object, kind, 0, 0);                        \
                FIELD(object, void *, 0x4C) = next;                     \
            }                                                            \
        }                                                                \
    }

DEFINE_COUNTDOWN_TRANSITION(sub_805DF4C, 5, sub_805DA78)
DEFINE_COUNTDOWN_TRANSITION(sub_8063C8C, 13, sub_8063C60)
DEFINE_COUNTDOWN_TRANSITION(sub_806EADC, 11, sub_808750C)
