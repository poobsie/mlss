#include "global.h"

#define SEC(name) __attribute__((section(".text.offset_reads." #name)))
#define DEFINE_OFFSET_READ(name, offset)                                 \
    SEC(name) s32 name(void *object)                                     \
    {                                                                    \
        return *(s16 *)((u8 *)object + offset);                          \
    }

DEFINE_OFFSET_READ(sub_8082D40, 0x776)
DEFINE_OFFSET_READ(sub_8082D50, 0x774)
