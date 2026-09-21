#include "math/interpolation.h"

void interpolation_configure(struct InterpolationState* state,
                             s32 initialValue, s16 duration, s16 targetValue)
    __attribute__((section(".text.early_code_helpers.sub_801B748")));
void interpolation_configure(struct InterpolationState* state,
                             s32 initialValue, s16 duration, s16 targetValue) {
    state->initialValue = initialValue;
    state->duration = duration;
    state->targetValue = targetValue;
    state->accumulator = 0xFFFF0000;
}

void interpolation_clear(struct InterpolationState* state)
    __attribute__((section(".text.sub_801B75C")));
void interpolation_clear(struct InterpolationState* state) {
    state->initialValue = 0;
    state->duration = 0;
    state->targetValue = 0;
    state->accumulator = 0;
}

typedef s32 (*RuntimeSignedDivide)(s32 numerator, s32 denominator);

extern u8 loc_8198220[];
extern u8 loc_819832C[];

#define RUNTIME_DIVIDE \
    ((RuntimeSignedDivide)(*(u8**)0x03001038 + \
        (loc_819832C - loc_8198220)))

s32 interpolate_s32_clamped(s32 start, s32 end, s32 duration, s32 elapsed)
    __attribute__((section(".text.sub_8163E0C")));
s32 interpolate_s32_clamped(s32 start, s32 end, s32 duration, s32 elapsed)
{
    if (duration <= 0)
        duration = 1;
    if (elapsed < 0)
        elapsed = 0;
    if (elapsed > duration)
        elapsed = duration;
    return start + RUNTIME_DIVIDE((end - start) * elapsed, duration);
}
