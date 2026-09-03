#include "global.h"

#define SECTION(name) __attribute__((section(".text." #name)))

void sub_801B75C(u8* object) SECTION(sub_801B75C);
void sub_801B75C(u8* object) {
    *(u32*)(object + 0) = 0;
    *(u16*)(object + 4) = 0;
    *(u32*)(object + 8) = 0;
    *(u32*)(object + 0xC) = 0;
}

void sub_80208E0(u8* object) SECTION(sub_80208E0);
void sub_80208E0(u8* object) {
    u32* target = *(u32**)(object + 0x48);
    target[0] = 1;
    target[1] = *(u32*)(object + 0x50);
    target[2] = *(u32*)(object + 0x4C);
    target[3] = 0;
}

void sub_8047784(u8* object) SECTION(sub_8047784);
void sub_8047784(u8* object) {
    object[0x20D] |= 0x10;
    object[0x217] |= 1;
}

void sub_804790C(u8* object, u8 value) SECTION(sub_804790C);
void sub_804790C(u8* object, u8 value) {
    object[0x239] = value;
    (*(u8**)(object + 0x294))[0x20] = value;
}

void sub_804794C(u8* object, u16 value) SECTION(sub_804794C);
void sub_804794C(u8* object, u16 value) {
    *(u16*)(object + 0x23E) = value;
}

void sub_8047994(u8* object) SECTION(sub_8047994);
void sub_8047994(u8* object) {
    object[0x2B5] &= 0x3F;
}

int sub_8047AF4(u8* object) SECTION(sub_8047AF4);
int sub_8047AF4(u8* object) {
    return (object[0x2B5] >> 3) & 1;
}
