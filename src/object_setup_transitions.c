#include "global.h"

#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.object_setup_transitions." #name)))

extern void sub_8082E1C(void *, s32, s32, s32);

#define DEFINE_OBJECT_SETUP(name, kind, delay, next)                     \
    extern void next(void);                                              \
    SEC(name) void name(void *object)                                    \
    {                                                                    \
        s32 mask;                                                        \
        s32 flag_value;                                                  \
        volatile u8 *flags;                                              \
        sub_8082E1C(object, kind, 0, 0);                                \
        flags = (u8 *)FIELD(object, void *, 8) + 0x12;                  \
        flag_value = *flags;                                             \
        mask = -7;                                                       \
        flag_value &= mask;                                              \
        *flags = flag_value;                                             \
        FIELD(object, u16, 0xAC) = delay;                               \
        FIELD(object, void *, 0x4C) = next;                             \
    }

DEFINE_OBJECT_SETUP(sub_808C62C, 7, 0x2D, sub_808C7B8)
DEFINE_OBJECT_SETUP(sub_808C65C, 3, 0x2D, sub_808C7E4)
DEFINE_OBJECT_SETUP(sub_808C68C, 7, 0x2D, sub_808C810)
DEFINE_OBJECT_SETUP(sub_808C724, 8, 0x0C, sub_808C8E0)
DEFINE_OBJECT_SETUP(sub_808C754, 3, 0x0C, sub_808C90C)
