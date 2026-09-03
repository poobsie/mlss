#include "global.h"
#include "mario_bros/object.h"

#define MB_LATE_SECTION(name) __attribute__((section(".text.mariobros_late." #name)))
#define MB_HELPER_SECTION(name) __attribute__((section(".text.mariobros_helpers_late." #name)))

extern u32 sub_8F6124C(u32, u32);
extern u32 sub_8F87BA0(u32, u32);
extern u8 sub_8F65EA0(void*);
extern void sub_8F63D28(void* object);

MB_LATE_SECTION(sub_8F5F3C8) void sub_8F5F3C8(struct MarioBrosObject* object) {
    object->positionX = sub_8F6124C(object->positionX, object->value18);
    object->positionY += object->value1C;
}

MB_LATE_SECTION(sub_8F611DC) void sub_8F611DC(struct MarioBrosObject* object) {
    if (sub_8F65EA0(object))
        object->state++;
}
MB_LATE_SECTION(sub_8F611DC) const u16 sub_8F611DC_padding = 0;

MB_HELPER_SECTION(sub_8F63DB8) void sub_8F63DB8(struct MarioBrosObject* object) {
    if (object->state != 7) {
        sub_8F63D28(object);
        object->value1C = -0x180;
    }
}

MB_LATE_SECTION(sub_8F85D1C) void sub_8F85D1C(struct MarioBrosObject* object) {
    object->positionX = sub_8F87BA0(object->positionX, object->value18);
    object->positionY += object->value1C;
}
