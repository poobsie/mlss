#ifndef GUARD_RUNTIME_DEFINITION_STATE_H
#define GUARD_RUNTIME_DEFINITION_STATE_H

#include "global.h"

struct DefinitionState {
    u32 state;
    const void* definition;
    u32 value08;
    u32 value0C;
    u32 value10;
    u32 value14;
};

#define definition_state_initialize_family_a sub_815817C
#define definition_state_reset_family_a sub_8158198
#define definition_state_initialize_family_b sub_815E9EC
#define definition_state_reset_family_b sub_815EA08

struct DefinitionState* definition_state_initialize_family_a(
    struct DefinitionState* state);
struct DefinitionState* definition_state_reset_family_a(
    struct DefinitionState* state);
struct DefinitionState* definition_state_initialize_family_b(
    struct DefinitionState* state);
struct DefinitionState* definition_state_reset_family_b(
    struct DefinitionState* state);

#endif
