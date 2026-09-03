#include "global.h"

#define SEC(name)   __attribute__((section(".text.text_late_helpers." #name)))
#define U8AT(p, o)  (*(u8*)((u8*)(p) + (o)))
#define U16AT(p, o) (*(u16*)((u8*)(p) + (o)))
#define U32AT(p, o) (*(u32*)((u8*)(p) + (o)))
#define PTRAT(p, o) (*(void**)((u8*)(p) + (o)))

extern void* sub_815FA3C(void* object);
extern void sub_8021FD4(void* object);

SEC(sub_8150A38) void sub_8150A38(void* object) {
    sub_8021FD4(object);
}
SEC(sub_8150A38) const u16 sub_8150A38_padding = 0;

SEC(sub_8158F60) void sub_8158F60(void* object) {
    s16* timer = (s16*)((u8*)object + 0x1F2A);

    --*timer;
    if (*timer < 0)
        U16AT(object, 0x1F28) = 0;
}

SEC(sub_8158A98) void sub_8158A98(void* object, s32 value) {
    void* child;
    u16 zero = 0;

    U16AT(object, 0x18) = 0xC8;
    U16AT(object, 0x20) = -value;
    U16AT(object, 0x38) = zero;
    child = sub_815FA3C(object);
    U16AT(child, 0xC) = zero;
    U8AT(object, 0x24) = 4;
}

SEC(sub_815F2C4) void sub_815F2C4(void* object, s32 value) {
    void* child;
    u16 zero = 0;

    U16AT(object, 0x18) = 0x64;
    U16AT(object, 0x20) = -value;
    U16AT(object, 0x38) = zero;
    child = sub_815FA3C(object);
    U16AT(child, 0xC) = zero;
    U8AT(object, 0x24) = 3;
}
