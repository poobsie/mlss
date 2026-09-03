#include "global.h"

#define AT(base, type, offset) (*(type *)((u8 *)(base) + (offset)))
#define SECTION(name) __attribute__((section(".text.field_state_preservation")))

struct __attribute__((packed)) LowBits {
    u8 value : 3;
};

#define LOW_BITS(base, offset) (((struct LowBits *)((u8 *)(base) + (offset)))->value)

extern void sub_8047804(void *, u8);
extern void sub_8047858(void *, u8);
extern void sub_80494D4(void *);
extern void sub_804FCD4(void *);

#define DEFINE_STATE_DISPATCH(name, finish) \
    SECTION(name) void name(void *object, u8 mode) \
    { \
        u16 state; \
        u32 saved214 = LOW_BITS(object, 0x214); \
        u32 saved24 = LOW_BITS(object, 0x24); \
        state = AT(object, u16, 4); \
        if ((u32)(u16)(state - 5) <= 4) \
            sub_804FCD4(object); \
        else if ((u32)(u16)(state - 10) <= 2) \
            sub_80494D4(object); \
        LOW_BITS(object, 0x214) = saved214; \
        LOW_BITS(object, 0x24) = saved24; \
        finish(object, mode); \
    }

DEFINE_STATE_DISPATCH(sub_804FD80, sub_8047804)
DEFINE_STATE_DISPATCH(sub_804FDF4, sub_8047858)

__attribute__((section(".text.field_state_preservation"))) const u16 field_state_padding = 0;
