#include "common.h"
#include "ui/functions.h"

struct UiBouncingObject {
    u8 gap00[0x70];
    s32 verticalVelocity70;
    u8 gap74[4];
    s32 verticalPosition78;
};

void sub_816D734(struct UiBouncingObject* object)
    __attribute__((section(".text.ui_motion.sub_816D734")));
void sub_816D734(struct UiBouncingObject* object)
{
    object->verticalPosition78 += object->verticalVelocity70;
    if (object->verticalPosition78 <= 0x57FF) {
        object->verticalPosition78 = 0x5800;
        object->verticalVelocity70 = -object->verticalVelocity70 / 2;
    }

    if (object->verticalPosition78 > 0x7800) {
        object->verticalPosition78 = 0x7800;
        object->verticalVelocity70 = -object->verticalVelocity70 / 2;
    }
}
