#include "field/actor.h"
#include "field/global_object_transitions.h"
#include "object/functions.h"
#include "object/runtime_object.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(symbol) \
    __attribute__((section(".text.misc_helpers_03." STRINGIFY(symbol))))

#define FIELD_RUNTIME (*(struct FieldObjectRuntime**)0x03000FD8)
#define FIELD_ACTOR_RUNTIME (*(struct FieldRuntime**)0x03000FD8)

struct FieldObjectPairRuntime {
    u8 unknown00[0x60];
    struct RuntimeObject* firstObject;
    struct RuntimeObject* secondObject;
};

void sub_80789B4(struct RuntimeObject* object);
void sub_807C298(struct RuntimeObject* object);
void sub_8082E1C(
    struct RuntimeObject* object, s32 animation, s32 command, s32 argument);
void sub_80873B8(struct RuntimeObject* object, s32 kind, s32 duration);
u8 sub_8087CE4(struct RuntimeObject* object);
void sub_8087DE4(void* action);
void sub_80894B8(struct RuntimeObject* object);
void sub_80D69D8(struct RuntimeObject* object);
void sub_810DD7C(struct RuntimeObject* object, void* owner, s32 value);
void sub_81140C0(struct RuntimeObject* object);
void sub_811458C(struct RuntimeObject* object);

SEC(object_on_nested_visual_complete_decrement_repeat_count)
void object_on_nested_visual_complete_decrement_repeat_count(
    struct RuntimeObject* object)
{
    RuntimeObjectCallback next;
    s32 remaining;

    if (object->linkedObject->linkedObject->visual->flags & 8) {
        remaining = object->valueA0 - 1;
        object->valueA0 = remaining;
        next = sub_81140C0;
        if (remaining != 0)
            next = sub_811458C;
        object->update = next;
    }
}

SEC(object_when_value80_clear_arm_followup_kind_3)
void object_when_value80_clear_arm_followup_kind_3(
    struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        object->timer = 0x1E;
        sub_80873B8(object, 3, 0);
        object->followup = sub_80894B8;
    }
}

SEC(object_when_nested_poll_clear_reset_state_and_callbacks)
void object_when_nested_poll_clear_reset_state_and_callbacks(
    struct RuntimeObject* object)
{
    u8 result;

    result = sub_8087CE4(object->linkedObject->linkedObject);
    if (result == 0) {
        object->state->value113 = result;
        object->followup = (RuntimeObjectCallback)0x081141F5;
        object->update = (RuntimeObjectCallback)0x081141F5;
    }
}

SEC(object_increment_visual_value0c_until_value80_clear)
void object_increment_visual_value0c_until_value80_clear(
    struct RuntimeObject* object)
{
    object->visual->value0C += 0x1000;
    if (object->value80 == 0) {
        object->state->valueB4 = 1;
        sub_807C298(object);
    }
}
SEC(object_increment_visual_value0c_until_value80_clear)
const u16 object_increment_visual_value0c_until_value80_clear_padding = 0;

SEC(object_on_visual_complete_animation_1_set_behavior_4)
void object_on_visual_complete_animation_1_set_behavior_4(
    struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 1, 0, 0);
        object->behaviorState = 4;
        object->update = sub_80789B4;
    }
}

SEC(object_on_visual_complete_clear_field_object_pair)
void object_on_visual_complete_clear_field_object_pair(
    struct RuntimeObject* object)
{
    struct FieldObjectPairRuntime* runtime;

    if (object->visual->flags & 8) {
        runtime = (struct FieldObjectPairRuntime*)FIELD_RUNTIME;
        runtime->firstObject->auxiliaryState = 0;
        runtime->secondObject->auxiliaryState = 0;
        sub_8082E1C(object, -1, -1, 0);
        object->update = 0;
    }
}

SEC(object_sync_second_field_actor_object_then_continue)
void object_sync_second_field_actor_object_then_continue(
    struct RuntimeObject* object)
{
    struct FieldActor* actor;
    struct RuntimeObject* action;
    struct RuntimeObject* activeObject;

    actor = FIELD_ACTOR_RUNTIME->actorB;
    action = (struct RuntimeObject*)&actor->action;
    sub_8087DE4(action);
    activeObject = action->linkedObject;
    activeObject->currentPositionX = action->currentPositionX;
    activeObject->currentPositionY = action->currentPositionY;
    activeObject->verticalPosition = action->verticalPosition;
    if (actor->flags81 & 0x20)
        object->update = sub_80D69D8;
}

SEC(object_disable_and_attach_to_first_field_object)
void object_disable_and_attach_to_first_field_object(
    struct RuntimeObject* object)
{
    sub_8082E1C(object, -1, -1, 0);
    object->update = 0;
    sub_810DD7C(&FIELD_RUNTIME->firstObjectOwner->object, object, 0xFF);
}
