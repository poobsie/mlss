#include "field/definition_callbacks.h"

#define SEC(name) __attribute__((section(".text.field_definition_callbacks." #name)))

void sub_8139AA0(struct FieldDefinitionCallbacks* object);
void sub_80514C4(
    void* context, struct FieldDefinitionCallbacks* object,
    void* slot);

SEC(sub_8051614)
void sub_8051614(void* context, struct FieldDefinitionCallbacks* object)
{
    object->callback(context, object, &object->callback);
}
SEC(sub_8051614) const u16 sub_8051614_padding = 0;

SEC(sub_80515DC)
void sub_80515DC(void* unused, struct FieldDefinitionCallbacks* object)
{
    sub_8139AA0(object);
    object->update = sub_8051614;
    object->callback = sub_80514C4;
}

SEC(sub_8051608)
void sub_8051608(void* unused, struct FieldDefinitionCallbacks* object)
{
    sub_80515DC(unused, object);
}
SEC(sub_8051608) const u16 sub_8051608_padding = 0;

void field_initialize_definition_callbacks(
    void* unused, struct FieldDefinitionCallbacks* object)
    __attribute__((alias("sub_80515DC")));
void field_initialize_definition_callbacks_forwarder(
    void* unused, struct FieldDefinitionCallbacks* object)
    __attribute__((alias("sub_8051608")));
void field_forward_definition_callback(
    void* context, struct FieldDefinitionCallbacks* object)
    __attribute__((alias("sub_8051614")));
