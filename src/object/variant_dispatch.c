#include "global.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.object_variant_dispatch." #name)))

#define DEFINE_OBJECT_VARIANT(name, first, second)                       \
    extern void first(struct RuntimeObject*);                            \
    extern void second(struct RuntimeObject*);                           \
    SEC(name) void name(struct RuntimeObject* object)                    \
    {                                                                    \
        if (object->state->variant == RUNTIME_OBJECT_VARIANT_FIRST)      \
            first(object);                                               \
        else                                                             \
            second(object);                                              \
    }                                                                    \
    SEC(name) const u16 name##_padding = 0;

DEFINE_OBJECT_VARIANT(sub_808DD04, sub_808CDD4, sub_808D408)
DEFINE_OBJECT_VARIANT(sub_808ED18, sub_808E0F0, sub_808E650)
DEFINE_OBJECT_VARIANT(sub_808FD14, sub_808F100, sub_808F658)
DEFINE_OBJECT_VARIANT(sub_8091DD8, sub_8090FB8, sub_8091548)
DEFINE_OBJECT_VARIANT(sub_8092F68, sub_8092148, sub_80926D8)
DEFINE_OBJECT_VARIANT(sub_8093EE0, sub_8093194, sub_8093724)
