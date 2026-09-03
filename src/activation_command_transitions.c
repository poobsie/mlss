#include "global.h"
#include "audio/sound_effects.h"
#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.activation_command_transitions." #name)))
extern void sub_80884AC(void *);
extern void sub_8082E1C(void *, s32, s32, s32);
#define DEFINE_ACTIVATION_COMMAND_TRANSITION(name, next)                 \
    extern void next(void *);                                            \
    SEC(name) void name(void *object)                                    \
    {                                                                    \
        s8 *flags;                                                       \
        sub_80884AC(object);                                             \
        if (FIELD(object, u8, 0x79) & 0x20) {                          \
            sub_8082E1C(object, 1, 0x40C2, 0);                          \
            flags = (s8 *)FIELD(object, void *, 8) + 0x12;             \
            *flags = (*flags & -7) | 2;                                 \
            sound_effect_play(0x15D, SOUND_VOLUME_UNCHANGED);                                \
            FIELD(object, void *, 0x4C) = next;                         \
        }                                                                \
    }
DEFINE_ACTIVATION_COMMAND_TRANSITION(sub_809B504, sub_809B5A8)
DEFINE_ACTIVATION_COMMAND_TRANSITION(sub_809BA44, sub_809B89C)
