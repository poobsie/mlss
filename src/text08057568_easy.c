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

struct EasyCopy3FA8 {
    u32 field_00;
    u32 field_04;
    u32 field_08;
};

struct EasyInit817C {
    u32 field_00;
    void* callback;
    u32 field_08;
    u32 field_0C;
    u32 field_10;
    u32 field_14;
};

#define DEFINE_EASY_INIT(name, callback_value) \
    void name(struct EasyInit817C* object) FUNCTION_SECTION(".text." #name); \
    void name(struct EasyInit817C* object) { \
        object->field_00 = 0; \
        object->callback = (void*)(callback_value); \
        object->field_08 = 0; \
        object->field_0C = 0; \
        object->field_10 = 0x7E00; \
        object->field_14 = 0; \
    }

DEFINE_EASY_INIT(sub_815817C, 0x08CDC570);
DEFINE_EASY_INIT(sub_815E9EC, 0x08CDCAD0);

#define DEFINE_EASY_CALLBACK(name, callback_value) \
    void name(struct EasyInit817C* object) FUNCTION_SECTION(".text." #name); \
    void name(struct EasyInit817C* object) { \
        object->callback = (void*)(callback_value); \
        object->field_00 = 0; \
    }

DEFINE_EASY_CALLBACK(sub_8158198, 0x08CDCA30);
DEFINE_EASY_CALLBACK(sub_815EA08, 0x08CDCF50);

void sub_8150DE8(void* object, u32 value) FUNCTION_SECTION(".text.sub_8150DE8");
void sub_8150DE8(void* object, u32 value) {
    *(u32*)((u8*)object + 0x30) = value;
}

u32 sub_8150DEC(void* object) FUNCTION_SECTION(".text.sub_8150DEC");
u32 sub_8150DEC(void* object) {
    return *(u32*)((u8*)object + 0x34);
}

void sub_81582C4(void* object) FUNCTION_SECTION(".text.sub_81582C4");
void sub_81582C4(void* object) {
    *(u32*)((u8*)object + 0x20) = 0;
}
FUNCTION_SECTION(".text.sub_81582C4") const u16 sub_81582C4_padding = 0;

s32 sub_8158308(void* object) FUNCTION_SECTION(".text.sub_8158308");
s32 sub_8158308(void* object) {
    return *(s16*)((u8*)object + 0x1C);
}
FUNCTION_SECTION(".text.sub_8158308") const u16 sub_8158308_padding = 0;

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

void sub_8163FA8(struct EasyCopy3FA8* destination,
                  struct EasyCopy3FA8* source)
    FUNCTION_SECTION(".text.sub_8163FA8");
void sub_8163FA8(struct EasyCopy3FA8* destination,
                  struct EasyCopy3FA8* source) {
    destination->field_00 = source->field_00;
    destination->field_04 = source->field_04;
    destination->field_08 = source->field_08;
}
FUNCTION_SECTION(".text.sub_8163FA8") const u16 sub_8163FA8_padding = 0;

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
