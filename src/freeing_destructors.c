#include "global.h"

#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.freeing_destructors." #name)))

extern void free_heap_8018DA8(void *);

#define DEFINE_FREEING_DESTRUCTOR(name, field_offset, descriptor)      \
    SEC(name) void name(void *object, s32 flags)                        \
    {                                                                    \
        FIELD(object, void *, field_offset) = (void *)(descriptor);     \
        if (flags & 1)                                                   \
            free_heap_8018DA8(object);                                  \
    }

DEFINE_FREEING_DESTRUCTOR(sub_8159378, 4, 0x08CDCA30)
DEFINE_FREEING_DESTRUCTOR(sub_81593B8, 4, 0x08CDCA30)
DEFINE_FREEING_DESTRUCTOR(sub_81593DC, 4, 0x08CDCA30)
DEFINE_FREEING_DESTRUCTOR(sub_8159400, 4, 0x08CDCA30)
DEFINE_FREEING_DESTRUCTOR(sub_8159440, 4, 0x08CDCA30)
DEFINE_FREEING_DESTRUCTOR(sub_8159464, 4, 0x08CDCA30)
DEFINE_FREEING_DESTRUCTOR(sub_8161580, 4, 0x08CDD090)
DEFINE_FREEING_DESTRUCTOR(sub_81615B4, 4, 0x08CDD090)
DEFINE_FREEING_DESTRUCTOR(sub_8163D4C, 0x0C, 0x08CDD118)
DEFINE_FREEING_DESTRUCTOR(sub_81DD648, 4, 0x08CDCA30)
