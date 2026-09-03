#include "audio/sound_effects.h"
#include "object/repeating_command.h"

void sub_80790CC(struct RuntimeObject* object);
void sub_8079018(struct RuntimeObject* object);
void sub_8082E1C(struct RuntimeObject* object, s32 animation, s32 command, s32 argument);

#define SEC(group, symbol) __attribute__((section(".text." group "." #symbol)))

enum {
    REPEATING_COMMAND_ID = 0x4029,
    REPEATING_COMMAND_ANIMATION = 0x0D,
    REPEATING_COMMAND_DELAY = 6,
    REPEATING_COMMAND_CYCLES = 6,
    REPEATING_COMMAND_SOUND = 0x86,
};

SEC("misc_helpers_03", sub_8079C70)
void object_begin_repeating_command_4029(struct RuntimeObject* object)
{
    sub_8082E1C(object, REPEATING_COMMAND_ANIMATION, REPEATING_COMMAND_ID, 0);
    object->update = object_repeat_command_4029_until_visual_complete;
    object->valueA4 = 0;
    object->valueA8 = 0;
}

SEC("small_functions_12", sub_8079C9C)
void object_repeat_command_4029_until_visual_complete(struct RuntimeObject* object)
{
    s32 timer = object->valueA4 - 1;
    object->valueA4 = timer;
    if (timer <= 0) {
        s32 cycleCount;

        sub_80790CC(object);
        sound_effect_play(REPEATING_COMMAND_SOUND, SOUND_VOLUME_UNCHANGED);
        object->valueA4 = REPEATING_COMMAND_DELAY;
        cycleCount = object->valueA8 + 1;
        object->valueA8 = cycleCount;
        if (cycleCount >= REPEATING_COMMAND_CYCLES
            && (object->visual->flags & 8)) {
            if (*(s32*)0x03000F6C == 0)
                sub_8082E1C(object, 6, REPEATING_COMMAND_ID, 0);
            else
                sub_8082E1C(object, 0x0A, REPEATING_COMMAND_ID, 0);
            object->update = sub_8079018;
        }
    }
}
