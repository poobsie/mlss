#include "audio/sound_effects.h"
#include "object/small_state_helpers.h"

s32 sub_8087CE4();
void sub_8082E1C(struct RuntimeObject* object, s32 animation, s32 command, s32 argument);
void sub_808750C(struct RuntimeObject* object);
void sub_81147B4(struct RuntimeObject* object);

#define SEC(symbol) __attribute__((section(".text.small_functions_01." #symbol)))

SEC(sub_8065ED4)
void object_when_link_chain_empty_start_animation_0c(struct RuntimeObject* object)
{
    u8 linkCount;
    struct RuntimeObject* linked;

    linkCount = 0;
    linked = object->linkedObject;
    if (linked != 0) {
        do {
            linkCount += 1;
            linked = linked->linkedObject;
        } while (linked != 0);
    }
    if (linkCount == 0) {
        sub_8082E1C(object, 0x0C, 0, 0);
        object->update = sub_808750C;
    }
}

SEC(sub_8067A4C)
void object_move_right_and_fall_to_ground(struct RuntimeObject* object)
{
    object->currentPositionX += 0x200;
    object->verticalPosition -= object->value8C;
    object->value8C += 0x66;
    if (object->verticalPosition <= 0) {
        object->verticalPosition = 0;
        object->update = sub_808750C;
    }
}

SEC(sub_80886BC)
void object_restore_saved_update_on_flag_20(struct RuntimeObject* object)
{
    sub_8087CE4();
    if (object->flags79 & 0x20) {
        object->update = object->followup;
        object->followup = 0;
    }
}

SEC(sub_811488C)
void object_when_nested_link_ready_continue(struct RuntimeObject* object)
{
    if ((sub_8087CE4(object->linkedObject->linkedObject) << 0x18) == 0) {
        sound_effect_stop(0xD5);
        object->update = sub_81147B4;
        sub_81147B4(object);
    }
}
