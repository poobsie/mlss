#include "object/small_visual_transitions.h"

void sub_8060E90(struct RuntimeObject* object);
void sub_8067A84(struct RuntimeObject* object);
void sub_8082E1C(struct RuntimeObject* object, s32 animation, s32 command, s32 argument);
void sub_808750C(struct RuntimeObject* object);
void sub_80883A0(struct RuntimeObject* object, s32 duration);
void sub_80DA098(struct RuntimeObject* object);
void sub_810FF78(struct RuntimeObject* object);
void sub_8110078(struct RuntimeObject* object);

#define SEC(symbol) __attribute__((section(".text.small_functions_01." #symbol)))

SEC(sub_80613FC)
void object_on_visual_complete_animation_0_then_idle(struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 0, 0, 0);
        object->update = sub_808750C;
    }
}

SEC(sub_8061480)
void object_on_visual_complete_animation_3_parameter_10(struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 3, 0, 0);
        object->visual->parameter20 = 0x10;
        object->update = sub_8060E90;
    }
}

SEC(sub_806829C)
void object_on_visual_complete_animation_3_then_continue(struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 3, 0, 0);
        object->update = sub_8067A84;
    }
}

SEC(sub_80DA0E0)
void object_when_visual_value21_clears_reset_timer(struct RuntimeObject* object)
{
    u8 value = object->visual->value21;

    if (value == 0) {
        object->timer = value;
        object->update = sub_80DA098;
    }
}

SEC(sub_810FE94)
void object_on_visual_complete_animation_0e_delay_1e_a(struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 0x0E, 0, 0);
        sub_80883A0(object, 0x1E);
        object->update = sub_810FF78;
    }
}

SEC(sub_810FF18)
void object_on_visual_complete_animation_0e_delay_1e_b(struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 0x0E, 0, 0);
        sub_80883A0(object, 0x1E);
        object->update = sub_8110078;
    }
}
