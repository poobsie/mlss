#include "global.h"

#define SECTION(name) __attribute__((section(".text.mariobros_transitions." #name)))

struct __attribute__((packed)) LowTwoBits { u8 value : 2; };
struct __attribute__((packed)) TransitionBits {
    u8 low : 2;
    u8 enabled : 1;
    u8 middle : 4;
    u8 high : 1;
};

extern u8 sub_8F611F8(void *);
extern void sub_8F6DEA4(u32);

#define DEFINE_TRANSITION(name, code) \
    SECTION(name) void name(void *object) \
    { \
        if (sub_8F611F8(object)) { \
            ((struct LowTwoBits *)((u8 *)object + 8))->value = 2; \
            ((struct TransitionBits *)((u8 *)object + 10))->high = 0; \
            ((struct TransitionBits *)((u8 *)object + 10))->enabled = 1; \
            *((u8 *)object + 4) = 3; \
            sub_8F6DEA4(code); \
        } \
    }

DEFINE_TRANSITION(sub_8F6009C, 0x17)
DEFINE_TRANSITION(sub_8F60BA0, 0x16)
DEFINE_TRANSITION(sub_8F629AC, 0x15)
