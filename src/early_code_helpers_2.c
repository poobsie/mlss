#include "global.h"

#define SECTION(name) __attribute__((section(".text." #name)))

void sub_80208E0(u8* object) SECTION(sub_80208E0);
void sub_80208E0(u8* object) {
    u32* target = *(u32**)(object + 0x48);
    target[0] = 1;
    target[1] = *(u32*)(object + 0x50);
    target[2] = *(u32*)(object + 0x4C);
    target[3] = 0;
}
