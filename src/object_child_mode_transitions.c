#include "global.h"

#define SECTION(name) __attribute__((section(".text.object_child_mode_transitions." #name)))
#define U8_AT(ptr, offset) (*(u8 *)((u8 *)(ptr) + (offset)))
#define U32_AT(ptr, offset) (*(u32 *)((u8 *)(ptr) + (offset)))

extern u32 sub_8087CE4(void);
extern u32 sub_80883F0(void);
extern void sub_8082E1C(void *, u32, u32, u32);
extern void sub_810FE1C(void);
extern void sub_810F9FC(void);
extern void sub_810F6D4(void);

#define DEFINE_TRANSITION(name, gate, kind, callback) \
SECTION(name) void name(void *object) \
{ \
    void *child; \
    if ((u8)gate() == 0) { \
        sub_8082E1C(object, kind, 0, 0); \
        child = (void *)U32_AT(object, 8); \
        { \
            s32 value = U8_AT(child, 0x12); \
            s32 mask = 7; \
            mask = -mask; \
            mask &= value; \
            mask |= 2; \
            U8_AT(child, 0x12) = mask; \
        } \
        U32_AT(object, 0x4C) = (u32)callback; \
    } \
}

DEFINE_TRANSITION(sub_810FBFC, sub_8087CE4, 8, sub_810FE1C)
DEFINE_TRANSITION(sub_810FF78, sub_80883F0, 7, sub_810F9FC)
DEFINE_TRANSITION(sub_8110078, sub_80883F0, 7, sub_810F6D4)
