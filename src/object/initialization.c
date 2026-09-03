#include "global.h"
#include "object/runtime_object.h"

#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.object_initialization." #name)))

#define DEFINE_OBJECT_INIT(name, next)                                   \
    extern void next(struct RuntimeObject*);                             \
    SEC(name) s32 name(struct RuntimeObject* object)                     \
    {                                                                    \
        void *source;                                                    \
        volatile u8 *flags;                                              \
        s32 flag_value;                                                  \
        s32 mask;                                                        \
        object->descriptor = (void *)0x084FE9A4;                         \
        source = (u8 *)*(void **)0x03000FF4 + 0x3C;                     \
        flags = &object->flags77;                                       \
        flag_value = *flags;                                             \
        mask = -0x41;                                                    \
        flag_value &= mask;                                              \
        mask = -0x21;                                                    \
        flag_value &= mask;                                              \
        *flags = flag_value;                                             \
        object->state->snapshot114 =                                    \
            FIELD(source, u16, 0x2A);                                   \
        object->update = next;                                          \
        return 1;                                                        \
    }

DEFINE_OBJECT_INIT(sub_808DD9C, sub_808DE44)
DEFINE_OBJECT_INIT(sub_80903DC, sub_8090460)
DEFINE_OBJECT_INIT(sub_8090748, sub_80907CC)
