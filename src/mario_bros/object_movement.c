#include "global.h"
#include "mario_bros/functions.h"
#include "mario_bros/object.h"

#define MB_LATE_SECTION(name) __attribute__((section(".text.mariobros_late." #name)))
#define MB_HELPER_SECTION(name) __attribute__((section(".text.mariobros_helpers_late." #name)))

extern s32 sub_8F6124C(s32, s32);
extern s32 sub_8F87BA0(s32, s32);
extern u8 sub_8F65EA0(void*);
extern void sub_8F63D28(void* object);
extern void sub_8F609BC(struct MarioBrosObject*);
extern void sub_8F627DC(struct MarioBrosObject*);

MB_LATE_SECTION(sub_8F5F3C8) void mario_bros_update_object_position_a(struct MarioBrosObject* object) {
    object->positionX = sub_8F6124C(object->positionX, object->value18);
    object->positionY += object->value1C;
}

MB_LATE_SECTION(sub_8F611DC) void mario_bros_advance_object_state_if_ready(struct MarioBrosObject* object) {
    if (sub_8F65EA0(object))
        object->state++;
}
MB_LATE_SECTION(sub_8F611DC) const u16 sub_8F611DC_padding = 0;

MB_HELPER_SECTION(sub_8F63DB8) void mario_bros_start_object_fall_unless_state_7(struct MarioBrosObject* object) {
    if (object->state != 7) {
        sub_8F63D28(object);
        object->value1C = -0x180;
    }
}

MB_LATE_SECTION(sub_8F85D1C) void mario_bros_update_object_position_b(struct MarioBrosObject* object) {
    object->positionX = sub_8F87BA0(object->positionX, object->value18);
    object->positionY += object->value1C;
}

#define DEFINE_FALLING_ADVANCE(name, wrapped_add, post_update)                 \
    MB_LATE_SECTION(name) void name(struct MarioBrosObject* object) {           \
        s32 x = object->positionX;                                              \
        s32 y = object->positionY;                                              \
        s32 deltaX = object->value18;                                           \
        s32 deltaY = object->value1C;                                           \
        deltaY += 0x18;                                                         \
        x = wrapped_add(x, deltaX);                                             \
        y += deltaY;                                                            \
        object->positionX = x;                                                  \
        object->positionY = y;                                                  \
        object->value18 = deltaX;                                               \
        object->value1C = deltaY;                                               \
        post_update(object);                                                    \
        if (!(object->flags0A & 4)) {                                           \
            object->value1C = 0;                                                \
            object->state = 6;                                                  \
        }                                                                       \
    }

/*
 * Mirrored falling-object updates. value18/value1C remain neutral aliases:
 * this family proves they are horizontal and vertical deltas here, but other
 * Mario Bros object classes reuse the same slots for unrelated values.
 */
DEFINE_FALLING_ADVANCE(mario_bros_advance_falling_object_a, sub_8F6124C,
                       sub_8F609BC)
DEFINE_FALLING_ADVANCE(mario_bros_advance_falling_object_b, sub_8F6124C,
                       sub_8F627DC)
MB_LATE_SECTION(sub_8F60D44) const u16 sub_8F60D44_padding = 0;
MB_LATE_SECTION(sub_8F62B50) const u16 sub_8F62B50_padding = 0;

#define DEFINE_LINKED_OBJECT_PREPARE(name)                                     \
    MB_LATE_SECTION(name) void name(struct MarioBrosObject* object) {           \
        u8 zero = 0;                                                            \
        u8 value = 9;                                                           \
        object->animationVariant = value;                                       \
        object->animationFrame = zero;                                          \
        value = object->flags0A;                                                \
        zero = 0x80;                                                            \
        value |= zero;                                                          \
        object->flags0A = value;                                                \
        value = 4;                                                              \
        object->state = value;                                                  \
    }

/* The linked object's class is still unknown; only its animation/state setup is named. */
DEFINE_LINKED_OBJECT_PREPARE(mario_bros_prepare_linked_object_a)
DEFINE_LINKED_OBJECT_PREPARE(mario_bros_prepare_linked_object_b)
MB_LATE_SECTION(sub_8F62FCC) const u16 sub_8F62FCC_padding = 0;
MB_LATE_SECTION(sub_8F89920) const u16 sub_8F89920_padding = 0;
