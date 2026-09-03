#include "global.h"

#define SEC(name)   __attribute__((section(".text.text_late_helpers." #name)))
#define U8AT(p, o)  (*(u8*)((u8*)(p) + (o)))
#define U16AT(p, o) (*(u16*)((u8*)(p) + (o)))
#define U32AT(p, o) (*(u32*)((u8*)(p) + (o)))
#define PTRAT(p, o) (*(void**)((u8*)(p) + (o)))

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
