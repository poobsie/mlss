#include "global.h"
#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.delayed_cleanup_transitions." #name)))
extern void sub_808DD2C(void *);
#define DEFINE_DELAYED_CLEANUP_TRANSITION(name, limit)                   \
    SEC(name) void name(void *object)                                    \
    {                                                                    \
        void *child = FIELD(object, void *, 0x28);                      \
        if (child != 0)                                                  \
            FIELD(child, s8, 0x111) &= -5;                              \
        if (FIELD(object, u8, 0x76) & 0x38)                             \
            sub_808DD2C(object);                                         \
        else if (FIELD(object, s16, 0xAC)++ > limit)                    \
            sub_808DD2C(object);                                         \
    }
DEFINE_DELAYED_CLEANUP_TRANSITION(sub_808EBB8, 0x17)
DEFINE_DELAYED_CLEANUP_TRANSITION(sub_808FBB4, 0x17)
DEFINE_DELAYED_CLEANUP_TRANSITION(sub_808FC04, 0x13)
