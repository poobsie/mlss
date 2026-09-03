#include "global.h"
#include "object/runtime_object.h"

#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.object_visual_setups." #name)))

extern void sub_8082E1C(struct RuntimeObject*, s32, s32, s32);

#define DEFINE_OBJECT_VISUAL_SETUP(name, sprite_value, behavior_state, next) \
    extern void next(struct RuntimeObject*);                             \
    SEC(name) s32 name(struct RuntimeObject* object)                     \
    {                                                                    \
        volatile u8 *flags;                                              \
        s32 flag_value;                                                  \
        s32 mask;                                                        \
        void *display;                                                   \
        object->descriptor = (void *)0x084FE9A4;                         \
        display = (u8 *)(*(void **)0x03000FF4) + 0x3C;                 \
        flags = &object->flags77;                                       \
        flag_value = *flags;                                             \
        mask = -0x41;                                                    \
        flag_value &= mask;                                              \
        mask = -0x21;                                                    \
        flag_value &= mask;                                              \
        *flags = flag_value;                                             \
        object->state->snapshot114 =                                    \
            FIELD(display, u16, 0x2A);                                  \
        sub_8082E1C(object, 4, 0x204D, 0);                              \
        object->visual->parameter20 = sprite_value;                      \
        object->behaviorState = behavior_state;                         \
        object->update = next;                                          \
        return 1;                                                        \
    }

DEFINE_OBJECT_VISUAL_SETUP(sub_808ED40, 0x30, 2, sub_808EE0C)
DEFINE_OBJECT_VISUAL_SETUP(sub_808FD3C, 0x10, 6, sub_808FE08)
DEFINE_OBJECT_VISUAL_SETUP(sub_8090AB4, 0x60, 1, sub_8090B80)
