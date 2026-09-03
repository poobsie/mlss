#include "global.h"
#include "object/runtime_object.h"
#define SEC(name) __attribute__((section(".text.timed_command_transitions." #name)))
extern void sub_8082E1C(struct RuntimeObject*, s32, s32, s32);
#define DEFINE_TIMED_COMMAND_TRANSITION(name, next)                       \
    extern void next(struct RuntimeObject*);                             \
    SEC(name) void name(struct RuntimeObject* object)                    \
    {                                                                    \
        s16 *timer = &object->timer;                                     \
        u16 value = *(u16 *)timer;                                       \
        if (*timer > 0)                                                  \
            *(u16 *)timer = value - 1;                                  \
        else {                                                           \
            sub_8082E1C(object, 0, 0x4108, 0);                          \
            sub_8082E1C(object->linkedObject, 6, 0x4109, 0);            \
            object->update = next;                                      \
        }                                                                \
    }
DEFINE_TIMED_COMMAND_TRANSITION(sub_809D454, sub_809CEB0)
DEFINE_TIMED_COMMAND_TRANSITION(sub_809D49C, sub_809CAF0)
