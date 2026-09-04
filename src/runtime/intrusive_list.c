#include "runtime/intrusive_list.h"

void free_heap_8018DA8(void* object);
void sub_8163BE4(struct RuntimeIntrusiveListOwner* owner);

#define DEFINE_LIST_OWNER_DESTRUCTOR(name, section_name)                    \
void name(struct RuntimeIntrusiveListOwner* owner, u32 flags)                \
    __attribute__((section(section_name)));                                  \
void name(struct RuntimeIntrusiveListOwner* owner, u32 flags) {              \
    owner->vtable = (const void*)0x08CDD108;                                 \
    sub_8163BE4(owner);                                                       \
    if (flags & 1)                                                           \
        free_heap_8018DA8(owner);                                            \
}

DEFINE_LIST_OWNER_DESTRUCTOR(runtime_intrusive_list_owner_destroy_a,
                             ".text.sub_8163888")
DEFINE_LIST_OWNER_DESTRUCTOR(runtime_intrusive_list_owner_destroy_b,
                             ".text.sub_8163D10")

#define SEC(name) __attribute__((section(".text.upper.sub_8163CD4")))

void runtime_intrusive_list_detach(struct RuntimeIntrusiveList* list,
                                   struct RuntimeIntrusiveNode* node)
    __attribute__((section(".text.sub_8163C94")));
void runtime_intrusive_list_detach(struct RuntimeIntrusiveList* list,
                                   struct RuntimeIntrusiveNode* node)
{
    if (node->previous != 0) {
        if (node->next != 0) {
            node->previous->next = node->next;
            node->next->previous = node->previous;
        } else {
            node->previous->next = 0;
            list->tail = node->previous;
        }
    } else {
        struct RuntimeIntrusiveNode* next = node->next;
        if (next != 0) {
            next->previous = 0;
            next = node->next;
        } else {
            list->tail = next;
        }
        list->head = next;
    }
    list->count--;
}
__attribute__((section(".text.sub_8163C94")))
const u16 runtime_intrusive_list_detach_padding = 0;

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
