#include "global.h"

#define DEFINE_NULLSUB(name)                                                \
    void name(void) __attribute__((section(".text." #name)));              \
    void name(void) {                                                       \
    }                                                                       \
    __attribute__((section(".text." #name))) const u16 name##_padding = 0

DEFINE_NULLSUB(nullsub_15);
DEFINE_NULLSUB(nullsub_3);
DEFINE_NULLSUB(nullsub_4);
DEFINE_NULLSUB(nullsub_8);
DEFINE_NULLSUB(nullsub_21);
DEFINE_NULLSUB(nullsub_7);
DEFINE_NULLSUB(nullsub_5);
DEFINE_NULLSUB(nullsub_6);
