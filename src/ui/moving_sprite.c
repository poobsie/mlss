#include "audio/sound_effects.h"
#include "ui/moving_sprite.h"

s32 ui_moving_sprite_check_proximity(
    struct UiMovingSpriteObject* object,
    struct UiMovingSpriteObject* other)
    __attribute__((section(".text.ui_moving_sprite.sub_816B230")));
s32 ui_moving_sprite_check_proximity(
    struct UiMovingSpriteObject* object,
    struct UiMovingSpriteObject* other)
{
    u16 enabledFlag = 1;

    if (!(other->valueAndFlags6C.halfwords.flags & enabledFlag)) {
        s32 deltaX = object->positionX - other->positionX;
        s32 deltaY = object->positionY - other->positionY;
        s32 distanceSquared =
            (deltaX * deltaX + deltaY * deltaY) >> 8;

        if (distanceSquared <= 0x8FFF) {
            sound_effect_play(0x37, SOUND_VOLUME_UNCHANGED);
            other->valueAndFlags6C.halfwords.flags |= enabledFlag;
            object->valueAndFlags6C.value = 6;
            return 1;
        }
    }
    return 0;
}
