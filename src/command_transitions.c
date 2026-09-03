#include "global.h"
#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.command_transitions." #name)))
extern void sub_8082E1C(void *, s32, s32, s32);
#define DEFINE_COMMAND_TRANSITION(name, kind, command, next)             \
    extern void next(void);                                              \
    SEC(name) void name(void *object)                                    \
    {                                                                    \
        s32 mask; s32 flag_value; volatile u8 *flags;                   \
        sub_8082E1C(object, kind, command, 0);                           \
        flags = (u8 *)FIELD(object, void *, 8) + 0x12;                 \
        flag_value = *flags; mask = -7; flag_value &= mask;             \
        flag_value |= 2; *flags = flag_value;                           \
        FIELD(object, void *, 0x4C) = next;                             \
    }
DEFINE_COMMAND_TRANSITION(sub_809B038, 2, 0x40BE, sub_809B068)
DEFINE_COMMAND_TRANSITION(sub_809C448, 11, 0x40BF, sub_809C4F8)
