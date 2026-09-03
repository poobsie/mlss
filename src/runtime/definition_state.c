#include "runtime/definition_state.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)

#define DEFINE_INITIALIZER(name, definitionValue)                         \
    struct DefinitionState* name(struct DefinitionState* state)           \
        __attribute__((section(".text." STRINGIFY(name))));              \
    struct DefinitionState* name(struct DefinitionState* state) {         \
        state->state = 0;                                                  \
        state->definition = (const void*)(definitionValue);                \
        state->value08 = 0;                                                \
        state->value0C = 0;                                                \
        state->value10 = 0x7E00;                                           \
        state->value14 = 0;                                                \
        return state;                                                      \
    }

DEFINE_INITIALIZER(definition_state_initialize_family_a, 0x08CDC570)
DEFINE_INITIALIZER(definition_state_initialize_family_b, 0x08CDCAD0)

#define DEFINE_RESET(name, definitionValue)                               \
    struct DefinitionState* name(struct DefinitionState* state)           \
        __attribute__((section(".text." STRINGIFY(name))));              \
    struct DefinitionState* name(struct DefinitionState* state) {         \
        state->definition = (const void*)(definitionValue);                \
        state->state = 0;                                                  \
        return state;                                                      \
    }

DEFINE_RESET(definition_state_reset_family_a, 0x08CDCA30)
DEFINE_RESET(definition_state_reset_family_b, 0x08CDCF50)
