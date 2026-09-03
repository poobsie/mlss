#include "global.h"
#include "audio/sound_effects.h"
#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.command_effect_transitions." #name)))
extern void sub_8082E1C(void *, s32, s32, s32);
extern void sub_80DF024(s32, s32, s32, s32, void *);
#define DEFINE_COMMAND_EFFECT_TRANSITION(name, command, effect, next)     \
    extern void next(void *);                                            \
    SEC(name) void name(void *object)                                    \
    {                                                                    \
        if (FIELD(FIELD(object, void *, 8), u8, 0x12) & 8) {           \
            sub_8082E1C(object, command, 0, 0);                          \
            sub_80DF024(effect, FIELD(object, s32, 0x38) / 0x100,      \
                FIELD(object, s32, 0x3C) / 0x100,                       \
                FIELD(object, s32, 0x40) / 0x100, object);              \
            sound_effect_play(0x10C, SOUND_VOLUME_UNCHANGED);                                \
            FIELD(object, void *, 0x4C) = next;                         \
        }                                                                \
    }
DEFINE_COMMAND_EFFECT_TRANSITION(sub_8098CBC, 0x13, 0x2841, sub_8098954)
DEFINE_COMMAND_EFFECT_TRANSITION(sub_8099050, 0x10, 0x2829, sub_8098D20)
DEFINE_COMMAND_EFFECT_TRANSITION(sub_80993E4, 0x0D, 0x2811, sub_80990B4)
