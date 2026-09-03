#include "global.h"

#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.conditional_setup_transitions." #name)))

extern void sub_8082E1C(void *, s32, s32, s32);

#define DEFINE_CONDITIONAL_SETUP_TRANSITION(name, kind, next)           \
    extern void next(void);                                              \
    SEC(name) void name(void *object)                                    \
    {                                                                    \
        if (FIELD(FIELD(object, void *, 8), u8, 0x12) & 8) {            \
            sub_8082E1C(object, kind, 0, 0);                            \
            FIELD(object, void *, 0x4C) = next;                         \
        }                                                                \
    }

DEFINE_CONDITIONAL_SETUP_TRANSITION(sub_8060438, 8, sub_8060544)
DEFINE_CONDITIONAL_SETUP_TRANSITION(sub_806048C, 5, sub_80605F8)
DEFINE_CONDITIONAL_SETUP_TRANSITION(sub_8064DDC, 0, sub_808750C)
