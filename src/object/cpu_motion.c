#include "audio/sound_effects.h"
#include "object/functions.h"
#include "object/runtime_leaf_callbacks.h"
#include "object/runtime_object.h"

#define SEC(symbol) \
    __attribute__((section(".text.misc_helpers_03." #symbol)))

void sub_807F47C(struct RuntimeObject* object);
void sub_8082E1C(
    struct RuntimeObject* object, s32 animation, s32 command, s32 argument);
void sub_8085B38(struct RuntimeObject* object);

SEC(sub_8088C3C)
void object_after_nonpositive_countdown_begin_forward_motion_2800(
    struct RuntimeObject* object)
{
    u32 timer;
    s32 value80 = object->value80;
    if (value80 == 0) {
        timer = *(u16 *)(void *)&object->timer - 1;
        object->timer = timer;
        if ((s32)((u32)timer << 16) <= 0) {
            sound_effect_stop(0x81);
            sub_807F47C(object);
            object->value84 = object->positionX + 0x2800;
            object->value88 = object->positionY;
            object->value8C = object->positionZBase;
            {
                s32 flagValue = object->flags79;
                s32 mask = 0x20;
                flagValue |= mask;
                object->flags79 = flagValue;
            }
            object->unknown7C = 0x400;
            object->unknown7A = value80;
            sub_8085B38(object);
            sub_8082E1C(object, 2, 0, 0);
            {
                s32 mask;
                s32 flagValue;
                volatile u8 *visualFlags;
                visualFlags = &object->visual->flags;
                flagValue = *visualFlags;
                mask = -7;
                flagValue &= mask;
                *visualFlags = flagValue;
            }
            object->update = sub_808750C;
        }
    }
}

SEC(sub_808954C)
void object_after_nonpositive_countdown_begin_forward_motion_3400(
    struct RuntimeObject* object)
{
    u32 timer;
    s32 value80 = object->value80;
    if (value80 == 0) {
        timer = *(u16 *)(void *)&object->timer - 1;
        object->timer = timer;
        if ((s32)((u32)timer << 16) <= 0) {
            sound_effect_stop(0x6C);
            sub_807F47C(object);
            object->value84 = object->positionX + 0x3400;
            object->value88 = object->positionY;
            object->value8C = object->positionZBase;
            {
                s32 flagValue = object->flags79;
                s32 mask = 0x20;
                flagValue |= mask;
                object->flags79 = flagValue;
            }
            object->unknown7C = 0x400;
            object->unknown7A = value80;
            sub_8085B38(object);
            sub_8082E1C(object, 2, 0, 0);
            {
                s32 mask;
                s32 flagValue;
                volatile u8 *visualFlags;
                visualFlags = &object->visual->flags;
                flagValue = *visualFlags;
                mask = -7;
                flagValue &= mask;
                *visualFlags = flagValue;
            }
            object->update = sub_808750C;
        }
    }
}
