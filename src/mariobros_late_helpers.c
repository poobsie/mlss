#include "global.h"

#define MB_LATE_SECTION(name) __attribute__((section(".text.mariobros_late." #name)))

extern void sub_8F6F360(void*, void*);
extern void sub_8F6F364(void*, void*, void*);
extern void sub_8F95EC0(void*, void*);
extern u32 sub_8F6124C(u32, u32);
extern u32 sub_8F87BA0(u32, u32);
extern u8 sub_8F65EA0(void*);
extern void sub_8F6D170(void);
extern void _08F6F340(u32);

struct MbLateObject {
    u8 pad_00[4];
    u8 state;
    u8 pad_05;
    u16 field_06;
    u8 pad_08[3];
    u8 frame;
    u8 variant;
    u8 pad_0D[3];
    u32 x;
    u32 y;
    u32 dx;
    u32 dy;
};

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

MB_LATE_SECTION(sub_8F5F3C8) void sub_8F5F3C8(struct MbLateObject* object) {
    object->x = sub_8F6124C(object->x, object->dx);
    object->y += object->dy;
}

MB_LATE_SECTION(sub_8F611DC) void sub_8F611DC(struct MbLateObject* object) {
    if (sub_8F65EA0(object))
        object->state++;
}
MB_LATE_SECTION(sub_8F611DC) const u16 sub_8F611DC_padding = 0;

MB_LATE_SECTION(sub_8F6DE98) void sub_8F6DE98(void) {
    sub_8F6D170();
}
MB_LATE_SECTION(sub_8F6DE98) const u16 sub_8F6DE98_padding = 0;

MB_LATE_SECTION(sub_8F85D1C) void sub_8F85D1C(struct MbLateObject* object) {
    object->x = sub_8F87BA0(object->x, object->dx);
    object->y += object->dy;
}

MB_LATE_SECTION(sub_8F6E1F8) void sub_8F6E1F8(void* object) {
    sub_8F6F360(object, *(void**)0x03006AE8);
}

MB_LATE_SECTION(sub_8F6E20C) void sub_8F6E20C(void* object) {
    sub_8F6F360(object, *(void**)0x03006AEC);
}

MB_LATE_SECTION(sub_8F6F210) void sub_8F6F210(void* arg0, void* arg1) {
    sub_8F6F364(arg0, arg1, *(void**)0x03006A60);
}

MB_LATE_SECTION(sub_8F94D78) void sub_8F94D78(void* object) {
    sub_8F95EC0(object, *(void**)0x03006A28);
}

MB_LATE_SECTION(sub_8F94D8C) void sub_8F94D8C(void* object) {
    sub_8F95EC0(object, *(void**)0x03006A2C);
}
