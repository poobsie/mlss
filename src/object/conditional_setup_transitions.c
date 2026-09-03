#include "global.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.conditional_setup_transitions." #name)))

extern void sub_8082E1C(struct RuntimeObject*, s32, s32, s32);

#define DEFINE_CONDITIONAL_SETUP_TRANSITION(name, kind, next)           \
    extern void next(struct RuntimeObject*);                             \
    SEC(name) void name(struct RuntimeObject* object)                    \
    {                                                                    \
        if (object->visual->flags & 8) {                                \
            sub_8082E1C(object, kind, 0, 0);                            \
            object->update = next;                                      \
        }                                                                \
    }

DEFINE_CONDITIONAL_SETUP_TRANSITION(sub_8060438, 8, sub_8060544)
DEFINE_CONDITIONAL_SETUP_TRANSITION(sub_806048C, 5, sub_80605F8)
DEFINE_CONDITIONAL_SETUP_TRANSITION(sub_8064DDC, 0, sub_808750C)
