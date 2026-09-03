#ifndef GUARD_FIELD_DEFINITION_CALLBACKS_H
#define GUARD_FIELD_DEFINITION_CALLBACKS_H

#include "global.h"

struct FieldDefinitionCallbacks;
typedef void (*FieldDefinitionCallback)(
    void* context, struct FieldDefinitionCallbacks* object,
    void* slot);

struct FieldDefinitionCallbacks {
    u8 unknown000[0x198];
    void (*update)(void* context, struct FieldDefinitionCallbacks* object);
    u8 unknown19C[4];
    FieldDefinitionCallback callback;
};

void field_initialize_definition_callbacks(
    void* unused, struct FieldDefinitionCallbacks* object);
void field_initialize_definition_callbacks_forwarder(
    void* unused, struct FieldDefinitionCallbacks* object);
void field_forward_definition_callback(
    void* context, struct FieldDefinitionCallbacks* object);

#endif
