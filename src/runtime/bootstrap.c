#include "global.h"
#include "math/decimal.h"
#include "runtime/memory.h"

#define SECTION(name) __attribute__((section(name)))

/*
 * This utility remains beside the runtime initializer because their original
 * code is contiguous and splitting the object changes alignment padding.
 */
SECTION(".text.runtime_bootstrap")
int decimal_digit_count(int limit) {
    int count = 0;
    int placeValue = 1;

    do {
        count++;
        placeValue *= 10;
    } while (placeValue <= limit);
    return count;
}

/* These names remain address-based until their wider users are decompiled. */
extern u8 byte_3000C28;
extern u32 dword_3000C6C;
extern u32 dword_3000C78;
extern u32 dword_80000F4;

SECTION(".text.runtime_bootstrap")
void runtime_memory_state_init(void) {
    byte_3000C28 = 0;
    dword_3000C6C = dword_80000F4;
    dword_3000C78 = 0;
}
