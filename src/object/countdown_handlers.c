#include "global.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.countdown_handlers." #name)))
#define DEFINE_COUNTDOWN(name, next)                                                                   \
    extern void next(struct RuntimeObject*);                                                           \
    SEC(name) void name(struct RuntimeObject* object) {                                                \
        s32 value = (u16)object->timer - 1;                                                            \
        object->timer = value;                                                                        \
        if ((value << 16) <= 0)                                                                        \
            object->update = next;                                                                    \
    }

DEFINE_COUNTDOWN(sub_80604E0, sub_808750C)
DEFINE_COUNTDOWN(sub_80708F8, sub_8070938)
DEFINE_COUNTDOWN(sub_8070918, sub_806F034)
DEFINE_COUNTDOWN(sub_807411C, sub_80744B4)
DEFINE_COUNTDOWN(sub_80746EC, sub_807470C)
