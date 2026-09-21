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
#define interpolate_s32_clamped sub_8163E0C
#define interpolate_s32_smoothstep_clamped sub_8163E50

void interpolation_configure(struct InterpolationState* state,
                             s32 initialValue, s16 duration, s16 targetValue);
void interpolation_clear(struct InterpolationState* state);
s32 interpolate_s32_clamped(
    s32 start, s32 end, s32 duration, s32 elapsed);
s32 interpolate_s32_smoothstep_clamped(
    s32 start, s32 end, s32 duration, s32 elapsed);

#endif
