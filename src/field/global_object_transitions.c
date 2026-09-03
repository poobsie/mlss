#include "field/global_object_transitions.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(symbol) \
    __attribute__((section(".text.misc_helpers_02." STRINGIFY(symbol))))

#define FIELD_OBJECT_RUNTIME (*(struct FieldObjectRuntime**)0x03000FD8)

void sub_8072550(struct RuntimeObject* object);
void sub_80725D0(struct RuntimeObject* object);
void sub_8082E1C(
    struct RuntimeObject* object, s32 animation, s32 command, s32 argument);

#define START_FIRST_OBJECT_ANIMATION_47(object, continuation)                \
    do {                                                                     \
        sub_8082E1C(&FIELD_OBJECT_RUNTIME->firstObjectOwner->object,          \
                    0x2F, 0, 0);                                             \
        (object)->update = (continuation);                                    \
    } while (0)

SEC(field_start_first_object_animation_47_then_continue_a)
void field_start_first_object_animation_47_then_continue_a(
    struct RuntimeObject* object)
{
    START_FIRST_OBJECT_ANIMATION_47(object, sub_8072550);
}

SEC(field_start_first_object_animation_47_then_continue_b)
void field_start_first_object_animation_47_then_continue_b(
    struct RuntimeObject* object)
{
    START_FIRST_OBJECT_ANIMATION_47(object, sub_80725D0);
}
