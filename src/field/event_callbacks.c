#include "field/event_callbacks.h"

#define SEC(name) __attribute__((section(".text.text_upper_structural." #name)))

extern u32 sub_813B5B4(struct FieldEventContext* context);
extern u32 sub_813B650(struct FieldEventContext* context);
extern void sub_813E974(void);
extern void sub_814706C(void);
extern void sub_8139AA0(struct FieldEventContext* context);

#define DEFINE_SELECTED_EVENT_SETUP(name, table_offset, next)            \
SEC(name) void name(                                                     \
    void* unused, struct FieldEventContext* context,                     \
    FieldEventCallback* callbacks)                                       \
{                                                                        \
    u8* table = context->selectionTable;                                 \
    if ((u8)sub_813B650(context) == 0) {                                 \
        context->selectedValue =                                         \
            table[context->selectionIndex + table_offset];               \
        callbacks[0] = (FieldEventCallback)0x0813B1E9;                   \
        callbacks[3] = (FieldEventCallback)0x0813B361;                   \
        callbacks[1] = (FieldEventCallback)(next);                       \
    }                                                                    \
}

DEFINE_SELECTED_EVENT_SETUP(sub_814260C, 0x58, 0x08141D55)
DEFINE_SELECTED_EVENT_SETUP(sub_8142760, 0x4E, 0x08141509)
DEFINE_SELECTED_EVENT_SETUP(sub_8142BCC, 0x6C, 0x0813E619)

#define DEFINE_ENABLE_EVENT_CALLBACKS(name, next)                        \
SEC(name) void name(void* unused, struct FieldEventContext* context)     \
{                                                                        \
    ((u8*)context)[0x33E] |= 0x10;                                      \
    sub_8139AA0(context);                                                \
    *(FieldEventCallback*)((u8*)context + 0x198) =                       \
        (FieldEventCallback)0x0813B381;                                  \
    *(FieldEventCallback*)((u8*)context + 0x1A0) =                       \
        (FieldEventCallback)(next);                                      \
}

DEFINE_ENABLE_EVENT_CALLBACKS(sub_81427E0, 0x08141509)
DEFINE_ENABLE_EVENT_CALLBACKS(sub_8147010, 0x08146FAD)

#define DEFINE_ENABLE_RESET_EVENT_CALLBACKS(name, next)                  \
SEC(name) void name(void* unused, struct FieldEventContext* context)     \
{                                                                        \
    ((u8*)context)[0x33E] |= 0x10;                                      \
    sub_8139AA0(context);                                                \
    *(u16*)((u8*)context + 0x1D4) = 0;                                  \
    *(FieldEventCallback*)((u8*)context + 0x198) =                       \
        (FieldEventCallback)0x0813B381;                                  \
    *(FieldEventCallback*)((u8*)context + 0x1A0) =                       \
        (FieldEventCallback)(next);                                      \
}

DEFINE_ENABLE_RESET_EVENT_CALLBACKS(sub_8142B04, 0x0813FDF5)
DEFINE_ENABLE_RESET_EVENT_CALLBACKS(sub_8145920, 0x08144CD5)
DEFINE_ENABLE_RESET_EVENT_CALLBACKS(sub_814BCC0, 0x08148E99)

SEC(sub_8142CF0)
void sub_8142CF0(
    void* unused, struct FieldEventContext* context,
    FieldEventCallback* output)
{
    if ((u8)sub_813B5B4(context) == 0)
        *output = sub_813E974;
}

SEC(sub_814704C)
void sub_814704C(
    void* unused, struct FieldEventContext* context,
    FieldEventCallback* output)
{
    if ((u8)sub_813B650(context) == 0)
        *output = sub_814706C;
}

void field_prepare_selected_event_variant_a(
    void*, struct FieldEventContext*, FieldEventCallback*)
    __attribute__((alias("sub_814260C")));
void field_prepare_selected_event_variant_b(
    void*, struct FieldEventContext*, FieldEventCallback*)
    __attribute__((alias("sub_8142760")));
void field_prepare_selected_event_variant_c(
    void*, struct FieldEventContext*, FieldEventCallback*)
    __attribute__((alias("sub_8142BCC")));
void field_enable_event_callbacks_variant_a(void*, struct FieldEventContext*)
    __attribute__((alias("sub_81427E0")));
void field_enable_event_callbacks_variant_b(void*, struct FieldEventContext*)
    __attribute__((alias("sub_8147010")));
void field_enable_and_reset_event_callbacks_variant_a(
    void*, struct FieldEventContext*) __attribute__((alias("sub_8142B04")));
void field_enable_and_reset_event_callbacks_variant_b(
    void*, struct FieldEventContext*) __attribute__((alias("sub_8145920")));
void field_enable_and_reset_event_callbacks_variant_c(
    void*, struct FieldEventContext*) __attribute__((alias("sub_814BCC0")));
void field_replace_callback_when_primary_gate_clears(
    void*, struct FieldEventContext*, FieldEventCallback*)
    __attribute__((alias("sub_8142CF0")));
void field_replace_callback_when_secondary_gate_clears(
    void*, struct FieldEventContext*, FieldEventCallback*)
    __attribute__((alias("sub_814704C")));
