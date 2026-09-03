#include "global.h"
#include "object/runtime_object.h"
#define SEC(name) __attribute__((section(".text.command_transitions." #name)))
extern void sub_8082E1C(struct RuntimeObject*, s32, s32, s32);
#define DEFINE_COMMAND_TRANSITION(name, kind, command, next)             \
    extern void next(struct RuntimeObject*);                             \
    SEC(name) void name(struct RuntimeObject* object)                    \
    {                                                                    \
        s32 mask; s32 flag_value; volatile u8 *flags;                   \
        sub_8082E1C(object, kind, command, 0);                           \
        flags = &object->visual->flags;                                 \
        flag_value = *flags; mask = -7; flag_value &= mask;             \
        flag_value |= 2; *flags = flag_value;                           \
        object->update = next;                                          \
    }
DEFINE_COMMAND_TRANSITION(sub_809B038, 2, 0x40BE, sub_809B068)
DEFINE_COMMAND_TRANSITION(sub_809C448, 11, 0x40BF, sub_809C4F8)
