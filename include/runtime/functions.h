#ifndef GUARD_RUNTIME_FUNCTIONS_H
#define GUARD_RUNTIME_FUNCTIONS_H

#include "global.h"

typedef void (*InterruptCallback)(void);

/* Semantic C names mapped to original symbols still referenced by assembly. */
#define game_state_set_play_time sub_8018A4C
#define runtime_noop_interrupt_callback nullsub_16
#define runtime_install_interrupt_callback sub_8018B78
#define runtime_clear_state_3000d28 sub_801AE1C

void game_state_set_play_time(u32 playTime);
void runtime_noop_interrupt_callback(void);
void runtime_install_interrupt_callback(int interrupt, InterruptCallback callback);
void runtime_clear_state_3000d28(void);

#endif
