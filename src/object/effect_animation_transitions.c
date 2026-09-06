#include "object/functions.h"
#include "object/runtime_object.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(symbol) \
    __attribute__((section(".text.effect_animation_transitions." STRINGIFY(symbol))))

void sub_80DF024(s32 effect, s32 x, s32 y, s32 z,
                 struct RuntimeObject* object);
s32 sub_810DD7C(struct RuntimeObject* object, void* owner, s32 command);

SEC(object_emit_effect_2adb_then_notify_owner)
s32 object_emit_effect_2adb_then_notify_owner(
    struct RuntimeObject* object, void* owner, s32 command)
{
    sub_80DF024(0x2ADB, object->currentPositionX / 0x100,
                object->currentPositionY / 0x100,
                object->verticalPosition / 0x100, owner);
    return sub_810DD7C(object, owner, command);
}
