#include "global.h"

#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.script_dispatch." #name)))
#define DEFINE_DISPATCH(name, first, second)                              \
    extern void first(void *);                                            \
    extern void second(void *);                                           \
    extern void sub_8087540(void);                                        \
    SEC(name) s32 name(void *object)                                     \
    {                                                                     \
        s16 value = FIELD(FIELD(object, void *, 0x28), s16, 0xEC);       \
        if (value == -1)                                                  \
            first(object);                                                \
        else if (value == -2)                                             \
            second(object);                                               \
        FIELD(object, void *, 0x68) = sub_8087540;                        \
        return 1;                                                         \
    }

DEFINE_DISPATCH(sub_808ECDC, sub_808EDA8, sub_808ED40)
DEFINE_DISPATCH(sub_808FCD8, sub_808FDA4, sub_808FD3C)
DEFINE_DISPATCH(sub_80903A0, sub_8090420, sub_80903DC)
DEFINE_DISPATCH(sub_809070C, sub_809078C, sub_8090748)
DEFINE_DISPATCH(sub_8090A78, sub_8090B1C, sub_8090AB4)
DEFINE_DISPATCH(sub_8091D9C, sub_8090E74, sub_8090F14)
DEFINE_DISPATCH(sub_8092F2C, sub_8092004, sub_80920A4)
DEFINE_DISPATCH(sub_8093EA4, sub_8093F8C, sub_8093F08)
DEFINE_DISPATCH(sub_8094538, sub_8094320, sub_80943C0)
DEFINE_DISPATCH(sub_8094990, sub_8094778, sub_8094818)
DEFINE_DISPATCH(sub_8094DE8, sub_8094BD0, sub_8094C70)
