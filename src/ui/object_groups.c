#include "global.h"
#include "ui/object.h"

#define SEC(name) __attribute__((section(".text.ui_groups." #name)))
#define PAD(name) SEC(name) const u16 name##_padding = 0

struct UiObjectGrid {
    u32 unknown00;
    struct UiObject* objects[6];
};

struct UiObjectGroup4 {
    struct UiObject* objects[4];
};

struct UiObjectNode {
    u8 unknown00[8];
    struct UiObjectNode* next;
};

struct UiObjectNodeList {
    struct UiObjectNode* head;
};

extern void sub_8161C9C(void* object, u32 mode, u32 value);
extern void sub_8161E38(void* object);

SEC(sub_81634DC)
void sub_81634DC(struct UiObjectGroup4* group) {
    sub_8161E38(group->objects[0]);
    sub_8161C9C(group->objects[0], 0, 0);
    sub_8161E38(group->objects[1]);
    sub_8161C9C(group->objects[1], 0, 0);
    sub_8161E38(group->objects[2]);
    sub_8161C9C(group->objects[2], 0, 0);
    sub_8161E38(group->objects[3]);
    sub_8161C9C(group->objects[3], 0, 0);
}
PAD(sub_81634DC);

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
