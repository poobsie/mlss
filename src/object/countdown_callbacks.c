#include "global.h"
#include "object/runtime_object.h"
#define SEC(name) __attribute__((section(".text.countdown_callbacks." #name)))
extern void sub_807C298(void *);
#define DEFINE_COUNTDOWN_CALLBACK(name)                                  \
    SEC(name) void name(struct RuntimeObject* object)                    \
    {                                                                    \
        s32 current = (u16)object->timer - 1;                            \
        object->timer = current;                                        \
        if ((s32)(current << 16) <= 0)                                  \
            sub_807C298(object);                                         \
    }                                                                    \
    SEC(name) const u16 name##_padding = 0;
DEFINE_COUNTDOWN_CALLBACK(sub_8067874)
DEFINE_COUNTDOWN_CALLBACK(sub_8070A7C)
