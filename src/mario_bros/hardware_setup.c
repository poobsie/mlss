#include "global.h"

#define MB_LATE_SECTION(name) __attribute__((section(".text.mariobros_late." #name)))

void _08F6F340(u32);

MB_LATE_SECTION(sub_8F510CC) void sub_8F510CC(void) {
    *(volatile u16*)0x04000004 = 0;
    *(volatile u16*)0x04000200 = 0;
    *(volatile u16*)0x04000208 = 0;
}

MB_LATE_SECTION(sub_8F5C06C) void sub_8F5C06C(void) {
    *(u32*)0x0203FFF8 = 0;
    *(u8*)0x0203FFFC = 0;
    *(u8*)0x0203FFFF = (*(u8*)0x0203FFFF & 0xFC) | 2;
    _08F6F340(0x9C);
}
