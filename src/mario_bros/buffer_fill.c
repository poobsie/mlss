#include "global.h"

#define MB_SECTION(name) __attribute__((section(".text.mariobros_helpers_" #name)))

MB_SECTION(sub_8F585B0) void sub_8F585B0(u16 value, u16* dst) {
    u16 i = 0;
    do {
        *dst++ = value;
        i++;
    } while (i <= 0x3FF);
}
