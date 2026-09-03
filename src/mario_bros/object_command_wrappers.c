#include "global.h"
#include "mario_bros/functions.h"
#include "mario_bros/object.h"

#define FUNCTION_SECTION(name) __attribute__((section(name)))

void sub_8F617E4(void*, int);

FUNCTION_SECTION(".text.mb_f60458") void mario_bros_begin_timed_animation(struct MarioBrosObject* object) {
    object->value06 = 0x1B8;
    object->animationVariant = 0;
    object->animationFrame = 0;
    object->state++;
}

FUNCTION_SECTION(".text.mb_f60458") void mario_bros_run_object_command_12_a(void* object) {
    sub_8F617E4(object, 0xC);
}

FUNCTION_SECTION(".text.mb_f60f60") void mario_bros_run_object_command_12_b(void* object) {
    sub_8F617E4(object, 0xC);
}

FUNCTION_SECTION(".text.mb_f62d28") void mario_bros_run_object_command_12_c(void* object) {
    sub_8F617E4(object, 0xC);
}
