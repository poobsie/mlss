#include "field/runtime_node_transition.h"
#include "field/runtime_flags.h"
#include "field/runtime_nodes.h"

#define SEC(symbol) __attribute__((section(".text.field_runtime_node_transition." #symbol)))
#define FIELD_RUNTIME (*(u8**)0x03000FD8)

void sub_8102F54(struct FieldRuntimeNodeTransition* transition);
void sub_81071F0(void);

SEC(sub_8106BB0)
void field_when_ready_push_runtime_node_and_continue(
    struct FieldRuntimeNodeTransition* transition)
{
    struct FieldRuntimeNode* node;
    s32 value;

    if ((field_runtime_test_flag_10() << 24) != 0)
        return;

    node = field_runtime_push_external_node(
        (struct FieldRuntimeNode**)(FIELD_RUNTIME + 0x4C), sub_81071F0);
    value = transition->value12;
    node->value12 = value;
    node->unknown0C = transition->value0C;
    transition->callback = sub_8102F54;
}
