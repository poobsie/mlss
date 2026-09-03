#include "global.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.object_completion_gates." #name)))

extern void sub_808DD2C(struct RuntimeObject*);

#define DEFINE_OBJECT_COMPLETION_GATE(name)                              \
    SEC(name) void name(struct RuntimeObject* object)                    \
    {                                                                    \
        if (object->flags76 & 0x38) {                                   \
            sub_808DD2C(object);                                         \
            return;                                                      \
        }                                                                \
        if (object->visual->flags & 8) {                                \
            sub_808DD2C(object);                                         \
        }                                                                \
    }                                                                    \
    SEC(name) const u16 name##_padding = 0;

DEFINE_OBJECT_COMPLETION_GATE(sub_808FC54)
DEFINE_OBJECT_COMPLETION_GATE(sub_8091C44)
DEFINE_OBJECT_COMPLETION_GATE(sub_8092DD4)
DEFINE_OBJECT_COMPLETION_GATE(sub_8093E20)
