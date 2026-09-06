#include "field/runtime_resource_teardown.h"
#include "field/runtime_nodes.h"
#include "graphics/linked_visual.h"

#define SEC(symbol) __attribute__((section(".text.field_runtime_resource_teardown." #symbol)))
#define FIELD_RUNTIME (*(struct FieldResourceRuntime**)0x03000FD8)
#define FIELD_DISPATCH (*(struct FieldResourceDispatch**)0x03000FDC)

struct FieldRuntimeResourceOwner {
    u8 unknown00[4];
    struct GraphicsLinkedVisual* visual04;
    struct FieldRuntimeNode* nodes08;
};

struct FieldResourceRuntime {
    u8 unknown000[0x364];
    struct FieldRuntimeResourceOwner* resourceOwner364;
};

struct FieldResourceDispatch {
    u8 unknown0000[0x8E58];
    void (*callback8E58)(struct FieldRuntimeResourceTeardown* teardown);
};

SEC(sub_8106EE8)
void field_release_runtime_resource_and_continue(
    struct FieldRuntimeResourceTeardown* teardown)
{
    struct FieldRuntimeNode* node;
    struct FieldRuntimeResourceOwner** ownerSlot;

    ownerSlot = &FIELD_RUNTIME->resourceOwner364;
    node = (*ownerSlot)->nodes08;
    while (node != 0)
        node = field_runtime_recycle_pool_240_node(node);

    graphics_destroy_linked_visual((*ownerSlot)->visual04);
    (*ownerSlot)->visual04 = 0;
    *ownerSlot = 0;
    teardown->callback = FIELD_DISPATCH->callback8E58;
}
