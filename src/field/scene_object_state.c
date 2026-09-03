#include "field/functions.h"
#include "field/scene_object.h"

void sub_8021ED8(void* sprite);

void field_clear_state_if_value_present(struct FieldSceneObject* object)
{
    s32 mask = ~0x1FE;

    if (object->value340 != 0) {
        object->state23B = 0;
        object->flags33E &= mask;
    }
}

void field_mark_sprite_and_set_state_7(struct FieldSceneObject* object)
{
    ((u8*)object)[0x20F] |= 2;
    sub_8021ED8(object->sprite);
    object->state23D = 7;
}
