#include "field/runtime_link_nodes.h"

#define FIELD_RUNTIME (*(u8**)0x03000FD8)
#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(symbol) __attribute__((section(".text.field_runtime_link_nodes." STRINGIFY(symbol))))

typedef void (*FieldRuntimeMemset)(u32 value, void* destination, u32 size);
#define FIELD_RUNTIME_MEMSET (*(FieldRuntimeMemset*)0x03001034)

SEC(field_runtime_allocate_link_node)
struct FieldRuntimeLinkNode* field_runtime_allocate_link_node(void)
{
    register u8* runtime asm("r3") = FIELD_RUNTIME;
    register struct FieldRuntimeLinkNode** freeHead asm("r2") =
        (struct FieldRuntimeLinkNode**)(runtime + 0x238);
    register struct FieldRuntimeLinkNode* node asm("r0") = *freeHead;
    register struct FieldRuntimeLinkNode** activeHead asm("r2");
    register u8 flags asm("r2");
    register u32 mask asm("r1");

    *freeHead = node->next;
    activeHead = (struct FieldRuntimeLinkNode**)(runtime + 0x23C);
    node->next = *activeHead;
    *activeHead = node;
    flags = node->flags0C;
    mask = -0x20;
    mask &= flags;
    node->flags0C = mask;
    return node;
}

SEC(field_runtime_attach_link_node)
struct FieldRuntimeLinkNode* field_runtime_attach_link_node(struct FieldRuntimeLinkOwner* owner)
{
    register struct FieldRuntimeLinkOwner* current asm("r3") = owner;
    register u8* runtime asm("r12") = FIELD_RUNTIME;
    register struct FieldRuntimeLinkNode** freeHead asm("r2") =
        (struct FieldRuntimeLinkNode**)(runtime + 0x238);
    register struct FieldRuntimeLinkNode* node asm("r0") = *freeHead;
    register struct FieldRuntimeLinkNode** activeHead asm("r2");
    register u8 flags asm("r2");
    register u32 mask asm("r1");

    *freeHead = node->next;
    activeHead = (struct FieldRuntimeLinkNode**)(runtime + 0x23C);
    node->next = *activeHead;
    *activeHead = node;
    flags = node->flags0C;
    mask = -0x20;
    mask &= flags;
    node->flags0C = mask;
    current->node04 = node;
    node->value04 = current->value08;
    node->value08 = current->payload0C;
    return node;
}

SEC(field_runtime_allocate_payload_node)
struct FieldRuntimePayloadNode* field_runtime_allocate_payload_node(void* value04, void* value08,
                                                                    void* value0C)
{
    struct FieldRuntimePayloadNode** freeHead =
        (struct FieldRuntimePayloadNode**)(FIELD_RUNTIME + 0x240);
    struct FieldRuntimePayloadNode* node = *freeHead;

    *freeHead = node->next;
    FIELD_RUNTIME_MEMSET(0, node, sizeof(*node));
    node->value04 = value04;
    node->value08 = value08;
    node->value0C = value0C;
    return node;
}

SEC(field_runtime_allocate_empty_payload_node)
struct FieldRuntimePayloadNode* field_runtime_allocate_empty_payload_node(void)
{
    struct FieldRuntimePayloadNode** freeHead =
        (struct FieldRuntimePayloadNode**)(FIELD_RUNTIME + 0x240);
    struct FieldRuntimePayloadNode* node = *freeHead;

    *freeHead = node->next;
    FIELD_RUNTIME_MEMSET(0, node, sizeof(*node));
    return node;
}
