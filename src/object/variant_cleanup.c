#include "global.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.object_variant_cleanup." #name)))
#define DEFINE_VARIANT_CLEANUP(name, first, second)                       \
    extern void first(struct RuntimeObject*);                             \
    extern void second(struct RuntimeObject*);                            \
    SEC(name) s32 name(struct RuntimeObject* object)                      \
    {                                                                     \
        s16 variant = object->state->variant;                             \
        if (variant == RUNTIME_OBJECT_VARIANT_FIRST)                      \
            first(object);                                                \
        else if (variant == RUNTIME_OBJECT_VARIANT_SECOND)                \
            second(object);                                               \
        object->cleanup = sub_8087540;                                    \
        return 1;                                                         \
    }

DEFINE_VARIANT_CLEANUP(sub_808ECDC, sub_808EDA8, sub_808ED40)
DEFINE_VARIANT_CLEANUP(sub_808FCD8, sub_808FDA4, sub_808FD3C)
DEFINE_VARIANT_CLEANUP(sub_80903A0, sub_8090420, sub_80903DC)
DEFINE_VARIANT_CLEANUP(sub_809070C, sub_809078C, sub_8090748)
DEFINE_VARIANT_CLEANUP(sub_8090A78, sub_8090B1C, sub_8090AB4)
DEFINE_VARIANT_CLEANUP(sub_8091D9C, sub_8090E74, sub_8090F14)
DEFINE_VARIANT_CLEANUP(sub_8092F2C, sub_8092004, sub_80920A4)
DEFINE_VARIANT_CLEANUP(sub_8093EA4, sub_8093F8C, sub_8093F08)
DEFINE_VARIANT_CLEANUP(sub_8094538, sub_8094320, sub_80943C0)
DEFINE_VARIANT_CLEANUP(sub_8094990, sub_8094778, sub_8094818)
DEFINE_VARIANT_CLEANUP(sub_8094DE8, sub_8094BD0, sub_8094C70)
