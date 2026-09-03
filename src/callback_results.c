#include "global.h"

#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.callback_results." #name)))

#define DEFINE_CALLBACK_RESULT(name, next)                               \
    extern void next(void);                                              \
    SEC(name) s32 name(void *object)                                     \
    {                                                                    \
        FIELD(object, void *, 0x4C) = next;                             \
        return 1;                                                        \
    }

DEFINE_CALLBACK_RESULT(sub_8099028, sub_8099034)
DEFINE_CALLBACK_RESULT(sub_80993BC, sub_80993C8)
