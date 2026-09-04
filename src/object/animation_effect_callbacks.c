#include "global.h"
#include "object/animation_effect_callbacks.h"

#define SEC(name) \
    __attribute__((section(".text.animation_effect_callbacks." #name)))

void sub_8082E1C(
    struct RuntimeObject* object, s32 animation, s32 command, s32 argument);
void sub_80997E4(struct RuntimeObject* object);
void sub_8099448(struct RuntimeObject* object);

SEC(sub_8099FFC)
void sub_8099FFC(struct RuntimeObject* object)
{
    sub_8082E1C(object, 2, 0, 0);
    object->timer = 0;
    object->value84 = object->positionX;
    /* unknown88 is the saved Y companion to value84 in this callback. */
    *(s32*)object->unknown88 = object->positionY;
    object->update = sub_80997E4;
}

SEC(sub_809A06C)
void sub_809A06C(struct RuntimeObject* object)
{
    sub_8082E1C(object, 2, 0, 0);
    object->timer = 0;
    object->value84 = object->positionX;
    /* unknown88 is the saved Y companion to value84 in this callback. */
    *(s32*)object->unknown88 = object->positionY;
    object->update = sub_8099448;
}
