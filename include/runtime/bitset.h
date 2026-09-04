#ifndef GUARD_RUNTIME_BITSET_H
#define GUARD_RUNTIME_BITSET_H

#include "global.h"

#define runtime_bitset_test sub_8163110
#define runtime_bitset_assign sub_8163134

u32 runtime_bitset_test(u16 bit);
void runtime_bitset_assign(u16 bit, u8 value);

#endif
