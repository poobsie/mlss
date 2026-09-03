#include "global.h"

#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.script_transitions." #name)))

typedef void (*Callback)(void *);

#define DEFINE_SCRIPT_TRANSITION(name, next)                            \
    extern void next(void *);                                           \
    SEC(name) void name(void *object)                                   \
    {                                                                    \
        u8 *script = FIELD(object, u8 *, 0x0C);                         \
        FIELD(object, u16, 0x10) = *(u16 *)script;                      \
        FIELD(object, u8 *, 0x0C) = script + 2;                         \
        FIELD(object, Callback, 4) = next;                              \
        FIELD(object, Callback, 4)(object);                             \
    }

DEFINE_SCRIPT_TRANSITION(sub_80E1908, sub_80DF5EC)
DEFINE_SCRIPT_TRANSITION(sub_80E1924, sub_80E1AF0)
DEFINE_SCRIPT_TRANSITION(sub_80E1940, sub_80DF2B0)
