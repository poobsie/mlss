#include "global.h"

#define MB_LATE_SECTION(name) __attribute__((section(".text.mariobros_late." #name)))

extern void sub_8F6F360(void*, void*);
extern void sub_8F6F364(void*, void*, void*);
extern void sub_8F95EC0(void*, void*);
extern void sub_8F6D170(void);

MB_LATE_SECTION(sub_8F6DE98) void sub_8F6DE98(void) {
    sub_8F6D170();
}
MB_LATE_SECTION(sub_8F6DE98) const u16 sub_8F6DE98_padding = 0;

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
