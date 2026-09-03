#include "global.h"
#include "audio/sound_effects.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.jump_setups_alternate." #name)))

typedef s32 (*RandomFunction)(s32);
extern void sub_8082E1C(struct RuntimeObject*, s32, s32, s32);

#define DEFINE_JUMP_SETUP_ALT(name, random_arg, shift, next)             \
    extern void next(struct RuntimeObject*);                             \
    SEC(name) void name(struct RuntimeObject* object)                    \
    {                                                                    \
        s32 value;                                                       \
        s32 mask;                                                        \
        s32 flag_value;                                                  \
        volatile u8 *flags;                                              \
        RandomFunction random;                                          \
        sound_effect_play(0x2B, SOUND_VOLUME_UNCHANGED);                                     \
        random = *(RandomFunction *)0x03001038;                          \
        value = random(random_arg);                                      \
        value = (value - shift) / 2;                                    \
        object->verticalVelocity = value;                               \
        object->verticalAcceleration = -shift;                          \
        sub_8082E1C(object, 5, 0x2000, 0);                              \
        flags = &object->visual->flags;                                 \
        flag_value = *flags;                                             \
        mask = -7;                                                       \
        flag_value &= mask;                                              \
        flag_value |= 2;                                                 \
        *flags = flag_value;                                             \
        object->update = next;                                          \
    }

DEFINE_JUMP_SETUP_ALT(sub_808EEB8, 0x00DC7900, 0xB0, sub_808EF8C)
DEFINE_JUMP_SETUP_ALT(sub_808FEB4, 0x00318790, 0x2C, sub_808FF88)
DEFINE_JUMP_SETUP_ALT(sub_80904C4, 0x004D1E40, 0x58, sub_8090598)
DEFINE_JUMP_SETUP_ALT(sub_8090830, 0x00A50A10, 0xBC, sub_8090904)
DEFINE_JUMP_SETUP_ALT(sub_8090C2C, 0x002928A1, 0x2F, sub_8090D00)
