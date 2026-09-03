#include "global.h"

#define SEC(name) __attribute__((section(".text.countdown_handlers." #name)))
#define DEFINE_COUNTDOWN(name, next)                                                                   \
    extern void next(void);                                                                            \
    SEC(name) void name(void* object) {                                                                \
        s32 value = *(u16*)((u8*)object + 0xAC) - 1;                                                   \
        *(u16*)((u8*)object + 0xAC) = value;                                                           \
        if ((value << 16) <= 0)                                                                        \
            *(void (**)(void))((u8*)object + 0x4C) = next;                                             \
    }

DEFINE_COUNTDOWN(sub_80604E0, sub_808750C)
DEFINE_COUNTDOWN(sub_80708F8, sub_8070938)
DEFINE_COUNTDOWN(sub_8070918, sub_806F034)
DEFINE_COUNTDOWN(sub_807411C, sub_80744B4)
DEFINE_COUNTDOWN(sub_80746EC, sub_807470C)
