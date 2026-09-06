#include "object/functions.h"
#include "object/runtime_object.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(symbol) \
    __attribute__((section(".text.effect_animation_transitions." STRINGIFY(symbol))))

void sub_80DF024(s32 effect, s32 x, s32 y, s32 z,
                 struct RuntimeObject* object);
s32 sub_810DD7C(struct RuntimeObject* object, void* owner, s32 command);
s32 sub_8086D80(struct RuntimeObject* object,
                struct RuntimeObject* comparedObject);
void sub_807F47C(struct RuntimeObject* object);
void sub_807C298(struct RuntimeObject* object);
void sub_809F194(struct RuntimeObject* object);

SEC(object_when_pair_query_clear_emit_effect_2661_and_continue)
s32 object_when_pair_query_clear_emit_effect_2661_and_continue(
    struct RuntimeObject* object, struct RuntimeObject* comparedObject)
{
    s32 result;

    result = sub_8086D80(object, comparedObject);
    if (result == 0) {
        sub_80DF024(0x2661, object->currentPositionX / 0x100,
                    object->currentPositionY / 0x100,
                    object->verticalPosition / 0x100, object);
        sub_807F47C(object);
        object->positionOwner = (u8*)object->state + 8;
        object->update = sub_809F194;
    }
    return result;
}

SEC(object_notify_owner_emit_effect_2651_and_destroy)
s32 object_notify_owner_emit_effect_2651_and_destroy(
    struct RuntimeObject* object, void* owner, s32 command)
{
    s32 result;

    result = sub_810DD7C(object, owner, command);
    sub_80DF024(0x2651, object->currentPositionX / 0x100,
                object->currentPositionY / 0x100,
                object->verticalPosition / 0x100, object);
    sub_807C298(object);
    return result;
}

SEC(object_emit_effect_2adb_then_notify_owner)
s32 object_emit_effect_2adb_then_notify_owner(
    struct RuntimeObject* object, void* owner, s32 command)
{
    sub_80DF024(0x2ADB, object->currentPositionX / 0x100,
                object->currentPositionY / 0x100,
                object->verticalPosition / 0x100, owner);
    return sub_810DD7C(object, owner, command);
}
