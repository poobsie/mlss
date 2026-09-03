#include "global.h"
#include "object/runtime_object.h"
#define SEC(name) __attribute__((section(".text.conditional_command_transitions." #name)))
extern void sub_8082E1C(struct RuntimeObject*, s32, s32, s32);
#define DEFINE_CONDITIONAL_COMMAND_TRANSITION(name, command, next)       \
    extern void next(struct RuntimeObject*);                             \
    SEC(name) void name(struct RuntimeObject* object)                    \
    {                                                                    \
        s32 mask; s32 flag_value; volatile u8 *flags;                   \
        if (object->visual->flags & 8) {                                \
            sub_8082E1C(object, 3, command, 0);                          \
            flags = &object->visual->flags;                             \
            flag_value = *flags; mask = -7; flag_value &= mask;         \
            flag_value |= 2; *flags = flag_value;                       \
            object->update = next;                                      \
        }                                                                \
    }
DEFINE_CONDITIONAL_COMMAND_TRANSITION(sub_809B068, 0x40BE, sub_809B0A8)
DEFINE_CONDITIONAL_COMMAND_TRANSITION(sub_809B920, 0x40C2, sub_809BA28)
