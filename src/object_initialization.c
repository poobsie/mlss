#include "global.h"

#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.object_initialization." #name)))

#define DEFINE_OBJECT_INIT(name, next)                                   \
    extern void next(void);                                              \
    SEC(name) s32 name(void *object)                                     \
    {                                                                    \
        void *source;                                                    \
        volatile u8 *flags;                                              \
        s32 flag_value;                                                  \
        s32 mask;                                                        \
        FIELD(object, void *, 0x6C) = (void *)0x084FE9A4;               \
        source = (u8 *)*(void **)0x03000FF4 + 0x3C;                     \
        flags = (u8 *)object + 0x77;                                    \
        flag_value = *flags;                                             \
        mask = -0x41;                                                    \
        flag_value &= mask;                                              \
        mask = -0x21;                                                    \
        flag_value &= mask;                                              \
        *flags = flag_value;                                             \
        FIELD(FIELD(object, void *, 0x28), s32, 0x114) =                \
            FIELD(source, u16, 0x2A);                                   \
        FIELD(object, void *, 0x4C) = next;                             \
        return 1;                                                        \
    }

DEFINE_OBJECT_INIT(sub_808DD9C, sub_808DE44)
DEFINE_OBJECT_INIT(sub_80903DC, sub_8090460)
DEFINE_OBJECT_INIT(sub_8090748, sub_80907CC)
