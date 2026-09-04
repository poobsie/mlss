#include "global.h"

#define SEC(name) __attribute__((section(".text.runtime_bitset." #name)))

struct RuntimeBitset {
    u8 unknown00[0x20];
    u32 words[1];
};

#define RUNTIME_BITSET (*(struct RuntimeBitset**)0x03000FC0)

SEC(sub_8163110)
u32 sub_8163110(u16 bit) {
    u32 shift = bit & 31;
    struct RuntimeBitset* bitset = RUNTIME_BITSET;

    return (bitset->words[bit >> 5] >> shift) & 1;
}

SEC(sub_8163134)
void sub_8163134(u16 bit, u8 value) {
    u32* word = &RUNTIME_BITSET->words[bit >> 5];
    u32 mask = 1 << (bit & 31);

    *word = (*word & ~mask) | ((value & 1) << (bit & 31));
}
