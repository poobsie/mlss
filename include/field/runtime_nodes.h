#ifndef GUARD_FIELD_RUNTIME_NODES_H
#define GUARD_FIELD_RUNTIME_NODES_H

#include "global.h"

struct FieldRuntimeNode {
    struct FieldRuntimeNode* next;
    void* ownerOrCallback;
    void* value;
    u8 unknown0C[4];
    u16 counter10;
};

/*
 * The list roles are still unknown.  Their offsets are retained in the names
 * until their callbacks and consumers establish stronger semantics.
 */
#define field_runtime_push_node_list_50 sub_807FF20
#define field_runtime_push_node_list_4c sub_807FF48
#define field_runtime_push_node_list_48 sub_807FF70
#define field_runtime_push_node_list_44 sub_807FF98
#define field_runtime_push_node_list_40 sub_807FFB8
#define field_runtime_push_external_node sub_807FFD8
#define field_runtime_recycle_pool_240_node sub_807FA94
#define field_runtime_push_object_node_list_4c sub_807FE7C

struct FieldRuntimeNode* field_runtime_push_node_list_50(void* ownerOrCallback, void* value);
struct FieldRuntimeNode* field_runtime_push_node_list_4c(void* ownerOrCallback, void* value);
struct FieldRuntimeNode* field_runtime_push_node_list_48(void* ownerOrCallback, void* value);
struct FieldRuntimeNode* field_runtime_push_node_list_44(void* ownerOrCallback);
struct FieldRuntimeNode* field_runtime_push_node_list_40(void* ownerOrCallback);
struct FieldRuntimeNode* field_runtime_push_external_node(struct FieldRuntimeNode** head,
                                                          void* ownerOrCallback);
struct FieldRuntimeNode* field_runtime_recycle_pool_240_node(struct FieldRuntimeNode* node);
void field_runtime_push_object_node_list_4c(void* object);

#endif
