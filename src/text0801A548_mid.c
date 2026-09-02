#include "global.h"
#include "common.h"

struct FieldObjectTail {
    u8 pad00[0x294];
    struct Sprite *sprite;
};

void sub_80403C4(struct FieldObjectTail *);

void sub_8051484(struct FieldObjectTail *object)
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
