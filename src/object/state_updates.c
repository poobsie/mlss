#include "global.h"
#include "object/runtime_object.h"
#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.object_state_updates." #name)))

#define DEFINE_VISUAL_STATE_UPDATE(name, next)                        \
    extern void next(struct RuntimeObject*);                          \
    SEC(name) s32 name(struct RuntimeObject* object)                  \
    {                                                                 \
        s8 *flags;                                                     \
        void *state;                                                   \
        object->descriptor = (void *)0x084FE8A8;                      \
        state = *(void **)0x03000FF4;                                 \
        flags = (s8 *)&object->flags77;                               \
        *flags &= ~0x40;                                               \
        *flags &= ~0x20;                                               \
        object->state->snapshot114 =                                  \
            FIELD(state, u16, 0x2A);                                  \
        object->update = next;                                        \
        return 1;                                                     \
    }
DEFINE_VISUAL_STATE_UPDATE(sub_8090420, sub_80904C4)
DEFINE_VISUAL_STATE_UPDATE(sub_809078C, sub_8090830)
