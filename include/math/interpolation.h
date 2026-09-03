#ifndef GUARD_MATH_INTERPOLATION_H
#define GUARD_MATH_INTERPOLATION_H

#include "global.h"

struct InterpolationState {
    s32 initialValue;
    s16 duration;
    u16 unknown06;
    s32 targetValue;
    s32 accumulator;
};

#define interpolation_configure sub_801B748
#define interpolation_clear sub_801B75C

void interpolation_configure(struct InterpolationState* state,
                             s32 initialValue, s16 duration, s16 targetValue);
void interpolation_clear(struct InterpolationState* state);

#endif
