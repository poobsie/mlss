#include "global.h"
#include "audio/sound_effects.h"

#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.jump_setups." #name)))

typedef s32 (*RandomFunction)(s32);
extern void sub_8082E1C(void *, s32, s32, s32);

#define DEFINE_JUMP_SETUP(name, random_arg, shift, next)                 \
    extern void next(void);                                              \
    SEC(name) void name(void *object)                                    \
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
        FIELD(object, u16, 0xB2) = value;                               \
        FIELD(object, s32, 0x94) = -shift;                              \
        sub_8082E1C(object, 5, 0x204D, 0);                              \
        flags = (u8 *)FIELD(object, void *, 8) + 0x12;                  \
        flag_value = *flags;                                             \
        mask = -7;                                                       \
        flag_value &= mask;                                              \
        flag_value |= 2;                                                 \
        *flags = flag_value;                                             \
        FIELD(object, void *, 0x4C) = next;                             \
    }

DEFINE_JUMP_SETUP(sub_808DE44, 0x005A1440, 0x48, sub_808DEEC)
DEFINE_JUMP_SETUP(sub_808EE54, 0x00B45100, 0x90, sub_808EF1C)
DEFINE_JUMP_SETUP(sub_808FE50, 0x002E4559, 0x25, sub_808FF18)
DEFINE_JUMP_SETUP(sub_8090460, 0x003F1440, 0x48, sub_8090528)
DEFINE_JUMP_SETUP(sub_80907CC, 0x0096F390, 0xAC, sub_8090894)
DEFINE_JUMP_SETUP(sub_8090BC8, 0x0025A739, 0x2B, sub_8090C90)
