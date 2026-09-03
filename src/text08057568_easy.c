#include "global.h"

#define FUNCTION_SECTION(name) __attribute__((section(name)))

struct EasyState38B0 {
    u32 field_00;
    u32 field_04;
    u32 field_08;
    void* callback;
};

struct EasyPair3320 {
    u16 field_00;
    u16 field_02;
};

void sub_816168C(void* object) FUNCTION_SECTION(".text.sub_816168C");
void sub_816168C(void* object) {
    *(void**)object = (void*)0x08CDD0B8;
}

void sub_8163320(struct EasyPair3320* object)
    FUNCTION_SECTION(".text.sub_8163320");
void sub_8163320(struct EasyPair3320* object) {
    object->field_00 = 0x10;
    object->field_02 = 0;
}
FUNCTION_SECTION(".text.sub_8163320") const u16 sub_8163320_padding = 0;

void sub_81638B0(struct EasyState38B0* object)
    FUNCTION_SECTION(".text.sub_81638B0");
void sub_81638B0(struct EasyState38B0* object) {
    object->field_04 = 0;
    object->field_00 = 0;
    object->field_08 = 0;
    object->callback = (void*)0x08CDD0E8;
}

u32 sub_8163748(void* object) FUNCTION_SECTION(".text.sub_8163748");
u32 sub_8163748(void* object) {
    return *(void**)object == 0;
}
FUNCTION_SECTION(".text.sub_8163748") const u16 sub_8163748_padding = 0;

void sub_8163B5C(void* object, u32 value)
    FUNCTION_SECTION(".text.sub_8163B5C");
void sub_8163B5C(void* object, u32 value) {
    *(u32*)((u8*)object + 0x64) = value;
}

void sub_8163BB8(void) FUNCTION_SECTION(".text.sub_8163BB8");
void sub_8163BB8(void) {
    *(u16*)0x0300102C = 0;
}

void sub_816544C(void* object, u32 value24, u32 value28)
    FUNCTION_SECTION(".text.sub_816544C");
void sub_816544C(void* object, u32 value24, u32 value28) {
    *(u32*)((u8*)object + 0x24) = value24;
    *(u32*)((u8*)object + 0x28) = value28;
}
FUNCTION_SECTION(".text.sub_816544C") const u16 sub_816544C_padding = 0;

void sub_816AFF0(void* object) FUNCTION_SECTION(".text.sub_816AFF0");
void sub_816AFF0(void* object) {
    *(u32*)((u8*)object + 0x490) |= 8;
}
