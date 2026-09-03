#include "global.h"
#include "field/scene_object.h"

#define SEC(name) __attribute__((section(".text.field_movement." #name)))

u8 sub_8041FFC(struct FieldSceneObject* object);

SEC(sub_804FBDC) u8 sub_804FBDC(struct FieldSceneObject* object)
{
    u8 result = 0;

    if (((*(u16*)&object->flags20C & 0x801) == 0x801)
        && !(object->flags35A & 2)) {
        object->movementStartX = object->positionX;
        object->movementStartY = object->positionY;
        result = sub_8041FFC(object);
    }
    return result;
}
