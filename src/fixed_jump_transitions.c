#include "global.h"
#include "audio/sound_effects.h"

#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.fixed_jump_transitions." #name)))

extern void sub_8082E1C(void *, s32, s32, s32);

#define DEFINE_FIXED_JUMP(name, next)                                    \
    extern void next(void);                                              \
    SEC(name) void name(void *object)                                    \
    {                                                                    \
        s32 mask;                                                        \
        s32 flag_value;                                                  \
        volatile u8 *flags;                                              \
        sound_effect_play(0x2B, SOUND_VOLUME_UNCHANGED);                                     \
        FIELD(object, s32, 0x94) = -0x48;                               \
        sub_8082E1C(object, 5, 0x204D, 0);                              \
        flags = (u8 *)FIELD(object, void *, 8) + 0x12;                  \
        flag_value = *flags;                                             \
        mask = -7;                                                       \
        flag_value &= mask;                                              \
        flag_value |= 2;                                                 \
        *flags = flag_value;                                             \
        FIELD(object, void *, 0x4C) = next;                             \
    }

DEFINE_FIXED_JUMP(sub_8091CC8, sub_8091E00)
DEFINE_FIXED_JUMP(sub_8092E58, sub_8092F90)
DEFINE_FIXED_JUMP(sub_8094464, sub_8094574)
DEFINE_FIXED_JUMP(sub_80948BC, sub_80949CC)
DEFINE_FIXED_JUMP(sub_8094D14, sub_8094E24)
