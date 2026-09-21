#include "global.h"
#include "ui/object.h"

#define SEC(name) __attribute__((section(".text.ui_groups." #name)))
#define PAD(name) SEC(name) const u16 name##_padding = 0

struct UiObjectNode {
    u8 unknown00[8];
    struct UiObjectNode* next;
};

struct UiObjectNodeList {
    struct UiObjectNode* head;
};

extern void sub_8161C9C(void* object, u32 mode, u32 value);
extern void sub_8161E38(void* object);
extern void free_heap_8018DA8(void* pointer);

#define DESTROY_UI_OBJECT(object_)                                      \
    do {                                                                \
        struct UiObject* object = (object_);                             \
        if (object != 0) {                                              \
            const struct UiObjectVtable* vtable = object->vtable;       \
            vtable->destructor(                                         \
                (u8*)object + vtable->destructorThisAdjustment, 3);     \
        }                                                               \
    } while (0)

SEC(sub_8163528)
void sub_8163528(struct UiObjectGroup4* group, u32 flags) {
    DESTROY_UI_OBJECT(group->objects[0]);
    DESTROY_UI_OBJECT(group->objects[1]);
    DESTROY_UI_OBJECT(group->objects[2]);
    DESTROY_UI_OBJECT(group->objects[3]);
    if (flags & 1)
        free_heap_8018DA8(group);
}
PAD(sub_8163528);

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

    object->visualDefinition = (const void*)0x08212934;
    object->visualStepIndex = 0;
    object->visualState = 0;
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
