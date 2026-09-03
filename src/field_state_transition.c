#include "global.h"

#define AT(base, type, offset) (*(type *)((u8 *)(base) + (offset)))
#define SECTION(name) __attribute__((section(".text.field_state_transition." #name)))

struct __attribute__((packed)) LowThreeBits {
    u8 value : 3;
};

struct __attribute__((packed)) BitSix {
    u8 pad : 6;
    u8 value : 1;
    u8 rest : 1;
};

extern void sub_8049000(void *, s32);

SECTION(sub_804FCD4) void sub_804FCD4(void *object)
{
    s32 value;
    ((struct LowThreeBits *)((u8 *)object + 0x214))->value = 3;
    if (AT(object, u8, 0x54) == 0) {
        u8 *flag = (u8 *)object + 0x35B;
        s32 bit = *flag & 8;
        value = 0x1001;
        if (bit)
            value += 0x27;
    } else {
        value = 0x1002;
    }
    sub_8049000(object, value);
    AT(object, s16, 4) = 0;
    ((struct BitSix *)((u8 *)object + 0x212))->value = 0;
}
