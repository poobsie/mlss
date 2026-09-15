#ifndef GUARD_RUNTIME_RANDOM_H
#define GUARD_RUNTIME_RANDOM_H

#include "global.h"

#define runtime_random_u32 sub_8199F30
#define runtime_scale_random_u32 sub_81DD77C

u32 runtime_random_u32(void);
u32 runtime_scale_random_u32(u32 upperBound, u32 randomValue);

#endif
