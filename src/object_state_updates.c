#include "global.h"
#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.object_state_updates." #name)))

#define DEFINE_VISUAL_STATE_UPDATE(name, next)                        \
    extern void next(void *);                                         \
    SEC(name) s32 name(void *object)                                  \
    {                                                                 \
        s8 *flags;                                                     \
        void *state;                                                   \
        FIELD(object, void *, 0x6C) = (void *)0x084FE8A8;            \
        state = *(void **)0x03000FF4;                                 \
        flags = (s8 *)object + 0x77;                                  \
        *flags &= ~0x40;                                               \
        *flags &= ~0x20;                                               \
        FIELD(FIELD(object, void *, 0x28), u32, 0x114) =              \
            FIELD(state, u16, 0x2A);                                  \
        FIELD(object, void *, 0x4C) = next;                           \
        return 1;                                                     \
    }
DEFINE_VISUAL_STATE_UPDATE(sub_8090420, sub_80904C4)
DEFINE_VISUAL_STATE_UPDATE(sub_809078C, sub_8090830)
