#include "global.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.countdown_transitions." #name)))

extern void sub_8082E1C(struct RuntimeObject*, s32, s32, s32);

#define DEFINE_COUNTDOWN_TRANSITION(name, kind, next)                   \
    extern void next(struct RuntimeObject*);                             \
    SEC(name) void name(struct RuntimeObject* object)                    \
    {                                                                    \
        s32 current;                                                     \
        if (object->visual->flags & 8) {                                \
            current = (u16)object->timer - 1;                            \
            object->timer = current;                                    \
            if ((s32)(current << 16) <= 0) {                            \
                sub_8082E1C(object, kind, 0, 0);                        \
                object->update = next;                                  \
            }                                                            \
        }                                                                \
    }

DEFINE_COUNTDOWN_TRANSITION(sub_805DF4C, 5, sub_805DA78)
DEFINE_COUNTDOWN_TRANSITION(sub_8063C8C, 13, sub_8063C60)
DEFINE_COUNTDOWN_TRANSITION(sub_806EADC, 11, sub_808750C)
