#ifndef GUARD_RUNTIME_INTRUSIVE_LIST_H
#define GUARD_RUNTIME_INTRUSIVE_LIST_H

#include "global.h"

#define runtime_intrusive_list_append_unique sub_8163CD4

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

void runtime_intrusive_list_append_unique(
    struct RuntimeIntrusiveList* list,
    struct RuntimeIntrusiveNode* node);

#endif
