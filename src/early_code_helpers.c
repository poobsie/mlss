#include "global.h"

#define FIELD_AT(ptr, type, offset) (*(type)((u8*)(ptr) + (offset)))
#define SECTION(name)               __attribute__((section(".text.early_code_helpers." #name)))

struct LowThreeBits {
    u8 value : 3;
};

struct LowTwoBits {
    u8 value : 2;
};

struct BitSix {
    u8 low : 6;
    u8 value : 1;
};

struct CallbackAt1A0 {
    u8 padding[0x1A0];
    void (*function)(void*, u8*, void*);
};

void sub_80FC1F8(void);
void sub_802FAE4(void*, void*, s32);
void sub_8029A0C(void*, void*, s32);
void sub_8020D40(s32);
void sub_8139AA0(void*);
void sub_80514C4(void);

void sub_803C424(u8* arg0) SECTION(sub_803C424);
void sub_803C424(u8* arg0) {
    u8* second = *(u8**)(arg0 + 0x204);
    u8* first = *(u8**)(arg0 + 0x200);

    *(u16*)(first + 4) = 0xB2;
    *(u16*)(second + 4) = 0xB2;
}
SECTION(sub_803C424) const u16 sub_803C424_padding = 0;

s32 sub_803C440(void* arg0) SECTION(sub_803C440);
s32 sub_803C440(void* arg0) {
    s32 var_r1;
    s8 temp_r0;

    var_r1 = 0;
    temp_r0 = (s8)FIELD_AT(FIELD_AT(arg0, void**, 0x200), u8*, 0x344);
    if (temp_r0 == 0x1C || temp_r0 == 0x15) {
        var_r1 = 1;
    }
    return var_r1;
}

s32 sub_803C4D8(void* arg0) SECTION(sub_803C4D8);
s32 sub_803C4D8(void* arg0) {
    u16 temp_r1;

    temp_r1 = FIELD_AT(FIELD_AT(arg0, void**, 0x200), u16*, 4);
    if ((u32)(u16)(temp_r1 - 0x10) <= 8U || (u32)(u16)(temp_r1 - 0x1D) <= 4U) {
        return 1;
    }
    return 0;
}
SECTION(sub_803C4D8) const u16 sub_803C4D8_padding = 0;

s32 sub_803E9F0(void* arg0) SECTION(sub_803E9F0);
s32 sub_803E9F0(void* arg0) {
    return 1 & FIELD_AT(arg0, u8*, 0x291);
}

void sub_804FB14(void* arg0) SECTION(sub_804FB14);
void sub_804FB14(void* arg0) {
    FIELD_AT(arg0, s32*, 0x18) = (s32)FIELD_AT(arg0, s32*, 8);
    FIELD_AT(arg0, s32*, 0x1C) = (s32)FIELD_AT(arg0, s32*, 0xC);
    FIELD_AT(arg0, s32*, 0x20) = (s32)FIELD_AT(arg0, s32*, 0x10);
    FIELD_AT(arg0, s32*, 0x24) = (s32)FIELD_AT(arg0, s32*, 0x14);
}
SECTION(sub_804FB14) const u16 sub_804FB14_padding = 0;

void sub_804FB28(struct LowThreeBits* object, u32 value) SECTION(sub_804FB28);
void sub_804FB28(struct LowThreeBits* object, u32 value) {
    object->value = value;
}
SECTION(sub_804FB28) const u16 sub_804FB28_padding = 0;

void sub_801AF50(void) SECTION(sub_801AF50);
void sub_801AF50(void) {
    sub_80FC1F8();
}
SECTION(sub_801AF50) const u16 sub_801AF50_padding = 0;

void sub_801DC38(u8* arg0) SECTION(sub_801DC38);
void sub_801DC38(u8* arg0) {
    ((void (*)(s32, s32)) * (void**)(arg0 + 0x14))(*(s32*)arg0, *(s32*)(arg0 + 4));
}
SECTION(sub_801DC38) const u16 sub_801DC38_padding = 0;

void sub_8028E4C(u8* object) SECTION(sub_8028E4C);
void sub_8028E4C(u8* object) {
    *(s16*)(object + 0x2F8) = 0;
    *(s16*)(object + 0x2FC) = 0;
    ((struct LowTwoBits*)(object + 0xF9))->value = 0;
}
SECTION(sub_8028E4C) const u16 sub_8028E4C_padding = 0;

void sub_803C538(void* arg0, void* arg1) SECTION(sub_803C538);
void sub_803C538(void* arg0, void* arg1) {
    sub_802FAE4(arg0, arg1, 1);
}

void sub_803C898(void* arg0, void* arg1) SECTION(sub_803C898);
void sub_803C898(void* arg0, void* arg1) {
    sub_8029A0C(arg0, arg1, 1);
}

void sub_804FAF8(u8* arg0) SECTION(sub_804FAF8);
void sub_804FAF8(u8* arg0) {
    sub_8020D40(*(s32*)(arg0 + 0x44));
    ((struct BitSix*)arg0)->value = 0;
}
SECTION(sub_804FAF8) const u16 sub_804FAF8_padding = 0;

void sub_8051614(void* arg0, u8* arg1) SECTION(sub_8051614);
void sub_8051614(void* arg0, u8* arg1) {
    struct CallbackAt1A0* object = (struct CallbackAt1A0*)arg1;
    object->function(arg0, arg1, &object->function);
}
SECTION(sub_8051614) const u16 sub_8051614_padding = 0;

void sub_80515DC(void* arg0, u8* arg1) SECTION(sub_80515DC);
void sub_80515DC(void* arg0, u8* arg1) {
    sub_8139AA0(arg1);
    *(void (**)(void))(arg1 + 0x198) = (void (*)(void))sub_8051614;
    *(void (**)(void))(arg1 + 0x1A0) = sub_80514C4;
}

void sub_8051608(void* arg0, u8* arg1) SECTION(sub_8051608);
void sub_8051608(void* arg0, u8* arg1) {
    sub_80515DC(arg0, arg1);
}
SECTION(sub_8051608) const u16 sub_8051608_padding = 0;
