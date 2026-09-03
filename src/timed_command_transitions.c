#include "global.h"
#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.timed_command_transitions." #name)))
extern void sub_8082E1C(void *, s32, s32, s32);
#define DEFINE_TIMED_COMMAND_TRANSITION(name, next)                       \
    extern void next(void *);                                            \
    SEC(name) void name(void *object)                                    \
    {                                                                    \
        s16 *timer = (s16 *)((u8 *)object + 0xAC);                      \
        u16 value = *(u16 *)timer;                                       \
        if (*timer > 0)                                                  \
            *(u16 *)timer = value - 1;                                  \
        else {                                                           \
            sub_8082E1C(object, 0, 0x4108, 0);                          \
            sub_8082E1C(FIELD(object, void *, 0x30), 6, 0x4109, 0);     \
            FIELD(object, void *, 0x4C) = next;                         \
        }                                                                \
    }
DEFINE_TIMED_COMMAND_TRANSITION(sub_809D454, sub_809CEB0)
DEFINE_TIMED_COMMAND_TRANSITION(sub_809D49C, sub_809CAF0)
