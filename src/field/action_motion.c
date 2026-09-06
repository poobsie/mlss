#include "field/action_process.h"

#define SEC(symbol) \
    __attribute__((section(".text.field_action_motion." #symbol)))

void sub_8082E1C(
    struct RuntimeObject* object, s32 animation, s32 command, s32 argument);
void sub_8081F84(struct FieldActionProcess* process);

SEC(sub_8080168)
u8 field_object_step_vertical_arc(struct RuntimeObject* object)
{
    s32 result;
    if (object->positionZBase <= 0) {
        result = 0;
    } else {
        object->verticalVelocity -= 0x5E;
        object->verticalPosition =
            object->positionZBase + object->verticalVelocity;
        if (object->verticalPosition <= 0) {
            object->verticalVelocity = 0;
            object->verticalPosition = 0;
            result = 0;
        } else {
            result = 1;
        }
    }
    return result;
}

SEC(sub_80821C4)
void field_action_count_down_then_reset_visual(
    struct FieldActionProcess* process)
{
    struct RuntimeObject* object = process->object;
    if (process->timer > 0) {
        process->timer--;
    } else {
        sub_8082E1C(object, 0, -1, 0);
        /* Signed access preserves the original compiler's mask sequence. */
        *(s8*)&object->visual->flags &= -7;
        process->update = sub_8081F84;
    }
}

SEC(sub_808225C)
void field_action_count_down_then_continue(struct FieldActionProcess* process)
{
    if (process->timer > 0)
        process->timer--;
    else
        process->update = sub_8081F84;
}
