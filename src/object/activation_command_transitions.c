#include "global.h"
#include "audio/sound_effects.h"
#include "object/runtime_object.h"
#define SEC(name) __attribute__((section(".text.activation_command_transitions." #name)))
extern void sub_80884AC(struct RuntimeObject*);
extern void sub_8082E1C(struct RuntimeObject*, s32, s32, s32);
#define DEFINE_ACTIVATION_COMMAND_TRANSITION(name, next)                 \
    extern void next(struct RuntimeObject*);                             \
    SEC(name) void name(struct RuntimeObject* object)                    \
    {                                                                    \
        s8 *flags;                                                       \
        sub_80884AC(object);                                             \
        if (object->flags79 & 0x20) {                                   \
            sub_8082E1C(object, 1, 0x40C2, 0);                          \
            flags = (s8 *)&object->visual->flags;                       \
            *flags = (*flags & -7) | 2;                                 \
            sound_effect_play(0x15D, SOUND_VOLUME_UNCHANGED);                                \
            object->update = next;                                      \
        }                                                                \
    }
DEFINE_ACTIVATION_COMMAND_TRANSITION(sub_809B504, sub_809B5A8)
DEFINE_ACTIVATION_COMMAND_TRANSITION(sub_809BA44, sub_809B89C)
