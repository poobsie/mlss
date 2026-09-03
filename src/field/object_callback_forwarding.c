#include "global.h"
#include "field/functions.h"
#include "field/object_wrapper.h"

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

void field_object_forward_slot70(struct FieldObjectWrapper *object, int arg1, u8 arg2)
{
    struct FieldObjectWrapper *child;
    struct FieldObjectCallbackEntry *entry;

    sub_8047C68(object, arg1, arg2);
    child = object->child;
    if (child != 0) {
        entry = &child->callbacks->slot70;
        entry->function((u8 *)child + entry->receiverOffset, arg1, arg2);
    }
}

int field_object_query_slot68(struct FieldObjectWrapper *object)
{
    struct FieldObjectWrapper *child;
    struct FieldObjectCallbackEntry *entry;
    int result;

    result = sub_8041FFC(object);
    child = object->child;
    if (child != 0) {
        entry = &child->callbacks->slot68;
        result = entry->function((u8 *)child + entry->receiverOffset);
    }
    return result;
}

void field_object_forward_slot60(struct FieldObjectWrapper *object, int arg1, int arg2, u8 arg3)
{
    struct FieldObjectWrapper *child;
    struct FieldObjectCallbackEntry *entry;

    sub_8041A2C(object, arg1, arg2, arg3);
    child = object->child;
    if (child != 0) {
        entry = &child->callbacks->slot60;
        entry->function((u8 *)child + entry->receiverOffset, arg1, arg2, arg3);
    }
}

void field_object_forward_slot58(struct FieldObjectWrapper *object)
{
    struct FieldObjectWrapper *child;
    struct FieldObjectCallbackEntry *entry;

    sub_8047CE8(object);
    child = object->child;
    if (child != 0) {
        entry = &child->callbacks->slot58;
        entry->function((u8 *)child + entry->receiverOffset);
    }
}

int field_object_query_slot50(struct FieldObjectWrapper *object, int arg1, int arg2)
{
    struct FieldObjectWrapper *child;
    struct FieldObjectCallbackEntry *entry;
    int result;

    result = sub_8041368(object, arg1, arg2);
    child = object->child;
    if (child != 0) {
        entry = &child->callbacks->slot50;
        result = entry->function((u8 *)child + entry->receiverOffset, arg1, arg2);
    }
    return result;
}

void field_object_forward_slot88(struct FieldObjectWrapper *object)
{
    struct FieldObjectWrapper *child;
    struct FieldObjectCallbackEntry *entry;

    sub_80459C0(object);
    child = object->child;
    if (child != 0) {
        entry = &child->callbacks->slot88;
        entry->function((u8 *)child + entry->receiverOffset);
    }
}

void field_object_forward_slot48(struct FieldObjectWrapper *object)
{
    struct FieldObjectWrapper *child;
    struct FieldObjectCallbackEntry *entry;

    sub_8040FA0(object);
    child = object->child;
    if (child != 0) {
        entry = &child->callbacks->slot48;
        entry->function((u8 *)child + entry->receiverOffset);
    }
}

void field_object_forward_slot40(struct FieldObjectWrapper *object, s16 arg1, s16 arg2, int arg3)
{
    struct FieldObjectWrapper *child;
    struct FieldObjectCallbackEntry *entry;

    sub_8040CF4(object, arg1, arg2, arg3);
    child = object->child;
    if (child != 0) {
        entry = &child->callbacks->slot40;
        entry->function((u8 *)child + entry->receiverOffset, arg1, arg2, arg3);
    }
}

void field_object_forward_enabled_slot20(struct FieldObjectWrapper *object)
{
    struct FieldObjectWrapper *child;
    struct FieldObjectCallbackEntry *entry;

    sub_8047FDC(object);
    child = object->child;
    if (child != 0 && (child->flags20C & 1) != 0) {
        entry = &child->callbacks->slot20;
        entry->function((u8 *)child + entry->receiverOffset);
    }
}

void field_object_forward_slot28(struct FieldObjectWrapper *object)
{
    struct FieldObjectWrapper *child;
    struct FieldObjectCallbackEntry *entry;

    sub_8040020(object);
    child = object->child;
    if (child != 0) {
        entry = &child->callbacks->slot28;
        entry->function((u8 *)child + entry->receiverOffset);
    }
}

void field_object_forward_slot30(struct FieldObjectWrapper *object, int arg1)
{
    struct FieldObjectWrapper *child;
    struct FieldObjectCallbackEntry *entry;

    sub_8040AE0(object, arg1);
    child = object->child;
    if (child != 0) {
        entry = &child->callbacks->slot30;
        entry->function((u8 *)child + entry->receiverOffset, arg1);
    }
}

void field_object_forward_slot18(struct FieldObjectWrapper *object)
{
    struct FieldObjectWrapper *child;
    struct FieldObjectCallbackEntry *entry;

    sub_80409F4(object);
    child = object->child;
    if (child != 0) {
        entry = &child->callbacks->slot18;
        entry->function((u8 *)child + entry->receiverOffset);
    }
}

void field_object_forward_slot10(struct FieldObjectWrapper *object, int arg1, int arg2, int arg3)
{
    struct FieldObjectWrapper *child;
    struct FieldObjectCallbackEntry *entry;

    sub_80403C4(object, arg1, arg2, arg3);
    child = object->child;
    if (child != 0) {
        entry = &child->callbacks->slot10;
        entry->function((u8 *)child + entry->receiverOffset, arg1, arg2, arg3);
    }
}
