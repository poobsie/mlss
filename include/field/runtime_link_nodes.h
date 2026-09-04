#ifndef GUARD_FIELD_RUNTIME_LINK_NODES_H
#define GUARD_FIELD_RUNTIME_LINK_NODES_H

#include "global.h"

struct FieldRuntimeLinkNode {
    struct FieldRuntimeLinkNode* next;
    void* value04;
    void* value08;
    u8 flags0C;
};

struct FieldRuntimeLinkOwner {
    u8 unknown00[4];
    struct FieldRuntimeLinkNode* node04;
    void* value08;
    u8 payload0C[1];
};

struct FieldRuntimePayloadNode {
    struct FieldRuntimePayloadNode* next;
    void* value04;
    void* value08;
    void* value0C;
    u8 unknown10[0x0C];
};

#define field_runtime_attach_link_node sub_807FA14
#define field_runtime_allocate_link_node sub_807FA50
#define field_runtime_allocate_payload_node sub_807FABC
#define field_runtime_allocate_empty_payload_node sub_807FB04

struct FieldRuntimeLinkNode* field_runtime_attach_link_node(struct FieldRuntimeLinkOwner* owner);
struct FieldRuntimeLinkNode* field_runtime_allocate_link_node(void);
struct FieldRuntimePayloadNode* field_runtime_allocate_payload_node(void* value04, void* value08,
                                                                    void* value0C);
struct FieldRuntimePayloadNode* field_runtime_allocate_empty_payload_node(void);

#endif
