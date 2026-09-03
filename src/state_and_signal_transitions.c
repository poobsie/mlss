#include "global.h"
#include "audio/sound_effects.h"
#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.state_and_signal_transitions." #name)))
extern s32 sub_8086D80(void *);
extern s32 sub_80871A8(void *);
extern void sub_8082E1C(void *, s32, s32, s32);
extern void sub_8089EC4(void *);
#define DEFINE_STATE_RESET(name, update)                                  \
    SEC(name) s32 name(void *object)                                     \
    {                                                                    \
        s32 result = update(object);                                     \
        if (result == 0) {                                               \
            FIELD(object, void *, 0x4C) = sub_8089EC4;                  \
            FIELD(object, s16, 0xAE) /= 2;                              \
            FIELD(object, u16, 0xB0) = result;                          \
            FIELD(object, u16, 0xB2) = result;                          \
            sub_8082E1C(object, 1, 0, 0);                               \
        }                                                                \
        return result;                                                   \
    }
DEFINE_STATE_RESET(sub_8089B4C, sub_8086D80)
DEFINE_STATE_RESET(sub_8089B90, sub_80871A8)

#define DEFINE_SIGNAL_TRANSITION(name, command, next)                    \
    extern void next(void *);                                            \
    SEC(name) void name(void *object)                                    \
    {                                                                    \
        s16 *timer = (s16 *)((u8 *)object + 0xAE);                      \
        if (--*timer <= 0) {                                             \
            sound_effect_play(0x54, SOUND_VOLUME_UNCHANGED);                                 \
            *timer = 10;                                                 \
        }                                                                \
        if (FIELD(FIELD(object, void *, 8), u8, 0x12) & 8) {           \
            sub_8082E1C(object, command, 0, 0);                          \
            FIELD(object, void *, 0x4C) = next;                         \
        }                                                                \
    }
DEFINE_SIGNAL_TRANSITION(sub_807972C, 13, sub_8079A90)
DEFINE_SIGNAL_TRANSITION(sub_8079A90, 0, sub_8077ECC)
