#include "global.h"

void sub_8021ED8(void *);

void sub_8051330(u8 *object)
{
    if (*(s16 *)(object + 0x340) != 0) {
        object[0x23B] = 0;
        *(s16 *)(object + 0x33E) &= ~0x1FE;
    }
}

void sub_8051368(u8 *object)
{
    object[0x20F] |= 2;
    sub_8021ED8(*(void **)(object + 0x294));
    object[0x23D] = 7;
}
