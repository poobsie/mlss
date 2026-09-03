#include "global.h"

#define FUNCTION_SECTION(name) __attribute__((section(name)))

void sub_816168C(void* object) FUNCTION_SECTION(".text.sub_816168C");
void sub_816168C(void* object) {
    *(void**)object = (void*)0x08CDD0B8;
}

void sub_816AFF0(void* object) FUNCTION_SECTION(".text.sub_816AFF0");
void sub_816AFF0(void* object) {
    *(u32*)((u8*)object + 0x490) |= 8;
}
