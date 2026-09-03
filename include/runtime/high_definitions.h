#ifndef GUARD_RUNTIME_HIGH_DEFINITIONS_H
#define GUARD_RUNTIME_HIGH_DEFINITIONS_H

#include "global.h"

#define runtime_call_with_mode_1 sub_81DA85C
#define runtime_get_definition_bd64_target sub_81DD2E0
#define runtime_destroy_definition_cf50 sub_81DD670
#define runtime_call_default_initializer sub_81DD690
#define runtime_initialize_definition_d0 sub_81DD69C

u16 runtime_call_with_mode_1(u16 value, u32 argument);
void* runtime_get_definition_bd64_target(void);
void runtime_destroy_definition_cf50(void* object, u32 flags);
void runtime_call_default_initializer(void);
void runtime_initialize_definition_d0(void* object);

#endif
