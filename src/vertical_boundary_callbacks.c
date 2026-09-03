#include "global.h"
#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.vertical_boundary_callbacks." #name)))
extern void sub_8088020(void *);
extern void sub_807C298(void *);
#define DEFINE_VERTICAL_BOUNDARY_CALLBACK(name)                          \
    SEC(name) void name(void *object)                                    \
    {                                                                    \
        sub_8088020(object);                                             \
        if (FIELD(FIELD(object, void *, 8), s16, 0)                     \
                + FIELD(object, s8, 0x45) <= 0)                         \
            sub_807C298(object);                                         \
    }                                                                    \
    SEC(name) const u16 name##_padding = 0;
DEFINE_VERTICAL_BOUNDARY_CALLBACK(sub_809C13C)
DEFINE_VERTICAL_BOUNDARY_CALLBACK(sub_809C1E8)
DEFINE_VERTICAL_BOUNDARY_CALLBACK(sub_809C570)
