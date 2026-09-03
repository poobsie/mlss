#include "runtime/intrusive_list.h"

#define SEC(name) __attribute__((section(".text.upper.sub_8163CD4")))

SEC(runtime_intrusive_list_append_unique)
void runtime_intrusive_list_append_unique(
    struct RuntimeIntrusiveList* list,
    struct RuntimeIntrusiveNode* node)
{
    struct RuntimeIntrusiveNode* current = list->head;

    if (current != 0) {
search:
        if (current != node) {
            current = current->next;
            if (current == 0)
                goto append;
            goto search;
        }
    } else {
append:
        current = list->head;
        if (current == 0) {
            node->next = current;
            node->previous = current;
            list->tail = node;
            list->head = node;
        } else {
            list->tail->next = node;
            node->previous = list->tail;
            node->next = 0;
            list->tail = node;
        }
        list->count++;
    }
}
