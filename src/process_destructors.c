#include "global.h"

#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.process_destructors." #name)))

extern void process_remove(void *, s32);

#define DEFINE_PROCESS_DESTRUCTOR(name, descriptor)                    \
    SEC(name) void name(void *object, s32 flags)                        \
    {                                                                    \
        FIELD(object, void *, 0x18) = (void *)(descriptor);             \
        process_remove(object, flags);                                  \
    }

DEFINE_PROCESS_DESTRUCTOR(sub_81367AC, 0x08CDC4A0)
DEFINE_PROCESS_DESTRUCTOR(sub_8168294, 0x08CDD140)
DEFINE_PROCESS_DESTRUCTOR(sub_816D96C, 0x08CDD220)
DEFINE_PROCESS_DESTRUCTOR(sub_8171FC0, 0x08CDD290)
