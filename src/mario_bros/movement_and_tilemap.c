#include "global.h"

#define SEC(name)   __attribute__((section(".text.mariobros_helpers_late." #name)))
#define U8AT(p, o)  (*(u8*)((u8*)(p) + (o)))
#define U32AT(p, o) (*(u32*)((u8*)(p) + (o)))

extern void sub_8F63D28(void* object);

SEC(sub_8F63DB8) void sub_8F63DB8(void* object) {
    if (U8AT(object, 4) != 7) {
        sub_8F63D28(object);
        U32AT(object, 0x1C) = -0x180;
    }
}

SEC(sub_8F591F8) void sub_8F591F8(void) {
    u8 row;

    for (row = 0; row <= 3; row++) {
        u8 column;
        u16* dst = (u16*)(0x0600EAD8 + row * 0x40);

        for (column = 0; column <= 6; column++)
            *dst++ = 0;
    }
}
