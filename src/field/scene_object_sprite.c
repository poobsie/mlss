#include "field/functions.h"
#include "field/scene_object.h"

void sub_80403C4(struct FieldSceneObject* object);

void field_reset_sprite_modes(struct FieldSceneObject* object)
{
    sub_80403C4(object);
    object->sprite->field_1F_0 = object->sprite->field_1F_2 = 0;
}

void sub_80514AC(void) {}
void nullsub_20(void) {}
void sub_80514B4(void) {}
void nullsub_19(void) {}
void sub_80514BC(void) {}
void nullsub_18(void) {}
