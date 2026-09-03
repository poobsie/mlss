#include "field/value_transfer.h"
#include "field/actor.h"
#include "field/effect_entry_sequence.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.field_value_transfer." #name)))
#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define MISC_SEC(name) \
    __attribute__((section(".text.misc_helpers_01." STRINGIFY(name))))
#define FIELD_RUNTIME (*(struct FieldEffectRuntime**)0x03000FD8)

void sub_807C298(struct RuntimeObject* object);
void sub_81165CC(struct FieldValueTransfer* state, s32 mode);

SEC(sub_8116610) void sub_8116610(struct FieldValueTransfer* state)
{
    s32 value = state->value34;
    u16* destination = &state->value44;
    s32 zero = 0;

    *destination = value;
    state->value34 = zero;
}
SEC(sub_8116610) const u16 sub_8116610_padding = 0;

void field_move_value_34_to_44(struct FieldValueTransfer* state)
    __attribute__((alias("sub_8116610")));

MISC_SEC(field_commit_runtime_value_transfer)
void field_commit_runtime_value_transfer(void)
{
    field_move_value_34_to_44(FIELD_RUNTIME->valueTransfer);
}

MISC_SEC(field_prepare_runtime_value_transfer)
void field_prepare_runtime_value_transfer(s32 mode)
{
    sub_81165CC(FIELD_RUNTIME->valueTransfer, mode);
}

MISC_SEC(field_trigger_primary_actor_object)
void field_trigger_primary_actor_object(void)
{
    struct FieldRuntime* runtime = (struct FieldRuntime*)FIELD_RUNTIME;
    sub_807C298(runtime->actorA->action.activeObject);
}
