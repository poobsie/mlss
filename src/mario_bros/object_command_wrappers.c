#include "global.h"
#include "mario_bros/object.h"

#define FUNCTION_SECTION(name) __attribute__((section(name)))

void sub_8F617E4(void*, int);

FUNCTION_SECTION(".text.mb_f60458") void sub_8F60458(struct MarioBrosObject* object) {
    object->value06 = 0x1B8;
    object->animationVariant = 0;
    object->animationFrame = 0;
    object->state++;
}

FUNCTION_SECTION(".text.mb_f60458") void sub_8F6046C(void* object) {
    sub_8F617E4(object, 0xC);
}

FUNCTION_SECTION(".text.mb_f60f60") void sub_8F60F60(void* object) {
    sub_8F617E4(object, 0xC);
}

FUNCTION_SECTION(".text.mb_f62d28") void sub_8F62D28(void* object) {
    sub_8F617E4(object, 0xC);
}
