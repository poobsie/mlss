#include "global.h"
#include "audio/sound_effects.h"

#define SEC(name)   __attribute__((section(".text.high." #name)))
#define U8AT(p, o)  (*(u8*)((u8*)(p) + (o)))
#define U16AT(p, o) (*(u16*)((u8*)(p) + (o)))
#define S16AT(p, o) (*(s16*)((u8*)(p) + (o)))
#define U32AT(p, o) (*(u32*)((u8*)(p) + (o)))
#define S32AT(p, o) (*(s32*)((u8*)(p) + (o)))
#define PTRAT(p, o) (*(void**)((u8*)(p) + (o)))

extern void free_heap_8018DA8(void*);
extern void sub_8021308(void*);
extern void sub_816391C(void*, void*, u16);
extern void sub_8163B60(void*);
extern u32 sub_81DA690(s16, s16);
extern u16 sub_81DA870(u16, u32, u32);
extern void sub_81DC7CC(void);
extern void _call_via_r0(void);
extern void sub_81DC4C8(void);
extern void* sub_81DD2E0(void);
extern void* sub_81DCF58(void);
extern void sub_8161330(void);

SEC(sub_816132C) u32 sub_816132C(void) {
    return 0;
}

SEC(sub_8199F24) void sub_8199F24(void* p) {
    *(void**)0x03001074 = p;
}
SEC(sub_81DD2E0) void* sub_81DD2E0(void) {
    return *(void**)0x08CDBD64;
}

SEC(sub_8167F30) void sub_8167F30(void* p) {
    U16AT(p, 0x6C) = 0;
    U16AT(p, 0x6E) = 0;
}

SEC(sub_8199470) u8 sub_8199470(u8* p) {
    *p = *(vu16*)0x04000006;
    return *p;
}

SEC(sub_8199D48) u32 sub_8199D48(void* p, u32 index) {
    PTRAT(p, 4) = ((void**)*(void**)0x03001070)[index];
    return 0;
}

SEC(sub_819A694) void sub_819A694(void* p) {
    U16AT(p, 0) &= 0xCFFF;
    U8AT(p, 0x17) = U8AT(p, 0x16);
}

SEC(sub_819A718) void sub_819A718(void* p) {
    U16AT(p, 0) &= 0xF9FF;
    U8AT(p, 0x1B) = U8AT(p, 0x1A);
}

SEC(sub_81DD69C) void sub_81DD69C(void* p) {
    PTRAT(p, 0xC) = (void*)0x08CDD0D0;
    U32AT(p, 4) = 0;
    U32AT(p, 0) = 0;
    U32AT(p, 8) = 0;
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

#define DEFINE_DESTROY(name, off, vtable)                                                              \
    SEC(name) void name(void* p, u32 flags) {                                                          \
        PTRAT(p, off) = (void*)(vtable);                                                               \
        if (flags & 1)                                                                                 \
            free_heap_8018DA8(p);                                                                      \
    }
DEFINE_DESTROY(sub_8167E9C, 0x10, 0x08CDD158)
DEFINE_DESTROY(sub_81DD670, 4, 0x08CDCF50)

#define DEFINE_FREE_IF_REQUESTED(name)                                                                 \
    SEC(name) void name(void* p, u32 flags) {                                                          \
        if (flags & 1)                                                                                 \
            free_heap_8018DA8(p);                                                                      \
    }
DEFINE_FREE_IF_REQUESTED(sub_8163280)
DEFINE_FREE_IF_REQUESTED(sub_8163308)

SEC(sub_81612E4) void sub_81612E4(void* p) {
    sub_8021308(PTRAT(p, 0xC));
    PTRAT(p, 0xC) = 0;
}

SEC(sub_816AFDC) void sub_816AFDC(void* p) {
    U32AT(p, 0x490) &= ~8;
}

#define DEFINE_INIT_3B60(name, vtable)                                                                 \
    SEC(name) void name(void* p) {                                                                     \
        PTRAT(p, 0xC) = (void*)(vtable);                                                               \
        sub_8163B60(p);                                                                                \
    }

SEC(sub_816D6D4) void sub_816D6D4(void* p) {
    if (U32AT(p, 0x88) != 0) {
        U32AT(p, 0x88) = 0;
        sound_effect_stop(0x97);
    }
}
SEC(sub_816D6F0) void sub_816D6F0(void* p) {
    if (U32AT(p, 0x88) == 0) {
        U32AT(p, 0x88) = 1;
        sound_effect_play(0x97, SOUND_VOLUME_UNCHANGED);
    }
}
SEC(sub_8171DD4) void sub_8171DD4(void* p) {
    if (U16AT(p, 0xEA) != 0) {
        U16AT(p, 0xEA) = 0;
        sound_effect_stop(0x97);
    }
}

SEC(sub_81DA85C) u16 sub_81DA85C(u16 value, u32 arg) {
    return sub_81DA870(value, arg, 1);
}

SEC(sub_8165404) void sub_8165404(void* p) {
    u32 zero = 0;
    CpuFastSet(&zero, PTRAT(p, 4), 0x01000800);
}

SEC(sub_81DD690) void sub_81DD690(void) {
    sub_8161330();
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
PAD(sub_816AFDC);
PAD(sub_816D6D4);
PAD(sub_816D6F0);
PAD(sub_8171DD4);
PAD(sub_81DD690);
