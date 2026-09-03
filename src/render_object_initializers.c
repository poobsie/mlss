#include "global.h"

#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.render_object_initializers." #name)))

extern void sub_815F8F4();
extern void sub_815F97C(void *, s32);

#define DEFINE_RENDER_OBJECT_INITIALIZER(name, descriptor)              \
    SEC(name) void *name(void *object, s32 mode, u16 value)             \
    {                                                                    \
        sub_815F8F4();                                                   \
        FIELD(object, void *, 0x30) = (void *)(descriptor);             \
        FIELD(object, u16, 0x34) = value;                               \
        sub_815F97C(object, 0);                                         \
        return object;                                                   \
    }

#define DEFINE_ACTIVE_RENDER_OBJECT_INITIALIZER(name, descriptor)       \
    SEC(name) void *name(void *object, s32 mode, u16 value)             \
    {                                                                    \
        sub_815F8F4();                                                   \
        FIELD(object, void *, 0x30) = (void *)(descriptor);             \
        FIELD(object, u16, 0x34) = value;                               \
        FIELD(object, u8, 0x24) = 1;                                   \
        return object;                                                   \
    }

DEFINE_RENDER_OBJECT_INITIALIZER(sub_81585B0, 0x08CDC670)
DEFINE_RENDER_OBJECT_INITIALIZER(sub_8158710, 0x08CDC6F0)
DEFINE_RENDER_OBJECT_INITIALIZER(sub_815EE08, 0x08CDCB90)
DEFINE_RENDER_OBJECT_INITIALIZER(sub_815EE88, 0x08CDCBD0)
DEFINE_RENDER_OBJECT_INITIALIZER(sub_815EF58, 0x08CDCC10)
DEFINE_ACTIVE_RENDER_OBJECT_INITIALIZER(sub_815881C, 0x08CDC770)
DEFINE_ACTIVE_RENDER_OBJECT_INITIALIZER(sub_815F064, 0x08CDCC90)
