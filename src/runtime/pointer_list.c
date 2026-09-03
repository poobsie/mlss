#include "runtime/pointer_list.h"

u32 pointer_list_count_value(struct PointerList* list, void* value)
    __attribute__((section(".text.sub_8163BC4")));
u32 pointer_list_count_value(struct PointerList* list, void* value) {
    struct PointerListNode* node = list->head;
    u32 count = 0;

    while (node != 0) {
        if (node->value == value) {
            count++;
        }
        node = node->next;
    }
    return count;
}

__attribute__((section(".text.sub_8163BC4")))
const u16 pointer_list_count_value_padding = 0;
