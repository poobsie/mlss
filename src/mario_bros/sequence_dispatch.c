#include "global.h"
#include "mario_bros/callback.h"
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

DEFINE_GLOBAL_TABLE_CALL(sub_8F55174, gMarioData_08F9F054)
DEFINE_GLOBAL_TABLE_CALL(sub_8F55C90, gMarioData_08F9F11C)
DEFINE_GLOBAL_TABLE_CALL(sub_8F5CBA4, gMarioData_08F9FA64)
