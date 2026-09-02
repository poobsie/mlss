#include "global.h"

#define M2C_FIELD(ptr, type, offset) (*(type)((u8 *)(ptr) + (offset)))
#define SECTION(name) __attribute__((section(".text.aegis_early_exact." #name)))

struct AegisBits3 {
    u8 value : 3;
};

struct AegisBit6 {
    u8 low : 6;
    u8 value : 1;
};

struct AegisCallback1A0 {
    u8 padding[0x1A0];
    void (*function)(void *, u8 *, void *);
};

void sub_80FC1F8(void);
void sub_802FAE4(void *, void *, s32);
void sub_8029A0C(void *, void *, s32);
void play_sfx_80195B4(s32, s32);
void sub_8020D40(s32);
void sub_8116654(s32, u8);
void sub_8116680(s32, u8);
void sub_8139AA0(void *);
void sub_80514C4(void);

void sub_801B748(u8 *arg0, s32 arg1, s16 arg2, s16 arg3) SECTION(sub_801B748);
void sub_801B748(u8 *arg0, s32 arg1, s16 arg2, s16 arg3)
{
    *(s32 *)(arg0 + 0) = arg1;
    *(s16 *)(arg0 + 4) = arg2;
    *(s32 *)(arg0 + 8) = arg3;
    *(s32 *)(arg0 + 0xC) = 0xFFFF0000;
}

void sub_803C424(u8 *arg0) SECTION(sub_803C424);
void sub_803C424(u8 *arg0)
{
    u8 *second = *(u8 **)(arg0 + 0x204);
    u8 *first = *(u8 **)(arg0 + 0x200);

    *(u16 *)(first + 4) = 0xB2;
    *(u16 *)(second + 4) = 0xB2;
}
SECTION(sub_803C424) const u16 sub_803C424_padding = 0;

s32 sub_803C440(void *arg0) SECTION(sub_803C440);
s32 sub_803C440(void *arg0)
{
    s32 var_r1;
    s8 temp_r0;

    var_r1 = 0;
    temp_r0 = (s8)M2C_FIELD(M2C_FIELD(arg0, void **, 0x200), u8 *, 0x344);
    if (temp_r0 == 0x1C || temp_r0 == 0x15) {
        var_r1 = 1;
    }
    return var_r1;
}

s32 sub_803C4D8(void *arg0) SECTION(sub_803C4D8);
s32 sub_803C4D8(void *arg0)
{
    u16 temp_r1;

    temp_r1 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x200), u16 *, 4);
    if ((u32)(u16)(temp_r1 - 0x10) <= 8U || (u32)(u16)(temp_r1 - 0x1D) <= 4U) {
        return 1;
    }
    return 0;
}
SECTION(sub_803C4D8) const u16 sub_803C4D8_padding = 0;

s32 sub_803E9F0(void *arg0) SECTION(sub_803E9F0);
s32 sub_803E9F0(void *arg0)
{
    return 1 & M2C_FIELD(arg0, u8 *, 0x291);
}

void sub_804FB14(void *arg0) SECTION(sub_804FB14);
void sub_804FB14(void *arg0)
{
    M2C_FIELD(arg0, s32 *, 0x18) = (s32)M2C_FIELD(arg0, s32 *, 8);
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32)M2C_FIELD(arg0, s32 *, 0xC);
    M2C_FIELD(arg0, s32 *, 0x20) = (s32)M2C_FIELD(arg0, s32 *, 0x10);
    M2C_FIELD(arg0, s32 *, 0x24) = (s32)M2C_FIELD(arg0, s32 *, 0x14);
}
SECTION(sub_804FB14) const u16 sub_804FB14_padding = 0;

void sub_804FB28(struct AegisBits3 *object, u32 value) SECTION(sub_804FB28);
void sub_804FB28(struct AegisBits3 *object, u32 value)
{
    object->value = value;
}
SECTION(sub_804FB28) const u16 sub_804FB28_padding = 0;

void sub_801AF50(void) SECTION(sub_801AF50);
void sub_801AF50(void)
{
    sub_80FC1F8();
}
SECTION(sub_801AF50) const u16 sub_801AF50_padding = 0;

void sub_801DC38(u8 *arg0) SECTION(sub_801DC38);
void sub_801DC38(u8 *arg0)
{
    ((void (*)(s32, s32))*(void **)(arg0 + 0x14))(*(s32 *)arg0, *(s32 *)(arg0 + 4));
}
SECTION(sub_801DC38) const u16 sub_801DC38_padding = 0;

void sub_8029878(void) SECTION(sub_8029878);
void sub_8029878(void)
{
    play_sfx_80195B4(0x50, -1);
}

void sub_803C538(void *arg0, void *arg1) SECTION(sub_803C538);
void sub_803C538(void *arg0, void *arg1)
{
    sub_802FAE4(arg0, arg1, 1);
}

void sub_803C898(void *arg0, void *arg1) SECTION(sub_803C898);
void sub_803C898(void *arg0, void *arg1)
{
    sub_8029A0C(arg0, arg1, 1);
}

void sub_8047D44(u8 *arg0) SECTION(sub_8047D44);
void sub_8047D44(u8 *arg0)
{
    sub_8116654(*(s32 *)(arg0 + 0x334), arg0[0x26E]);
}

void sub_8047D64(u8 *arg0) SECTION(sub_8047D64);
void sub_8047D64(u8 *arg0)
{
    sub_8116680(*(s32 *)(arg0 + 0x334), arg0[0x26E]);
}

void sub_804FAF8(u8 *arg0) SECTION(sub_804FAF8);
void sub_804FAF8(u8 *arg0)
{
    sub_8020D40(*(s32 *)(arg0 + 0x44));
    ((struct AegisBit6 *)arg0)->value = 0;
}
SECTION(sub_804FAF8) const u16 sub_804FAF8_padding = 0;

void sub_8051614(void *arg0, u8 *arg1) SECTION(sub_8051614);
void sub_8051614(void *arg0, u8 *arg1)
{
    struct AegisCallback1A0 *object = (struct AegisCallback1A0 *)arg1;
    object->function(arg0, arg1, &object->function);
}
SECTION(sub_8051614) const u16 sub_8051614_padding = 0;

void sub_80515DC(void *arg0, u8 *arg1) SECTION(sub_80515DC);
void sub_80515DC(void *arg0, u8 *arg1)
{
    sub_8139AA0(arg1);
    *(void (**)(void))(arg1 + 0x198) = (void (*)(void))sub_8051614;
    *(void (**)(void))(arg1 + 0x1A0) = sub_80514C4;
}

void sub_8051608(void *arg0, u8 *arg1) SECTION(sub_8051608);
void sub_8051608(void *arg0, u8 *arg1)
{
    sub_80515DC(arg0, arg1);
}
SECTION(sub_8051608) const u16 sub_8051608_padding = 0;
