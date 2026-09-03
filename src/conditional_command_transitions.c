#include "global.h"
#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.conditional_command_transitions." #name)))
extern void sub_8082E1C(void *, s32, s32, s32);
#define DEFINE_CONDITIONAL_COMMAND_TRANSITION(name, command, next)       \
    extern void next(void);                                              \
    SEC(name) void name(void *object)                                    \
    {                                                                    \
        s32 mask; s32 flag_value; volatile u8 *flags;                   \
        if (FIELD(FIELD(object, void *, 8), u8, 0x12) & 8) {            \
            sub_8082E1C(object, 3, command, 0);                          \
            flags = (u8 *)FIELD(object, void *, 8) + 0x12;             \
            flag_value = *flags; mask = -7; flag_value &= mask;         \
            flag_value |= 2; *flags = flag_value;                       \
            FIELD(object, void *, 0x4C) = next;                         \
        }                                                                \
    }
DEFINE_CONDITIONAL_COMMAND_TRANSITION(sub_809B068, 0x40BE, sub_809B0A8)
DEFINE_CONDITIONAL_COMMAND_TRANSITION(sub_809B920, 0x40C2, sub_809BA28)
