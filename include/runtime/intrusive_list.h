#ifndef GUARD_RUNTIME_INTRUSIVE_LIST_H
#define GUARD_RUNTIME_INTRUSIVE_LIST_H

#include "global.h"

#define runtime_intrusive_list_append_unique sub_8163CD4
#define runtime_intrusive_list_owner_destroy_a sub_8163888
#define runtime_intrusive_list_owner_destroy_b sub_8163D10
#define runtime_intrusive_list_detach sub_8163C94

struct RuntimeIntrusiveNode {
    void* value00;
    struct RuntimeIntrusiveNode* previous;
    struct RuntimeIntrusiveNode* next;
};

struct RuntimeIntrusiveList {
    struct RuntimeIntrusiveNode* head;
    struct RuntimeIntrusiveNode* tail;
    s32 count;
};

struct RuntimeIntrusiveListOwner {
    struct RuntimeIntrusiveList list;
    const void* vtable;
};

void runtime_intrusive_list_append_unique(
    struct RuntimeIntrusiveList* list,
    struct RuntimeIntrusiveNode* node);
void runtime_intrusive_list_owner_destroy_a(
    struct RuntimeIntrusiveListOwner* owner, u32 flags);
void runtime_intrusive_list_owner_destroy_b(
    struct RuntimeIntrusiveListOwner* owner, u32 flags);
void runtime_intrusive_list_detach(struct RuntimeIntrusiveList* list,
                                   struct RuntimeIntrusiveNode* node);

#endif
