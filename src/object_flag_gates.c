#include "global.h"

#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.object_flag_gates." #name)))

extern void sub_8087540(void *);

#define DEFINE_OBJECT_FLAG_GATE(name)                                    \
    SEC(name) void name(void *object)                                    \
    {                                                                    \
        if (FIELD(FIELD(object, void *, 8), u8, 0x12) & 8)              \
            sub_8087540(object);                                         \
    }                                                                    \
    SEC(name) const u16 name##_padding = 0;

DEFINE_OBJECT_FLAG_GATE(sub_808C070)
DEFINE_OBJECT_FLAG_GATE(sub_808C098)
DEFINE_OBJECT_FLAG_GATE(sub_808C0C0)
DEFINE_OBJECT_FLAG_GATE(sub_808C0E8)
DEFINE_OBJECT_FLAG_GATE(sub_808C19C)
