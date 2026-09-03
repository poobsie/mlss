#include "global.h"
#include "mario_bros/callback.h"
#include "mario_bros/functions.h"
#include "mario_bros/runtime.h"

#define SECTION(name) __attribute__((section(".text.mariobros_global_dispatch." #name)))

extern void *gMarioData_08F9F054[];
extern void *gMarioData_08F9F11C[];
extern void *gMarioData_08F9FA64[];

#define DEFINE_GLOBAL_TABLE_CALL(name, table) \
    SECTION(name) void name(void) \
    { \
        mario_bros_call_callback(table[gMarioGlobal_03000F50.sequenceIndex]); \
    }

DEFINE_GLOBAL_TABLE_CALL(mario_bros_dispatch_sequence_callback_a, gMarioData_08F9F054)
DEFINE_GLOBAL_TABLE_CALL(mario_bros_dispatch_sequence_callback_b, gMarioData_08F9F11C)
DEFINE_GLOBAL_TABLE_CALL(mario_bros_dispatch_sequence_callback_c, gMarioData_08F9FA64)
