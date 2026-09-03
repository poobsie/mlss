#include "global.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.object_flag_gates." #name)))

#define DEFINE_OBJECT_FLAG_GATE(name)                                    \
    SEC(name) void name(struct RuntimeObject* object)                    \
    {                                                                    \
        if (object->visual->flags & 8)                                  \
            sub_8087540(object);                                         \
    }                                                                    \
    SEC(name) const u16 name##_padding = 0;

DEFINE_OBJECT_FLAG_GATE(sub_808C070)
DEFINE_OBJECT_FLAG_GATE(sub_808C098)
DEFINE_OBJECT_FLAG_GATE(sub_808C0C0)
DEFINE_OBJECT_FLAG_GATE(sub_808C0E8)
DEFINE_OBJECT_FLAG_GATE(sub_808C19C)
