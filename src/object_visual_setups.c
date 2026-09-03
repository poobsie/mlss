#include "global.h"

#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.object_visual_setups." #name)))

extern void sub_8082E1C(void *, s32, s32, s32);

#define DEFINE_OBJECT_VISUAL_SETUP(name, sprite_value, state, next)      \
    extern void next(void);                                              \
    SEC(name) s32 name(void *object)                                     \
    {                                                                    \
        volatile u8 *flags;                                              \
        s32 flag_value;                                                  \
        s32 mask;                                                        \
        void *display;                                                   \
        FIELD(object, s32, 0x6C) = 0x084FE9A4;                          \
        display = (u8 *)(*(void **)0x03000FF4) + 0x3C;                 \
        flags = (u8 *)object + 0x77;                                    \
        flag_value = *flags;                                             \
        mask = -0x41;                                                    \
        flag_value &= mask;                                              \
        mask = -0x21;                                                    \
        flag_value &= mask;                                              \
        *flags = flag_value;                                             \
        FIELD(FIELD(object, void *, 0x28), s32, 0x114) =                \
            FIELD(display, u16, 0x2A);                                  \
        sub_8082E1C(object, 4, 0x204D, 0);                              \
        FIELD(FIELD(object, void *, 8), u8, 0x20) = sprite_value;       \
        FIELD(object, s32, 0x9C) = state;                               \
        FIELD(object, void *, 0x4C) = next;                             \
        return 1;                                                        \
    }

DEFINE_OBJECT_VISUAL_SETUP(sub_808ED40, 0x30, 2, sub_808EE0C)
DEFINE_OBJECT_VISUAL_SETUP(sub_808FD3C, 0x10, 6, sub_808FE08)
DEFINE_OBJECT_VISUAL_SETUP(sub_8090AB4, 0x60, 1, sub_8090B80)
