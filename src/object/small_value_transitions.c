#include "audio/sound_effects.h"
#include "object/small_value_transitions.h"

void sub_806E98C(struct RuntimeObject* object);
void sub_806F90C(struct RuntimeObject* object);
void sub_806FCF0(struct RuntimeObject* object);
void sub_807F4FC(struct RuntimeObject* object);
void sub_8082E1C(struct RuntimeObject* object, s32 animation, s32 command, s32 argument);
void sub_80873B8(struct RuntimeObject* object, s32 value, s32 argument);
void sub_808C868(struct RuntimeObject* object);

#define SEC(symbol) __attribute__((section(".text.small_functions_01." #symbol)))

SEC(sub_806E794)
void object_when_value80_clear_start_paired_animation_5(struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        sound_effect_stop(0x6C);
        sub_8082E1C(object, 5, 0, 0);
        sub_8082E1C(object->linkedObject, 5, 0, 0);
        object->update = sub_806E98C;
    }
}

SEC(sub_8070F98)
void object_when_value80_clear_start_animation_16_delay_4(struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        sound_effect_stop(0x11C);
        sub_8082E1C(object, 0x16, 0, 0);
        object->timer = 4;
        object->update = sub_806F90C;
    }
}

SEC(sub_807116C)
void object_when_value80_clear_start_animation_25(struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        sound_effect_stop(0x11C);
        object->value8C = 0x14;
        sub_8082E1C(object, 0x25, 0, 0);
        object->update = sub_806FCF0;
    }
}

SEC(sub_808C6EC)
void object_when_value80_clear_prepare_followup_after_18(struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        sound_effect_stop(0x81);
        sub_807F4FC(object);
        object->timer = 0x18;
        sub_80873B8(object, 3, 0);
        object->followup = sub_808C868;
    }
}
