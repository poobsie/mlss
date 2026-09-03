#include "global.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.object_setup_transitions." #name)))

extern void sub_8082E1C(struct RuntimeObject*, s32, s32, s32);

#define DEFINE_OBJECT_SETUP(name, kind, delay, next)                     \
    extern void next(struct RuntimeObject*);                             \
    SEC(name) void name(struct RuntimeObject* object)                    \
    {                                                                    \
        s32 mask;                                                        \
        s32 flag_value;                                                  \
        volatile u8 *flags;                                              \
        sub_8082E1C(object, kind, 0, 0);                                \
        flags = &object->visual->flags;                                 \
        flag_value = *flags;                                             \
        mask = -7;                                                       \
        flag_value &= mask;                                              \
        *flags = flag_value;                                             \
        object->timer = delay;                                          \
        object->update = next;                                          \
    }

DEFINE_OBJECT_SETUP(sub_808C62C, 7, 0x2D, sub_808C7B8)
DEFINE_OBJECT_SETUP(sub_808C65C, 3, 0x2D, sub_808C7E4)
DEFINE_OBJECT_SETUP(sub_808C68C, 7, 0x2D, sub_808C810)
DEFINE_OBJECT_SETUP(sub_808C724, 8, 0x0C, sub_808C8E0)
DEFINE_OBJECT_SETUP(sub_808C754, 3, 0x0C, sub_808C90C)
