#include "global.h"

#define SEC(name) __attribute__((section(".text.upper_aegis3." #name)))

extern void sub_80DEEA8(void *, void *, void *, u32, void *, u32, u32, u32, u32, u32, u32, void *, u32);
extern void sub_81728A4(void);
extern void sub_8172C2C(void);
extern void sub_8173004(void);
extern void sub_81733E4(void);
extern void sub_81736C0(void);
extern void sub_81743E4(void);
extern void sub_8174E9C(void);
extern void sub_817518C(void);
extern void sub_817547C(void);
extern void sub_818353C(void);
extern void sub_8183338(void);
extern void sub_8183134(void);
extern void sub_8183008(void);
extern void sub_8182EDC(void);
extern void sub_8183740(void);
extern void sub_818386C(void);
extern void sub_8183AF8(void);
extern void sub_8183D84(void);
extern void sub_8184010(void);
extern void sub_818429C(void);
extern void sub_8184528(void);
extern void sub_818475C(void);
extern void sub_8184CF4(void);
extern void sub_8184E14(void);
extern void sub_8184F34(void);
extern void sub_81858C4(void);
extern void sub_8185A00(void);
extern void sub_81866E4(void);
extern void sub_8186864(void);
extern void sub_81869C0(void);
extern void sub_8186F7C(void);
extern void sub_81870FC(void);
extern void sub_818727C(void);
extern void sub_8187E24(void);

#define DEFINE_WRAPPER(name, call_id, callback, value1, value2, value3, value4, data, value5) \
    SEC(name) void name(void *arg0, void *arg1, void *arg2, u32 arg3) { \
        sub_80DEEA8(arg0, arg1, arg2, call_id, callback, value1, value2, value3, value4, arg3, arg3, data, value5); \
    }

DEFINE_WRAPPER(sub_81768D0, 0, sub_817547C, 0x0000207D, 7, 0, 5, (void *)0x08504884, 5)
DEFINE_WRAPPER(sub_817690C, 0, sub_817518C, 0x0000207D, 7, 0, 5, (void *)0x08504870, 5)
DEFINE_WRAPPER(sub_8176948, 0, sub_8174E9C, 0x0000207D, 2, 0, 5, (void *)0x0850485C, 5)
DEFINE_WRAPPER(sub_8176ADC, 0, sub_81743E4, 0x0000207D, 9, 0, 1, (void *)0x08504828, 1)
DEFINE_WRAPPER(sub_8176CF8, 0x1f, sub_81736C0, 0x0000207D, 7, 0, 5, (void *)0x085047E8, 5)
DEFINE_WRAPPER(sub_8176D34, 0x19, sub_81733E4, 0x0000207D, 7, 0, 5, (void *)0x085047D4, 5)
DEFINE_WRAPPER(sub_8176DE8, 0, sub_8173004, 0x0000207F, 2, 0, 1, (void *)0x085047C4, 1)
DEFINE_WRAPPER(sub_8176E9C, 0, sub_8172C2C, 0x0000207C, 0xc, 0, 2, (void *)0x085047B4, 2)
DEFINE_WRAPPER(sub_8176F18, 0, sub_81728A4, 0x0000207D, 0, 0, 1, (void *)0x085047A0, 2)
DEFINE_WRAPPER(sub_818B778, 0x29, sub_8187E24, 0x000040B0, 1, 0, 1, (void *)0x08505018, 5)
DEFINE_WRAPPER(sub_818B970, 0x65, sub_818727C, 0x000040AD, 0, 0, 1, (void *)0x08504F8C, 6)
DEFINE_WRAPPER(sub_818B9AC, 0x65, sub_81870FC, 0x000040AC, 0, 0, 1, (void *)0x08504F74, 6)
DEFINE_WRAPPER(sub_818B9E8, 0x65, sub_8186F7C, 0x000040AF, 0, 0, 1, (void *)0x08504F5C, 6)
DEFINE_WRAPPER(sub_818BB14, 0x33, sub_81869C0, 0x00004079, 0, 0, 1, (void *)0x08504F28, 5)
DEFINE_WRAPPER(sub_818BB50, 0x33, sub_8186864, 0x00004079, 0, 0, 1, (void *)0x08504F14, 5)
DEFINE_WRAPPER(sub_818BB8C, 0x65, sub_81866E4, 0x00004110, 0, 0, 1, (void *)0x08504EFC, 6)
DEFINE_WRAPPER(sub_818BCB8, 0x51, sub_8185A00, 0x0000416C, 0, 0, 1, (void *)0x08504E9C, 4)
DEFINE_WRAPPER(sub_818BCF4, 0x51, sub_81858C4, 0x0000416C, 1, 0, 1, (void *)0x08504E8C, 4)
DEFINE_WRAPPER(sub_818BE30, 0x29, sub_8184F34, 0x00004183, 0, 0, 1, (void *)0x08504E64, 2)
DEFINE_WRAPPER(sub_818BE6C, 0x24, sub_8184E14, 0x00004183, 0, 0, 1, (void *)0x08504E5C, 2)
DEFINE_WRAPPER(sub_818BEA8, 0x20, sub_8184CF4, 0x00004183, 0, 0, 1, (void *)0x08504E54, 2)
DEFINE_WRAPPER(sub_818BF98, 0x15, sub_818475C, 0x00004165, 0, 0, 4, (void *)0x08504E34, 2)
DEFINE_WRAPPER(sub_818C010, 0x8d, sub_8184528, 0x000040D3, 1, 0, 1, (void *)0x08504E28, 2)
DEFINE_WRAPPER(sub_818C04C, 0x47, sub_818429C, 0x000040C4, 0, 0, 0xc, (void *)0x08504E18, 4)
DEFINE_WRAPPER(sub_818C088, 0x47, sub_8184010, 0x000040C4, 0, 0, 3, (void *)0x08504E08, 4)
DEFINE_WRAPPER(sub_818C0C4, 0x47, sub_8183D84, 0x000040C4, 0, 0, 3, (void *)0x08504DF8, 4)
DEFINE_WRAPPER(sub_818C100, 0x47, sub_8183AF8, 0x000040C4, 0, 0, 3, (void *)0x08504DE8, 4)
DEFINE_WRAPPER(sub_818C13C, 0x47, sub_818386C, 0x000040C4, 0, 0, 3, (void *)0x08504DD8, 4)
DEFINE_WRAPPER(sub_818C178, 0x29, sub_8183740, 0x0000416D, 0, 0, 1, (void *)0x08504DCC, 3)
DEFINE_WRAPPER(sub_818C1B4, 0x97, sub_818353C, 0x0000416D, 0, 0, 0xa, (void *)0x08504DB8, 5)
DEFINE_WRAPPER(sub_818C1F0, 0x83, sub_8183338, 0x0000416D, 0, 0, 1, (void *)0x08504DA4, 5)
DEFINE_WRAPPER(sub_818C22C, 0x83, sub_8183134, 0x0000416E, 0, 0, 1, (void *)0x08504D90, 5)
DEFINE_WRAPPER(sub_818C268, 0x97, sub_8183008, 0x0000416D, 0, 0, 1, (void *)0x08504D84, 3)
DEFINE_WRAPPER(sub_818C2A4, 0x97, sub_8182EDC, 0x0000416D, 0, 0, 1, (void *)0x08504D78, 3)
