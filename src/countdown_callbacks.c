#include "global.h"
#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.countdown_callbacks." #name)))
extern void sub_807C298(void *);
#define DEFINE_COUNTDOWN_CALLBACK(name)                                  \
    SEC(name) void name(void *object)                                    \
    {                                                                    \
        s32 current = FIELD(object, u16, 0xAC) - 1;                     \
        FIELD(object, u16, 0xAC) = current;                             \
        if ((s32)(current << 16) <= 0)                                  \
            sub_807C298(object);                                         \
    }                                                                    \
    SEC(name) const u16 name##_padding = 0;
DEFINE_COUNTDOWN_CALLBACK(sub_8067874)
DEFINE_COUNTDOWN_CALLBACK(sub_8070A7C)
