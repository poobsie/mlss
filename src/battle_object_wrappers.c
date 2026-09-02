#include "global.h"

void sub_815FB14(void* object, void* argument, void* definition);

#define OBJECT_WRAPPER_SECTION(name) __attribute__((section(name)))
#define OBJECT_WRAPPER_BODY(address)                                      \
    void* definition = (void*)(address);                                  \
    *(void**)((u8*)object + 0x30) = definition;                           \
    sub_815FB14(object, argument, definition)

void sub_8158450(void* object, void* argument)
    OBJECT_WRAPPER_SECTION(".text.sub_8158450");
void sub_8158450(void* object, void* argument) {
    OBJECT_WRAPPER_BODY(0x08CDC5B0);
}

void sub_8158518(void* object, void* argument)
    OBJECT_WRAPPER_SECTION(".text.sub_8158518");
void sub_8158518(void* object, void* argument) {
    OBJECT_WRAPPER_BODY(0x08CDC5F0);
}

void sub_815859C(void* object, void* argument)
    OBJECT_WRAPPER_SECTION(".text.sub_815859C");
void sub_815859C(void* object, void* argument) {
    OBJECT_WRAPPER_BODY(0x08CDC670);
}

void sub_81585D8(void* object, void* argument)
    OBJECT_WRAPPER_SECTION(".text.sub_81585D8");
void sub_81585D8(void* object, void* argument) {
    OBJECT_WRAPPER_BODY(0x08CDC630);
}

void sub_8158654(void* object, void* argument)
    OBJECT_WRAPPER_SECTION(".text.sub_8158654");
void sub_8158654(void* object, void* argument) {
    OBJECT_WRAPPER_BODY(0x08CDC6B0);
}

void sub_81586FC(void* object, void* argument)
    OBJECT_WRAPPER_SECTION(".text.sub_81586FC");
void sub_81586FC(void* object, void* argument) {
    OBJECT_WRAPPER_BODY(0x08CDC6F0);
}

void sub_8158808(void* object, void* argument)
    OBJECT_WRAPPER_SECTION(".text.sub_8158808");
void sub_8158808(void* object, void* argument) {
    OBJECT_WRAPPER_BODY(0x08CDC770);
}

void sub_81588C8(void* object, void* argument)
    OBJECT_WRAPPER_SECTION(".text.sub_81588C8");
void sub_81588C8(void* object, void* argument) {
    OBJECT_WRAPPER_BODY(0x08CDC930);
}

void sub_8158920(void* object, void* argument)
    OBJECT_WRAPPER_SECTION(".text.sub_8158920");
void sub_8158920(void* object, void* argument) {
    OBJECT_WRAPPER_BODY(0x08CDC970);
}

void sub_8158994(void* object, void* argument)
    OBJECT_WRAPPER_SECTION(".text.sub_8158994");
void sub_8158994(void* object, void* argument) {
    OBJECT_WRAPPER_BODY(0x08CDC7B0);
}

void sub_81589DC(void* object, void* argument)
    OBJECT_WRAPPER_SECTION(".text.sub_81589DC");
void sub_81589DC(void* object, void* argument) {
    OBJECT_WRAPPER_BODY(0x08CDC7F0);
}

void sub_8158A50(void* object, void* argument)
    OBJECT_WRAPPER_SECTION(".text.sub_8158A50");
void sub_8158A50(void* object, void* argument) {
    OBJECT_WRAPPER_BODY(0x08CDC830);
}

void sub_8158AEC(void* object, void* argument)
    OBJECT_WRAPPER_SECTION(".text.sub_8158AEC");
void sub_8158AEC(void* object, void* argument) {
    OBJECT_WRAPPER_BODY(0x08CDC870);
}
