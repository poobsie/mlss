#include "global.h"
#include "object/runtime_object.h"

#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.object_visual_setups_alternate." #name)))

extern void sub_8082E1C(struct RuntimeObject*, s32, s32, s32);

#define DEFINE_OBJECT_VISUAL_SETUP_ALTERNATE(name, sprite_value, behavior_state, next) \
    extern void next(struct RuntimeObject*);                             \
    SEC(name) s32 name(struct RuntimeObject* object)                     \
    {                                                                    \
        volatile u8 *flags;                                              \
        s32 flag_value;                                                  \
        s32 mask;                                                        \
        void *display;                                                   \
        object->descriptor = (void *)0x084FE8A8;                         \
        display = *(void **)0x03000FF4;                                  \
        flags = &object->flags77;                                       \
        flag_value = *flags;                                             \
        mask = -0x41;                                                    \
        flag_value &= mask;                                              \
        mask = -0x21;                                                    \
        flag_value &= mask;                                              \
        *flags = flag_value;                                             \
        object->state->snapshot114 =                                    \
            FIELD(display, u16, 0x2A);                                  \
        sub_8082E1C(object, 4, 0x2000, 0);                              \
        object->visual->parameter20 = sprite_value;                      \
        object->behaviorState = behavior_state;                         \
        object->update = next;                                          \
        return 1;                                                        \
    }

DEFINE_OBJECT_VISUAL_SETUP_ALTERNATE(sub_808EDA8, 0x30, 2, sub_808EE30)
DEFINE_OBJECT_VISUAL_SETUP_ALTERNATE(sub_808FDA4, 0x30, 2, sub_808FE2C)
DEFINE_OBJECT_VISUAL_SETUP_ALTERNATE(sub_8090B1C, 0x60, 1, sub_8090BA4)
