#ifndef GUARD_FIELD_RUNTIME_NODE_TRANSITION_H
#define GUARD_FIELD_RUNTIME_NODE_TRANSITION_H

#include "global.h"

struct FieldRuntimeNodeTransition {
    u8 unknown00[4];
    void (*callback)(struct FieldRuntimeNodeTransition* transition);
    u8 unknown08[4];
    void* value0C;
    u8 unknown10[2];
    s16 value12;
};

#define field_when_ready_push_runtime_node_and_continue sub_8106BB0

void field_when_ready_push_runtime_node_and_continue(
    struct FieldRuntimeNodeTransition* transition);

#endif
