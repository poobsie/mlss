#include "field/runtime_nodes.h"

struct FieldRuntimeNodeLists {
    u8 unknown00[0x3C];
    struct FieldRuntimeNode* freeNodes;
    struct FieldRuntimeNode* list40;
    struct FieldRuntimeNode* list44;
    struct FieldRuntimeNode* list48;
    struct FieldRuntimeNode* list4C;
    struct FieldRuntimeNode* list50;
    u8 unknown54[0x1EC];
    struct FieldRuntimeNode* pool240;
};

#define FIELD_RUNTIME_NODE_LISTS (*(struct FieldRuntimeNodeLists**)0x03000FD8)
#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(symbol) __attribute__((section(".text.field_runtime_nodes." STRINGIFY(symbol))))

struct FieldRuntimeObject79 {
    u8 unknown00[0x79];
    u8 flags79;
};

void sub_807FEB4(struct FieldRuntimeNode* node);

#define DEFINE_PUSH_NODE_WITH_VALUE(symbol, member)                                  \
    SEC(symbol) struct FieldRuntimeNode* symbol(void* ownerOrCallback, void* value)  \
    {                                                                                 \
        register void* owner asm("r4") = ownerOrCallback;                              \
        register struct FieldRuntimeNodeLists* runtime asm("r3") =                    \
            FIELD_RUNTIME_NODE_LISTS;                                                  \
        register struct FieldRuntimeNode* node asm("r0") = runtime->freeNodes;         \
        runtime->freeNodes = node->next;                                               \
        node->next = runtime->member;                                                  \
        node->ownerOrCallback = owner;                                                 \
        node->counter10 = 0;                                                           \
        runtime->member = node;                                                        \
        node->value = value;                                                           \
        return node;                                                                   \
    }

SEC(field_runtime_recycle_pool_240_node)
struct FieldRuntimeNode* field_runtime_recycle_pool_240_node(struct FieldRuntimeNode* node)
{
    register struct FieldRuntimeNode* current asm("r3") = node;
    register struct FieldRuntimeNode* next asm("r0");
    register struct FieldRuntimeNode** pool asm("r1");

    if (current != NULL) {
        next = current->next;
        pool = (struct FieldRuntimeNode**)((u8*)FIELD_RUNTIME_NODE_LISTS + 0x240);
        current->next = *pool;
        *pool = current;
    } else {
        next = NULL;
    }
    return next;
}
SEC(field_runtime_recycle_pool_240_node)
const u16 field_runtime_recycle_pool_240_node_padding = 0;

SEC(field_runtime_push_object_node_list_4c)
void field_runtime_push_object_node_list_4c(void* object)
{
    struct FieldRuntimeObject79* runtimeObject = object;
    struct FieldRuntimeNodeLists* runtime;
    struct FieldRuntimeNode* node;
    void* callback;
    register u32 zero asm("r1");
    register u8 flags asm("r1");
    register u32 flagMask asm("r2");

    flags = runtimeObject->flags79;
    flagMask = 0x10;
    flags |= flagMask;
    runtimeObject->flags79 = flags;
    runtime = FIELD_RUNTIME_NODE_LISTS;
    callback = sub_807FEB4;
    node = runtime->freeNodes;
    runtime->freeNodes = node->next;
    node->next = runtime->list4C;
    node->ownerOrCallback = callback;
    zero = 0;
    node->counter10 = zero;
    runtime->list4C = node;
    node->value = object;
}

#define DEFINE_PUSH_NODE(symbol, member)                                              \
    SEC(symbol) struct FieldRuntimeNode* symbol(void* ownerOrCallback)                \
    {                                                                                 \
        register void* owner asm("r3") = ownerOrCallback;                              \
        register struct FieldRuntimeNodeLists* runtime asm("r2") =                    \
            FIELD_RUNTIME_NODE_LISTS;                                                  \
        register struct FieldRuntimeNode* node asm("r0") = runtime->freeNodes;         \
        runtime->freeNodes = node->next;                                               \
        node->next = runtime->member;                                                  \
        node->ownerOrCallback = ownerOrCallback;                                       \
        node->counter10 = 0;                                                           \
        runtime->member = node;                                                        \
        return node;                                                                   \
    }

DEFINE_PUSH_NODE_WITH_VALUE(field_runtime_push_node_list_50, list50)
DEFINE_PUSH_NODE_WITH_VALUE(field_runtime_push_node_list_4c, list4C)
DEFINE_PUSH_NODE_WITH_VALUE(field_runtime_push_node_list_48, list48)
DEFINE_PUSH_NODE(field_runtime_push_node_list_44, list44)
DEFINE_PUSH_NODE(field_runtime_push_node_list_40, list40)

SEC(field_runtime_push_external_node)
struct FieldRuntimeNode* field_runtime_push_external_node(struct FieldRuntimeNode** head,
                                                          void* ownerOrCallback)
{
    register struct FieldRuntimeNode** listHead asm("r4") = head;
    register struct FieldRuntimeNodeLists* runtime asm("r3") = FIELD_RUNTIME_NODE_LISTS;
    register struct FieldRuntimeNode* node asm("r0") = runtime->freeNodes;
    runtime->freeNodes = node->next;
    node->next = *listHead;
    node->ownerOrCallback = ownerOrCallback;
    node->counter10 = 0;
    *listHead = node;
    return node;
}
