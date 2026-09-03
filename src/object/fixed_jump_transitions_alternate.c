#include "global.h"
#include "audio/sound_effects.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.fixed_jump_transitions_alternate." #name)))

extern void sub_8082E1C(struct RuntimeObject*, s32, s32, s32);

#define DEFINE_FIXED_JUMP_ALTERNATE(name, next)                          \
    extern void next(struct RuntimeObject*);                             \
    SEC(name) void name(struct RuntimeObject* object)                    \
    {                                                                    \
        s32 mask;                                                        \
        s32 flag_value;                                                  \
        volatile u8 *flags;                                              \
        sound_effect_play(0x2B, SOUND_VOLUME_UNCHANGED);                                     \
        object->verticalAcceleration = -0x58;                           \
        sub_8082E1C(object, 5, 0x2000, 0);                              \
        flags = &object->visual->flags;                                 \
        flag_value = *flags;                                             \
        mask = -7;                                                       \
        flag_value &= mask;                                              \
        flag_value |= 2;                                                 \
        *flags = flag_value;                                             \
        object->update = next;                                          \
    }

DEFINE_FIXED_JUMP_ALTERNATE(sub_8091D34, sub_8091E70)
DEFINE_FIXED_JUMP_ALTERNATE(sub_8092EC4, sub_8093000)
DEFINE_FIXED_JUMP_ALTERNATE(sub_80944D0, sub_80945E4)
DEFINE_FIXED_JUMP_ALTERNATE(sub_8094928, sub_8094A3C)
DEFINE_FIXED_JUMP_ALTERNATE(sub_8094D80, sub_8094E94)
