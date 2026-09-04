#include "global.h"
#include "graphics/functions.h"
#include "graphics/resource.h"

#define SEC(name)   __attribute__((section(".text.high." #name)))
#define U16AT(p, o) (*(u16*)((u8*)(p) + (o)))
#define U32AT(p, o) (*(u32*)((u8*)(p) + (o)))
#define S32AT(p, o) (*(s32*)((u8*)(p) + (o)))
#define PTRAT(p, o) (*(void**)((u8*)(p) + (o)))

void free_heap_8018DA8(void*);
void sub_8021308(void*);
void sprite_hide_8021F20(void*);
void sub_80184F4(void*);
void sub_8018218(void*, void*, u32, u32, u32);

SEC(sub_816507C) void graphics_clear_tile_buffer(struct GraphicsTileBufferOwner* object) {
    u32 zero = 0;
    CpuFastSet(&zero, object->tileBuffer20, 0x01000C00);
    sprite_hide_8021F20(object->firstSprite);
    sprite_hide_8021F20(object->secondSprite);
}

SEC(sub_81650DC) void graphics_upload_tile_buffer(struct GraphicsTileBufferOwner* object) {
    sub_80184F4(object->transfer38);
    sub_8018218(object->tileBuffer20, object->transfer38, 0x3000, 0x20, 0);
}

SEC(sub_8165420) void graphics_upload_palette_state(struct GraphicsPaletteOwner* object) {
    sub_8018218(object->source04, object->destination10, 0x2000, 0x20, 0);
    *object->output2C = object->value24;
    *object->output30 = object->value28;
}

SEC(sub_816132C) u32 sub_816132C(void) {
    return 0;
}

SEC(sub_81612E4) void sub_81612E4(void* p) {
    sub_8021308(PTRAT(p, 0xC));
    PTRAT(p, 0xC) = 0;
}

SEC(sub_8167F30) void sub_8167F30(void* p) {
    U16AT(p, 0x6C) = 0;
    U16AT(p, 0x6E) = 0;
}

SEC(sub_8163264) void sub_8163264(void* p, s32 x, s32 y) {
    S32AT(p, 0x10) = x;
    S32AT(p, 8) = x;
    S32AT(p, 0) = x;
    S32AT(p, 0x14) = y;
    S32AT(p, 0xC) = y;
    S32AT(p, 4) = y;
    S32AT(p, 0x18) = x >> 8;
    S32AT(p, 0x1C) = y >> 8;
    U32AT(p, 0x24) = 0;
}

SEC(sub_81631DC) u32 sub_81631DC(void* p) {
    return PTRAT(p, 0x24) == 0;
}

SEC(sub_81632EC) void sub_81632EC(void* p, u16 count) {
    U16AT(p, 0) = count;
    if (count == 0)
        U16AT(p, 0) = 1;
    U16AT(p, 2) = 0;
}

SEC(sub_81632C8) u32 sub_81632C8(u16* p) {
    if (p[1] < p[0]) {
        p[1]++;
        if (p[1] < p[0])
            return 0;
    }
    return 1;
}

SEC(sub_816391C) void sub_816391C(void* p, void* owner, u16 value) {
    U16AT(p, 0x4C) = 0;
    U16AT(p, 0x4A) = value;
    PTRAT(p, 0x44) = (void*)0x0821282A;
    U16AT(p, 0x48) = 0;
    PTRAT(p, 0x40) = owner;
}

SEC(sub_8165250) void sub_8165250(void* p, u32 index, u16 a, u16 b, u16 c) {
    ((u16*)PTRAT(p, 0x18))[index] = a | (b << 5) | (c << 10);
}

SEC(sub_8167E9C) void sub_8167E9C(void* p, u32 flags) {
    PTRAT(p, 0x10) = (void*)0x08CDD158;
    if (flags & 1)
        free_heap_8018DA8(p);
}

SEC(sub_8163280) void sub_8163280(void* p, u32 flags) {
    if (flags & 1)
        free_heap_8018DA8(p);
}

SEC(sub_8163308) void sub_8163308(void* p, u32 flags) {
    if (flags & 1)
        free_heap_8018DA8(p);
}

SEC(sub_8165404) void sub_8165404(void* p) {
    u32 zero = 0;
    CpuFastSet(&zero, PTRAT(p, 4), 0x01000800);
}

#define PAD(name) const u16 name##_padding SEC(name) = 0
PAD(sub_8167F30);
PAD(sub_8163264);
PAD(sub_81631DC);
PAD(sub_81632EC);
PAD(sub_81632C8);
PAD(sub_8165250);
PAD(sub_8163280);
PAD(sub_8163308);
PAD(sub_81650DC);
