#include "global.h"

#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.object_completion_gates." #name)))

extern void sub_808DD2C(void *);

#define DEFINE_OBJECT_COMPLETION_GATE(name)                              \
    SEC(name) void name(void *object)                                    \
    {                                                                    \
        if (FIELD(object, u8, 0x76) & 0x38) {                           \
            sub_808DD2C(object);                                         \
            return;                                                      \
        }                                                                \
        if (FIELD(FIELD(object, void *, 8), u8, 0x12) & 8) {            \
            sub_808DD2C(object);                                         \
        }                                                                \
    }                                                                    \
    SEC(name) const u16 name##_padding = 0;

DEFINE_OBJECT_COMPLETION_GATE(sub_808FC54)
DEFINE_OBJECT_COMPLETION_GATE(sub_8091C44)
DEFINE_OBJECT_COMPLETION_GATE(sub_8092DD4)
DEFINE_OBJECT_COMPLETION_GATE(sub_8093E20)
