#include "global.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.object_completion_gates." #name)))

#define DEFINE_OBJECT_COMPLETION_GATE(name)                              \
    SEC(name) void name(struct RuntimeObject* object)                    \
    {                                                                    \
        if (object->flags76 & 0x38) {                                   \
            runtime_object_finish_action(object);                        \
            return;                                                      \
        }                                                                \
        if (object->visual->flags & 8) {                                \
            runtime_object_finish_action(object);                        \
        }                                                                \
    }                                                                    \
    SEC(name) const u16 name##_padding = 0;

DEFINE_OBJECT_COMPLETION_GATE(sub_808FC54)
DEFINE_OBJECT_COMPLETION_GATE(sub_8091C44)
DEFINE_OBJECT_COMPLETION_GATE(sub_8092DD4)
DEFINE_OBJECT_COMPLETION_GATE(sub_8093E20)
