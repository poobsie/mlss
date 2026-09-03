#include "audio/sound_effects.h"
#include "object/small_setup_transitions.h"

s32 sub_8082B00(void);
void sub_8082E1C(struct RuntimeObject* object, s32 animation, s32 command, s32 argument);
void sub_805F638(struct RuntimeObject* object);
void sub_8061B8C(struct RuntimeObject* object);
void sub_8068F3C(struct RuntimeObject* object);
void sub_80694B4(struct RuntimeObject* object);
void sub_808750C(struct RuntimeObject* object);
void sub_80DB860(struct RuntimeObject* object);

#define SEC(symbol) __attribute__((section(".text.small_functions_01." #symbol)))

SEC(sub_805F604)
void object_when_ready_start_animation_2_sound_118(struct RuntimeObject* object)
{
    if (sub_8082B00() == 0) {
        sub_8082E1C(object, 2, 0, 0);
        sound_effect_play(0x118, SOUND_VOLUME_UNCHANGED);
        object->update = sub_805F638;
    }
}

SEC(sub_8062150)
void object_use_link_or_when_ready_start_animation_0a(struct RuntimeObject* object)
{
    RuntimeObjectCallback next;

    if (object->linkedObject != 0) {
        next = sub_808750C;
        goto install_next;
    }
    if (sub_8082B00() == 0) {
        sub_8082E1C(object, 0x0A, 0, 0);
        next = sub_8061B8C;
install_next:
        object->update = next;
    }
}

SEC(sub_806947C)
void object_when_ready_start_animation_2_values_a4_a8(struct RuntimeObject* object)
{
    if (sub_8082B00() == 0) {
        sub_8082E1C(object, 2, 0, 0);
        object->valueA4 = 0x300;
        object->valueA8 = 0x66;
        object->update = sub_8068F3C;
    }
}

SEC(sub_806A3C0)
void object_when_ready_start_animation_2_values_8c_a8(struct RuntimeObject* object)
{
    if (sub_8082B00() == 0) {
        sub_8082E1C(object, 2, 0, 0);
        object->value8C = 0x300;
        object->valueA8 = 0x66;
        object->update = sub_80694B4;
    }
}

SEC(sub_80DBDE8)
void object_start_animation_2_sound_11a_delay_30(struct RuntimeObject* object)
{
    sub_8082E1C(object, 2, 0, 0);
    sound_effect_play(0x11A, SOUND_VOLUME_UNCHANGED);
    object->timer = 0x30;
    object->update = sub_80DB860;
}
