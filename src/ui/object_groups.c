#include "global.h"
#include "ui/object.h"

#define SEC(name) __attribute__((section(".text.ui_groups." #name)))
#define PAD(name) SEC(name) const u16 name##_padding = 0

struct UiObjectGrid {
    u32 unknown00;
    struct UiObject* objects[6];
};

struct UiObjectNode {
    u8 unknown00[8];
    struct UiObjectNode* next;
};

struct UiObjectNodeList {
    struct UiObjectNode* head;
};

extern void sub_8161C9C(struct UiObjectNode* object, u32 mode, u32 value);

SEC(sub_8163650)
void sub_8163650(struct UiObjectGrid* grid, u32 row, u32 column) {
    struct UiObject* object;

    column--;
    object = grid->objects[row * 3 + column];

    object->value44 = (void*)0x08212934;
    object->counter48 = 0;
    object->state40 = 0;
}

SEC(sub_8163864)
void sub_8163864(struct UiObjectNodeList* list, u32 mode, u32 value) {
    struct UiObjectNode* object = list->head;

    while (object != 0) {
        sub_8161C9C(object, mode, value);
        object = object->next;
    }
}
PAD(sub_8163864);
