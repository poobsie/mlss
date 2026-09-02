#include "global.h"

#define SEC(name) __attribute__((section(".text.high." #name)))
#define U8AT(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define U16AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U32AT(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define S32AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTRAT(p, o) (*(void **)((u8 *)(p) + (o)))

/* Rejected drafts remain local to this translation unit and are discarded. */
#define sub_8163A6C rejected_sub_8163A6C
#define sub_8160EC4 rejected_sub_8160EC4
#define sub_819B0F8 rejected_sub_819B0F8
#define sub_819B19C rejected_sub_819B19C
#define sub_8199D5C rejected_sub_8199D5C
#define sub_816156C rejected_sub_816156C
#define sub_816127C rejected_sub_816127C
#define sub_8163A08 rejected_sub_8163A08
#define sub_C rejected_sub_8163A6C
#define sub_8163650 rejected_sub_8163650
#define sub_8163110 rejected_sub_C_8163110
#define sub_8161954 rejected_sub_8161954
#define sub_81639C4 rejected_sub_81639C4
#define sub_816B0E0 rejected_sub_816B0E0
#define sub_816B21C rejected_sub_816B21C
#define sub_816D6C0 rejected_sub_816D6C0
#define sub_819B9B4 rejected_sub_819B9B4
#define sub_819BA10 rejected_sub_819BA10
#define sub_81DCE7C rejected_sub_81DCE7C
#define sub_81DCF6C rejected_sub_81DCF6C
#define sub_819A9B4 rejected_sub_819A9B4
#define sub_8171B44 rejected_sub_8171B44
#define sub_8199480 rejected_sub_8199480
#define sub_81DC49C rejected_sub_81DC49C
#define sub_81DC4B0 rejected_sub_81DC4B0

extern void free_heap_8018DA8(void *);
extern void sub_8021308(void *);
extern void sub_816391C(void *, void *, u16);
extern void sub_8163B60(void *);
extern void stop_sfx_80195A8(u32);
extern void play_sfx_80195B4(u32, s32);
extern u32 sub_81DA690(s16, s16);
extern u32 sub_819B418(u16);
extern u16 sub_81DA870(u16, u32, u32);
extern void sub_81DC7CC(void);
extern void _call_via_r0(void);
extern void sub_81DC4C8(void);
extern void *sub_81DD2E0(void);
extern void *sub_81DCF58(void);
extern void sub_8161330(void);

SEC(sub_816132C) u32 sub_816132C(void) { return 0; }

SEC(sub_8199F24) void sub_8199F24(void *p) { *(void **)0x03001074 = p; }
SEC(sub_81DD2E0) void *sub_81DD2E0(void) { return *(void **)0x08CDBD64; }

SEC(sub_8167F30) void sub_8167F30(void *p)
{ U16AT(p, 0x6C) = 0; U16AT(p, 0x6E) = 0; }

SEC(sub_8199470) u8 sub_8199470(u8 *p)
{ *p = *(vu16 *)0x04000006; return *p; }

SEC(sub_8163A6C) void sub_8163A6C(void *p)
{ U16AT(p, 0x54) = U16AT(p, 0x52); U16AT(p, 0x58) = U16AT(p, 0x56); }

SEC(sub_8199D48) u32 sub_8199D48(void *p, u32 index)
{ PTRAT(p, 4) = ((void **)*(void **)0x03001070)[index]; return 0; }

SEC(sub_819A694) void sub_819A694(void *p)
{ U16AT(p, 0) &= 0xCFFF; U8AT(p, 0x17) = U8AT(p, 0x16); }

SEC(sub_819A718) void sub_819A718(void *p)
{ U16AT(p, 0) &= 0xF9FF; U8AT(p, 0x1B) = U8AT(p, 0x1A); }

SEC(sub_81DD69C) void sub_81DD69C(void *p)
{ PTRAT(p, 0xC) = (void *)0x08CDD0D0; U32AT(p, 4)=0; U32AT(p, 0)=0; U32AT(p, 8)=0; }

SEC(sub_8160EC4) void sub_8160EC4(void *p)
{ U32AT(p, 0x804)=0; U32AT(p, 0x80C)=0; }

SEC(sub_819B0F8) void sub_819B0F8(u32 index, void *value)
{ ((void **)((u8 *)*(void **)0x03007FF0 + 0x4A4))[index] = value; }

SEC(sub_819B19C) void sub_819B19C(u32 offset)
{ U8AT(*(void **)0x03007FF0, 0x494 + offset) |= 1; }

SEC(sub_8199D5C) void *sub_8199D5C(void *p, u8 a, u8 b, void *value)
{
    void *old = PTRAT(p, 8);
    U8AT(p, 0xC)=a; U8AT(p, 0xD)=b; PTRAT(p, 8)=value;
    U8AT(p, 0x12) &= 0xDF;
    return old;
}

SEC(sub_816156C) void sub_816156C(void *p)
{ U32AT(p, 0)=0; PTRAT(p, 4)=(void *)0x08CDD060; }

SEC(sub_8163264) void sub_8163264(void *p, s32 x, s32 y)
{
    S32AT(p,0x10)=x; S32AT(p,8)=x; S32AT(p,0)=x;
    S32AT(p,0x14)=y; S32AT(p,0xC)=y; S32AT(p,4)=y;
    S32AT(p,0x18)=x>>8; S32AT(p,0x1C)=y>>8; U32AT(p,0x24)=0;
}

SEC(sub_816127C) void sub_816127C(void *p, s32 *q)
{
    s16 *out=PTRAT(p,0xC);
    out[0]=(S32AT(p,0x14)-q[0])>>8;
    out=PTRAT(p,0xC);
    out[1]=(S32AT(p,0x18)-q[1])>>8;
}

SEC(sub_81631DC) u32 sub_81631DC(void *p) { return PTRAT(p,0x24)==0; }

SEC(sub_81632EC) void sub_81632EC(void *p, u16 count)
{ U16AT(p,0)=count; if (count==0) U16AT(p,0)=1; U16AT(p,2)=0; }

SEC(sub_81632C8) u32 sub_81632C8(u16 *p)
{
    if (p[1] < p[0]) { p[1]++; if (p[1] < p[0]) return 0; }
    return 1;
}

SEC(sub_8163A08) u32 sub_8163A08(void *p)
{ return PTRAT(p,0x44)==0 || U32AT(p,0x40)==1; }

SEC(sub_816391C) void sub_816391C(void *p, void *owner, u16 value)
{
    U16AT(p,0x4C)=0; U16AT(p,0x4A)=value; PTRAT(p,0x44)=(void *)0x0821282A;
    U16AT(p,0x48)=0; PTRAT(p,0x40)=owner;
}

SEC(sub_8163650) void sub_8163650(void *p, u32 row, u32 col)
{
    void *q=((void **)((u8 *)p+4))[(row*3)+(col-1)];
    PTRAT(q,0x44)=(void *)0x08212934; U16AT(q,0x48)=0; U32AT(q,0x40)=0;
}

SEC(sub_8163110) u32 sub_8163110(u16 value)
{
    u32 shift=(value & 0x1F00)>>8;
    u32 index=(value>>5)&7;
    u32 *base=*(u32 **)0x03000FC0;
    return (base[8+index]>>shift)&1;
}

SEC(sub_8160E4C) void sub_8160E4C(void *source)
{
    vu32 *dma=(vu32 *)0x040000D4;
    dma[0]=(u32)source; dma[1]=U32AT(source,0x810); dma[2]=0x84000200; (void)dma[2];
}

SEC(sub_8161954) void *sub_8161954(void *p)
{
    U32AT(p,8)=0; U32AT(p,0x10)=0; U32AT(p,0xC)=0; U32AT(p,0x14)=0;
    U16AT(p,0)=0; U16AT(p,2)=0; U16AT(p,4)=0; U16AT(p,6)=0; return p;
}

SEC(sub_8165250) void sub_8165250(void *p, u32 index, u16 a, u16 b, u16 c)
{ ((u16 *)PTRAT(p,0x18))[index] = a | (b<<5) | (c<<10); }

#define DEFINE_DESTROY(name, off, vtable) SEC(name) void name(void *p, u32 flags) { \
    PTRAT(p,off)=(void *)(vtable); if (flags&1) free_heap_8018DA8(p); }
DEFINE_DESTROY(sub_816154C,4,0x08CDD090)
DEFINE_DESTROY(sub_8167E9C,0x10,0x08CDD158)
DEFINE_DESTROY(sub_81DD5B0,0x338,0x08CDBDE8)
DEFINE_DESTROY(sub_81DD5D4,0x338,0x08CDBDE8)
DEFINE_DESTROY(sub_81DD5F8,0x338,0x08CDBDE8)
DEFINE_DESTROY(sub_81DD670,4,0x08CDCF50)

#define DEFINE_FREE_IF_REQUESTED(name) SEC(name) void name(void *p, u32 flags) { \
    if (flags&1) free_heap_8018DA8(p); }
DEFINE_FREE_IF_REQUESTED(sub_8163280)
DEFINE_FREE_IF_REQUESTED(sub_8163308)

SEC(sub_81612E4) void sub_81612E4(void *p)
{ sub_8021308(PTRAT(p,0xC)); PTRAT(p,0xC)=0; }

SEC(sub_81639C4) void sub_81639C4(void *p, void *owner)
{ sub_816391C(p,(void *)6,(u32)owner); }

SEC(sub_816AFDC) void sub_816AFDC(void *p) { U32AT(p,0x490)&=~8; }

#define DEFINE_INIT_3B60(name, vtable) SEC(name) void name(void *p) { \
    PTRAT(p,0xC)=(void *)(vtable); sub_8163B60(p); }
DEFINE_INIT_3B60(sub_816B0E0,0x08CDD1C8)
DEFINE_INIT_3B60(sub_816B21C,0x08CDD1D8)
DEFINE_INIT_3B60(sub_816D6C0,0x08CDD248)

SEC(sub_816D6D4) void sub_816D6D4(void *p)
{ if (U32AT(p,0x88)!=0) { U32AT(p,0x88)=0; stop_sfx_80195A8(0x97); } }
SEC(sub_816D6F0) void sub_816D6F0(void *p)
{ if (U32AT(p,0x88)==0) { U32AT(p,0x88)=1; play_sfx_80195B4(0x97,-1); } }
SEC(sub_8171DD4) void sub_8171DD4(void *p)
{ if (U16AT(p,0xEA)!=0) { U16AT(p,0xEA)=0; stop_sfx_80195A8(0x97); } }

SEC(sub_8171B44) void sub_8171B44(void *p)
{ if (*(vu16 *)((u8 *)0x0300034C+0x2A) & 8) U32AT(p,0x44)=4; }

SEC(sub_8199480) u8 sub_8199480(s16 x,s16 y) { return ((u16)sub_81DA690(x,y))>>8; }

#define DEFINE_SOUND1(name, expr) SEC(name) u32 name(u32 a,u32 b) { return sub_819B418((u16)(expr)); }
DEFINE_SOUND1(sub_819B970,(a<<8)|b)
DEFINE_SOUND1(sub_819B984,(a<<8)|0x1000)
DEFINE_SOUND1(sub_819B99C,(a<<8)|0x2000)
DEFINE_SOUND1(sub_819B9B4,(a<<8)|0x9000|b)
DEFINE_SOUND1(sub_819B9D0,a|0x5000)
DEFINE_SOUND1(sub_819B9E8,a|0x6000)
DEFINE_SOUND1(sub_819BA00,0x7000)
DEFINE_SOUND1(sub_819BA10,(a<<8)|0x8000|b)

SEC(sub_81DA85C) u16 sub_81DA85C(u16 value, u32 arg) { return sub_81DA870(value,arg,1); }

SEC(sub_8165404) void sub_8165404(void *p)
{ u32 zero=0; CpuFastSet(&zero,PTRAT(p,4),0x01000800); }

SEC(sub_81DCE7C) s32 sub_81DCE7C(void *value)
{
    s32 i=0; void **p=(void **)0x03001A78;
    while (i<=0x13 && *p!=value) { p+=2; i++; }
    return i;
}

SEC(sub_81DCF6C) void *sub_81DCF6C(void *p)
{ void *q=sub_81DD2E0(); *(void **)q=sub_81DCF58(); return p; }

SEC(sub_81DD690) void sub_81DD690(void) { sub_8161330(); }

SEC(sub_819A9B4) u8 sub_819A9B4(s32 value)
{ if(value<=0x14) return 0xD7; if(value<=0x50) return ((u8 *)0x0821CA74)[value-0x15]; return 0; }

SEC(sub_81DC49C) u32 sub_81DC49C(void)
{ ((void (*)(void))*(void **)0x08CDB630)(); return 8; }

SEC(sub_81DC4B0) void sub_81DC4B0(void)
{ *(void **)0x08CDB630=sub_81DC4C8; ((void (*)(void))sub_81DC4C8)(); }

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
PAD(sub_819B970);
PAD(sub_819B9D0);
PAD(sub_819B9E8);
PAD(sub_819BA00);
PAD(sub_81DD690);
