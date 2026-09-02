#include "global.h"

struct CallbackEntry {
    s16 offset;
    u16 pad2;
    int (*function)();
};

struct FieldObjectWrapper {
    u8 pad00[0x338];
    u8 *callbacks;
    u8 pad33C[8];
    struct FieldObjectWrapper *child;
};

int sub_8041FFC(struct FieldObjectWrapper *);
void sub_8047C68(struct FieldObjectWrapper *, int, u8);
void sub_8041A2C(struct FieldObjectWrapper *, int, int, u8);
void sub_8047CE8(struct FieldObjectWrapper *);
int sub_8041368(struct FieldObjectWrapper *, int, int);
void sub_80459C0(struct FieldObjectWrapper *);
void sub_8040FA0(struct FieldObjectWrapper *);
void sub_8040CF4(struct FieldObjectWrapper *, s16, s16, int);
void sub_8047FDC(struct FieldObjectWrapper *);
void sub_8040020(struct FieldObjectWrapper *);
void sub_8040AE0(struct FieldObjectWrapper *, int);
void sub_80409F4(struct FieldObjectWrapper *);
void sub_80403C4(struct FieldObjectWrapper *, int, int, int);

void sub_8050518(struct FieldObjectWrapper *object, int arg1, u8 arg2)
{
    struct FieldObjectWrapper *child;
    struct CallbackEntry *entry;

    sub_8047C68(object, arg1, arg2);
    child = object->child;
    if (child != 0) {
        entry = (struct CallbackEntry *)(child->callbacks + 0x70);
        entry->function((u8 *)child + entry->offset, arg1, arg2);
    }
}

int sub_8050554(struct FieldObjectWrapper *object)
{
    struct FieldObjectWrapper *child;
    struct CallbackEntry *entry;
    int result;

    result = sub_8041FFC(object);
    child = object->child;
    if (child != 0) {
        entry = (struct CallbackEntry *)(child->callbacks + 0x68);
        result = entry->function((u8 *)child + entry->offset);
    }
    return result;
}

void sub_8050584(struct FieldObjectWrapper *object, int arg1, int arg2, u8 arg3)
{
    struct FieldObjectWrapper *child;
    struct CallbackEntry *entry;

    sub_8041A2C(object, arg1, arg2, arg3);
    child = object->child;
    if (child != 0) {
        entry = (struct CallbackEntry *)(child->callbacks + 0x60);
        entry->function((u8 *)child + entry->offset, arg1, arg2, arg3);
    }
}

void sub_80505C4(struct FieldObjectWrapper *object)
{
    struct FieldObjectWrapper *child;
    struct CallbackEntry *entry;

    sub_8047CE8(object);
    child = object->child;
    if (child != 0) {
        entry = (struct CallbackEntry *)(child->callbacks + 0x58);
        entry->function((u8 *)child + entry->offset);
    }
}

int sub_80505F4(struct FieldObjectWrapper *object, int arg1, int arg2)
{
    struct FieldObjectWrapper *child;
    struct CallbackEntry *entry;
    int result;

    result = sub_8041368(object, arg1, arg2);
    child = object->child;
    if (child != 0) {
        entry = (struct CallbackEntry *)(child->callbacks + 0x50);
        result = entry->function((u8 *)child + entry->offset, arg1, arg2);
    }
    return result;
}

void sub_805062C(struct FieldObjectWrapper *object)
{
    struct FieldObjectWrapper *child;
    struct CallbackEntry *entry;

    sub_80459C0(object);
    child = object->child;
    if (child != 0) {
        entry = (struct CallbackEntry *)(child->callbacks + 0x88);
        entry->function((u8 *)child + entry->offset);
    }
}

void sub_805065C(struct FieldObjectWrapper *object)
{
    struct FieldObjectWrapper *child;
    struct CallbackEntry *entry;

    sub_8040FA0(object);
    child = object->child;
    if (child != 0) {
        entry = (struct CallbackEntry *)(child->callbacks + 0x48);
        entry->function((u8 *)child + entry->offset);
    }
}

void sub_805068C(struct FieldObjectWrapper *object, s16 arg1, s16 arg2, int arg3)
{
    struct FieldObjectWrapper *child;
    struct CallbackEntry *entry;

    sub_8040CF4(object, arg1, arg2, arg3);
    child = object->child;
    if (child != 0) {
        entry = (struct CallbackEntry *)(child->callbacks + 0x40);
        entry->function((u8 *)child + entry->offset, arg1, arg2, arg3);
    }
}

void sub_80506D0(struct FieldObjectWrapper *object)
{
    struct FieldObjectWrapper *child;
    struct CallbackEntry *entry;

    sub_8047FDC(object);
    child = object->child;
    if (child != 0 && (*((u8 *)child + 0x20C) & 1) != 0) {
        entry = (struct CallbackEntry *)(child->callbacks + 0x20);
        entry->function((u8 *)child + entry->offset);
    }
}

void sub_8050710(struct FieldObjectWrapper *object)
{
    struct FieldObjectWrapper *child;
    struct CallbackEntry *entry;

    sub_8040020(object);
    child = object->child;
    if (child != 0) {
        entry = (struct CallbackEntry *)(child->callbacks + 0x28);
        entry->function((u8 *)child + entry->offset);
    }
}

void sub_8050740(struct FieldObjectWrapper *object, int arg1)
{
    struct FieldObjectWrapper *child;
    struct CallbackEntry *entry;

    sub_8040AE0(object, arg1);
    child = object->child;
    if (child != 0) {
        entry = (struct CallbackEntry *)(child->callbacks + 0x30);
        entry->function((u8 *)child + entry->offset, arg1);
    }
}

void sub_8050774(struct FieldObjectWrapper *object)
{
    struct FieldObjectWrapper *child;
    struct CallbackEntry *entry;

    sub_80409F4(object);
    child = object->child;
    if (child != 0) {
        entry = (struct CallbackEntry *)(child->callbacks + 0x18);
        entry->function((u8 *)child + entry->offset);
    }
}

void sub_80507A4(struct FieldObjectWrapper *object, int arg1, int arg2, int arg3)
{
    struct FieldObjectWrapper *child;
    struct CallbackEntry *entry;

    sub_80403C4(object, arg1, arg2, arg3);
    child = object->child;
    if (child != 0) {
        entry = (struct CallbackEntry *)(child->callbacks + 0x10);
        entry->function((u8 *)child + entry->offset, arg1, arg2, arg3);
    }
}
