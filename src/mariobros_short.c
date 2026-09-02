#include "global.h"

#define FUNCTION_SECTION(name) __attribute__((section(name)))

struct Mb604Object {
    u8 pad_00[4];
    u8 counter;
    u8 pad_05;
    u16 field_06;
    u8 pad_08[3];
    u8 field_0B;
    u8 field_0C;
};

void sub_8F617E4(void*, int);

FUNCTION_SECTION(".text.mb_f60458") void sub_8F60458(struct Mb604Object* object) {
    object->field_06 = 0x1B8;
    object->field_0C = 0;
    object->field_0B = 0;
    object->counter++;
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
