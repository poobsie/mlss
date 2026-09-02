#include "global.h"

u32 sub_8161E38(void* object);

#define FUNCTION_SECTION(name) __attribute__((section(name)))

struct UiObjectHelper {
    u8 pad_00[0x40];
    u32 state;
    void* value;
    u16 counter;
};

u32 sub_81639E0(void* object, void* value)
    FUNCTION_SECTION(".text.sub_81639E0");
u32 sub_81639E0(void* object, void* value) {
    struct UiObjectHelper* helper = object;

    helper->value = value;
    helper->counter = 0;
    helper->state = 0;
    return sub_8161E38(object);
}
__attribute__((section(".text.sub_81639E0")))
const u16 sub_81639E0_padding = 0;

void sub_81639F8(void* object, void* value)
    FUNCTION_SECTION(".text.sub_81639F8");
void sub_81639F8(void* object, void* value) {
    struct UiObjectHelper* helper = object;

    helper->value = value;
    helper->counter = 0;
    helper->state = 0;
}
__attribute__((section(".text.sub_81639F8")))
const u16 sub_81639F8_padding = 0;

void sub_8163A64(void* object, u32 value18, u32 value1C, u32 value20)
    FUNCTION_SECTION(".text.sub_8163A64");
void sub_8163A64(void* object, u32 value18, u32 value1C, u32 value20) {
    *(u32*)((u8*)object + 0x18) = value18;
    *(u32*)((u8*)object + 0x1C) = value1C;
    *(u32*)((u8*)object + 0x20) = value20;
}
