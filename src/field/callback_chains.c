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
void sub_814DB34(u32 context, struct FieldSceneObject* object);
void sub_814D838(
    u32 context, struct FieldSceneObject* object, void* callbackSlot);
u8 sub_8138C8C(u32 context, struct FieldSceneObject* object);
void sub_81382A8(struct FieldSceneObject* object);
void sub_81385A8(struct FieldSceneObject* object);
void sub_81370C4(struct FieldSceneObject* object, u32 value);
void sub_81378CC(
    struct FieldSceneObject* object, u32 mode, s32 x, s32 y);
void sub_8137FA4(struct FieldSceneObject* object);
void sub_81381D4(struct FieldSceneObject* object);
void sub_8136A84(
    u32 context, struct FieldSceneObject* object, void* callbackSlot);

SEC(sub_81396A8)
void field_scene_run_active_callback_and_refresh(
    u32 context, struct FieldSceneObject* object)
{
    object->callback1A0(context, object, &object->callback1A0);
    if (object->flags2B5 & FIELD_SCENE_FLAGS_2B5_08)
        sub_81385A8(object);
}

SEC(sub_8139708)
void field_scene_begin_positioned_transition_a(
    u32 context, struct FieldSceneObject* object,
    void* callbackSlot)
{
    struct FieldSceneCallbackCursor* cursor = callbackSlot;

    (void)context;
    sub_81370C4(object, 0xFF);
    sub_81378CC(
        object, 1, object->transitionCoordinateX * 0x100,
        object->transitionCoordinateY * 0x100);
    sub_8137FA4(object);
    sub_81381D4(object);
    sub_81385A8(object);
    cursor->current = sub_8136A84;
}

__attribute__((section(".text.field_scene_callbacks.sub_8139364")))
void field_scene_branch_on_condition_or_advance_callback(
    u32 context, struct FieldSceneObject* object,
    struct FieldSceneCallbackCursor* cursor)
{
    s32 clearMask;
    u8 flags;

    if ((u8)sub_8138C8C(context, object) == 1) {
        sub_81382A8(object);
    } else {
        flags = object->callbackStateFlags;
        clearMask = 3;
        clearMask = -clearMask;
        clearMask &= flags;
        clearMask |= 1;
        object->callbackStateFlags = clearMask;
        cursor->current = cursor->next;
    }
}

__attribute__((section(".text.field_scene_callbacks.sub_813915C")))
void field_scene_countdown_linked_selection_then_restore_callback(
    u32 context, struct FieldSceneObject* object,
    FieldSceneChainCallback* callbackSlot)
{
    struct FieldSceneObject* linked = object->linkedSceneObject344;
    u32 remaining = (u16)linked->selectedValue - 1U;
    u8 flags;
    s32 clearMask;

    (void)context;
    linked->selectedValue = remaining;
    if ((remaining << 16) == 0) {
        flags = object->callbackStateFlags;
        flags |= 1;
        clearMask = 3;
        clearMask = -clearMask;
        flags &= clearMask;
        object->callbackStateFlags = flags;
        *callbackSlot = linked->callback1AC;
    }
}
__attribute__((section(".text.field_scene_callbacks.sub_813915C")))
const u16 field_scene_countdown_linked_selection_padding = 0;

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
void sub_8136D00(
    u32, struct FieldSceneObject*, void*);
void sub_81395AC(u32 context, struct FieldSceneObject* object);

SEC(field_promote_dispatch_and_start_callback_chain)
void field_promote_dispatch_and_start_callback_chain(
    u32 context, struct FieldSceneObject* object)
{
    s8* flags;

    sub_8138944(object, 0x0F);
    object->dispatch198 = object->dispatch19C;
    object->callback1A0 = sub_8136D00;
    object->callback1A4 = sub_8136D00;
    flags = (s8*)&object->flags214;
    *flags = (*flags & -8) | 1;
    object->dispatch198(context, object);
}

#define field_prepare_scene_visual sub_814DB34
#define field_update_prepared_scene_visual sub_814D838
#define field_prepare_scene_visual_and_set_callback sub_814DCFC

SEC(sub_814DCFC)
void field_prepare_scene_visual_and_set_callback(
    u32 context, struct FieldSceneObject* object,
    FieldSceneChainCallback* callbackSlot)
{
    field_prepare_scene_visual(context, object);
    *callbackSlot = field_update_prepared_scene_visual;
}

SEC(sub_8139970)
void field_install_and_run_scene_dispatch_81395ac(
    u32 context, struct FieldSceneObject* object)
{
    object->dispatch198 = sub_81395AC;
    object->dispatch198(context, object);
}

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
    field_scene_load_scaled_bounds(object, 0);
    object->dispatch198 = sub_813B380;
    object->callback1A0 = sub_813C758;
    object->callback1A4 = sub_813C758;
    sub_813B380(context, object);
}

#define DEFINE_LINKED_PROFILE_CHAIN(name, dispatch)                    \
    SEC(name) void name(u32 context, struct FieldSceneObject* object)   \
    {                                                                    \
        sub_8138944(object, 0);                                         \
        field_scene_load_scaled_bounds(object, 0);                      \
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
    field_scene_load_scaled_bounds(object, 0);
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
    field_scene_load_scaled_bounds(object, 0);
    sub_8138FD4(object, 0x0B);
    object->dispatch198 = sub_814448C;
    object->callback1A0 = sub_8139420;
    object->callback1A4 = sub_8139420;
    sub_814448C(context, object);
}

SEC(field_forward_linked_callback_and_advance_on_sprite_flag)
void field_forward_linked_callback_and_advance_on_sprite_flag(
    u32 context, struct FieldSceneObject* object)
{
    FieldSceneChainCallback* callback =
        &object->linkedSceneObject344->callback1A0;

    if (*callback != 0)
        (*callback)(context, object, callback);
    if (object->sprite->field_12_3) {
        s8* flags = (s8*)&object->flags214;

        *flags = (*flags & -8) | 3;
        object->dispatch198 = field_initialize_callback_chain_variant_m;
    }
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
