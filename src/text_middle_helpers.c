#include "global.h"

#define SEC(name)   __attribute__((section(".text.middle." #name)))
#define U8AT(p, o)  (*(u8*)((u8*)(p) + (o)))
#define U16AT(p, o) (*(u16*)((u8*)(p) + (o)))
#define U32AT(p, o) (*(u32*)((u8*)(p) + (o)))
#define PTRAT(p, o) (*(void**)((u8*)(p) + (o)))

extern void sprite_hide_8021F20(void*);
extern void sprite_show_8020CBC(void*);
extern void process_remove(void*);

SEC(sub_81218E0) int sub_81218E0(void) {
    return 0;
}
SEC(sub_80E92A8) void* sub_80E92A8(void** p) {
    return *p;
}

SEC(sub_8134B64) void sub_8134B64(u16* p) {
    p[0] = 0;
    p[1] = 0;
    p[2] = 0x10;
}

SEC(sub_8136688) void sub_8136688(u32* dest, u32* src) {
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
}
SEC(sub_8136688) const u16 sub_8136688_padding = 0;

SEC(sub_81218C8) void sub_81218C8(u8* p) {
    sprite_hide_8021F20(PTRAT(p, 0x30));
}
SEC(sub_81218D4) void sub_81218D4(u8* p) {
    sprite_show_8020CBC(PTRAT(p, 0x30));
}

SEC(sub_8127E38) u32 sub_8127E38(u32 value) {
    return (value - ((*(vu16*)0x02000008 & 0xC) << 12)) << 17 >> 22;
}

SEC(sub_80FAEEC) u8 sub_80FAEEC(u8* p) {
    return U8AT(PTRAT(p, 0x24), 0x9A1);
}

SEC(sub_80FB7E0) void* sub_80FB7E0(u16 index) {
    return ((void**)0x083D7458)[index];
}
SEC(sub_80FB7F0) void* sub_80FB7F0(u16 index) {
    return ((void**)0x0851FA00)[index];
}

SEC(get_field_object_count) u8 get_field_object_count(u16 index, u8* out) {
    u8* p = ((u8**)0x083D6C58)[index];
    *out = p[1] >> 3;
    return *out;
}

SEC(sub_80FB7BC) void* sub_80FB7BC(u16 index, u8* out) {
    u8* p = ((u8**)0x083D6C58)[index];
    *out = p[0] & 0x3F;
    return p - ((p[3] << 8) | p[2]);
}

SEC(sub_8108CBC) void sub_8108CBC(u8* p) {
    U16AT(p, 0x11E) &= 0xFFF;
}

SEC(sub_810D260) void* sub_810D260(u32 value, u8* base) {
    int offset = 0;
    do {
        value >>= 4;
        offset += 4;
    } while (value != 0);
    return base + offset;
}
