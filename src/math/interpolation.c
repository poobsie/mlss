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
