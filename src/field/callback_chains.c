#include "field/functions.h"
#include "field/scene_object.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(name) __attribute__((section(".text.upper." STRINGIFY(name))))

void sub_80473DC(struct FieldSceneObject* object);
void sub_81387C8(struct FieldSceneObject* object, s32 index);
void sub_8138B84(struct FieldSceneObject* object, s32 index);
void sub_8138944(struct FieldSceneObject* object, s32 index);
void sub_8138FD4(struct FieldSceneObject* object, s32 index);
void sub_8138FF0(struct FieldSceneObject* object, s32 index);
void sub_8139030(struct FieldSceneObject* object, s32 index);
void sub_813B380(u32 context, struct FieldSceneObject* object);
void sub_81398C4(u32 context, struct FieldSceneObject* object);
void sub_81396A8(u32 context, struct FieldSceneObject* object);
void sub_813C5FC(u32 context, struct FieldSceneObject* object);
void sub_813CDB8(u32 context, struct FieldSceneObject* object);
void sub_813D284(u32 context, struct FieldSceneObject* object);
void sub_81435E4(u32 context, struct FieldSceneObject* object);
void sub_814448C(u32 context, struct FieldSceneObject* object);
void sub_815041C(struct FieldSceneObject* object, s32 value);
void sub_814E8B0(
    u32 context, struct FieldSceneObject* object, void* callbackSlots);

void sub_8139508(
    u32, struct FieldSceneObject*, void*);
void sub_813955C(
    u32, struct FieldSceneObject*, void*);
void sub_813967C(
    u32, struct FieldSceneObject*, void*);
void sub_8139708(
    u32, struct FieldSceneObject*, void*);
void sub_81397CC(
    u32, struct FieldSceneObject*, void*);
void sub_8139880(
    u32, struct FieldSceneObject*, void*);
void sub_81368AC(
    u32, struct FieldSceneObject*, void*);
void sub_8139420(
    u32, struct FieldSceneObject*, void*);
void sub_813C758(
    u32, struct FieldSceneObject*, void*);
void sub_813C810(
    u32, struct FieldSceneObject*, void*);

SEC(field_initialize_callback_chain_from_definition)
void field_initialize_callback_chain_from_definition(
    u32 context, struct FieldSceneObject* object)
{
    sub_81387C8(object, 0);
    sub_8138B84(object, 0);
    object->dispatch198 = sub_813B380;
    object->callback1A0 = sub_81397CC;
    object->callback1A4 = sub_81397CC;
    sub_813B380(context, object);
}

SEC(field_forward_linked_callback_with_cleanup)
void field_forward_linked_callback_with_cleanup(
    u32 context, struct FieldSceneObject* object,
    void* callbackSlot)
{
    FieldSceneChainCallback* callbacks = callbackSlot;

    if (object->flags214 & 0x40)
        sub_80473DC(object);
    callbacks[1](context, object, callbacks);
}

#define DEFINE_CALLBACK_CHAIN(name, dispatch, callback)                \
    SEC(name) void name(u32 context, struct FieldSceneObject* object)   \
    {                                                                    \
        object->dispatch198 = dispatch;                                 \
        object->callback1A0 = callback;                                 \
        object->callback1A4 = callback;                                 \
        dispatch(context, object);                                      \
    }

#define DEFINE_CALLBACK_CHAIN_WITH_AUX(name, dispatch, callback, aux)  \
    SEC(name) void name(u32 context, struct FieldSceneObject* object)   \
    {                                                                    \
        object->dispatch198 = dispatch;                                 \
        object->callback1A0 = callback;                                 \
        object->callback1A4 = callback;                                 \
        object->callback1AC = aux;                                      \
        dispatch(context, object);                                      \
    }

DEFINE_CALLBACK_CHAIN_WITH_AUX(
    field_initialize_callback_chain_variant_a,
    sub_813B380, sub_8139508, field_forward_linked_callback_with_cleanup)
DEFINE_CALLBACK_CHAIN(
    field_initialize_callback_chain_variant_b, sub_81398C4, sub_813955C)
DEFINE_CALLBACK_CHAIN_WITH_AUX(
    field_initialize_callback_chain_variant_c,
    sub_81396A8, sub_813967C, sub_813967C)
DEFINE_CALLBACK_CHAIN_WITH_AUX(
    field_initialize_callback_chain_variant_d,
    sub_813B380, sub_8139708, field_forward_linked_callback_with_cleanup)
DEFINE_CALLBACK_CHAIN(
    field_initialize_callback_chain_variant_e, sub_813B380, sub_81368AC)
DEFINE_CALLBACK_CHAIN(
    field_initialize_callback_chain_variant_f, sub_813B380, sub_81397CC)
DEFINE_CALLBACK_CHAIN(
    field_initialize_callback_chain_variant_g, sub_81398C4, sub_8139880)

SEC(field_initialize_callback_chain_variant_h)
void field_initialize_callback_chain_variant_h(
    u32 context, struct FieldSceneObject* object)
{
    sub_81387C8(object, 0x15);
    sub_8138FF0(object, 0x28);
    object->dispatch198 = sub_813C5FC;
    object->callback1A0 = sub_813C810;
    object->callback1A4 = sub_813C810;
    sub_813C5FC(context, object);
}

SEC(field_initialize_callback_chain_variant_i)
void field_initialize_callback_chain_variant_i(
    u32 context, struct FieldSceneObject* object)
{
    sub_81387C8(object, 0);
    sub_8139030(object, 0);
    object->dispatch198 = sub_813B380;
    object->callback1A0 = sub_813C758;
    object->callback1A4 = sub_813C758;
    sub_813B380(context, object);
}

#define DEFINE_LINKED_PROFILE_CHAIN(name, dispatch)                    \
    SEC(name) void name(u32 context, struct FieldSceneObject* object)   \
    {                                                                    \
        sub_8138944(object, 0);                                         \
        sub_8139030(object, 0);                                         \
        sub_8138FD4(object, 0x0B);                                      \
        sub_8138944(object->linkedSceneObject344, 0x0F);                \
        object->dispatch198 = dispatch;                                 \
        object->callback1A0 = sub_8139420;                              \
        object->callback1A4 = sub_8139420;                              \
        dispatch(context, object);                                      \
    }

DEFINE_LINKED_PROFILE_CHAIN(
    field_initialize_callback_chain_variant_j, sub_813D284)
DEFINE_LINKED_PROFILE_CHAIN(
    field_initialize_callback_chain_variant_k, sub_813CDB8)

SEC(field_initialize_callback_chain_variant_l)
void field_initialize_callback_chain_variant_l(
    u32 context, struct FieldSceneObject* object)
{
    sub_81387C8(object, 0);
    sub_8139030(object, 0);
    sub_8138FD4(object, 0x0B);
    object->dispatch198 = sub_81435E4;
    object->callback1A0 = sub_8139420;
    object->callback1A4 = sub_8139420;
    sub_81435E4(context, object);
}

SEC(field_initialize_callback_chain_variant_m)
void field_initialize_callback_chain_variant_m(
    u32 context, struct FieldSceneObject* object)
{
    sub_8138944(object, 0);
    sub_8139030(object, 0);
    sub_8138FD4(object, 0x0B);
    object->dispatch198 = sub_814448C;
    object->callback1A0 = sub_8139420;
    object->callback1A4 = sub_8139420;
    sub_814448C(context, object);
}

SEC(field_prepare_callback_slot_3_and_dispatch)
void field_prepare_callback_slot_3_and_dispatch(
    u32 context, struct FieldSceneObject* object,
    struct FieldCallbackSlots* callbacks)
{
    sub_815041C(object, 0);
    callbacks->slots[3] = sub_814E8B0;
    sub_814E8B0(context, object, callbacks);
}
