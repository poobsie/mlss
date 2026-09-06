#include "global.h"
#include "audio/sound_effects.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.object_unique_callbacks." #name)))

void sub_8082E1C(
    struct RuntimeObject* object, s32 animation, s32 command, s32 argument);
void sub_809E0EC(struct RuntimeObject* object);
void sub_809C59C(struct RuntimeObject* object);
void sub_809B610(struct RuntimeObject* object);

#define object_launch_with_command_40C2 sub_809B558
SEC(sub_809B558)
void object_launch_with_command_40C2(struct RuntimeObject* object)
{
    s8* visualFlags;

    object->currentPositionY += 0x100;
    object->verticalPosition = 0x2600;
    sub_8082E1C(object, 1, 0x40C2, 0);
    visualFlags = (s8*)&object->visual->flags;
    *visualFlags = (*visualFlags & -7) | 2;
    sound_effect_play(0x15D, SOUND_VOLUME_UNCHANGED);
    object->update = sub_809B610;
}

#define object_advance_value75_and_stop sub_809CA9C
SEC(sub_809CA9C)
void object_advance_value75_and_stop(struct RuntimeObject* object)
{
    object->unknown75 += 5;
    sub_809C59C(object);
    sub_8082E1C(object, 0, 0, 0);
    object->update = NULL;
}
SEC(sub_809CA9C)
const u16 object_advance_value75_and_stop_padding = 0;

#define object_count_down_to_callback_809E0EC sub_809E410
SEC(sub_809E410)
void object_count_down_to_callback_809E0EC(struct RuntimeObject* object)
{
    if (object->timer > 0)
        object->timer--;
    else
        object->update = sub_809E0EC;
}
