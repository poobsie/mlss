#ifndef GUARD_RUNTIME_POINTER_LIST_H
#define GUARD_RUNTIME_POINTER_LIST_H

#include "global.h"

struct PointerListNode {
    void* value;
    u32 unknown04;
    struct PointerListNode* next;
};

struct PointerList {
    struct PointerListNode* head;
};

#define pointer_list_count_value sub_8163BC4

u32 pointer_list_count_value(struct PointerList* list, void* value);

#endif
