#include "global.h"

#define SECTION(name) __attribute__((section(name)))

extern u8 byte_3000C28;
extern u32 dword_3000C6C;
extern u32 dword_3000C78;
extern u32 dword_80000F4;

SECTION(".text.runtime_helpers_tail")
int sub_80197C4(int limit) {
    int count = 0;
    int value = 1;

    do {
        count++;
        value *= 10;
    } while (value <= limit);
    return count;
}

SECTION(".text.runtime_helpers_tail")
void sub_80197E0(void) {
    byte_3000C28 = 0;
    dword_3000C6C = dword_80000F4;
    dword_3000C78 = 0;
}
