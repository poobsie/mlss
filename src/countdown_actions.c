#include "global.h"
#include "audio/sound_effects.h"
#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.countdown_actions." #name)))
extern void sub_8082E1C(void *, s32, s32, s32);
extern void sub_808750C(void *);
extern void sub_807B7A8(void *);
extern void sub_807FE40(void *);
#define DEFINE_COUNTDOWN_CHILD_ACTION(name)                              \
    SEC(name) void name(void *object)                                    \
    {                                                                    \
        if (--FIELD(object, s16, 0xAC) <= 0) {                          \
            sub_807B7A8(FIELD(object, void *, 0x28));                   \
            sub_807FE40(FIELD(object, void *, 0x28));                   \
        }                                                                \
    }                                                                    \
    SEC(name) const u16 name##_padding = 0;
#define DEFINE_COUNTDOWN_COMMAND_ACTION(name)                            \
    SEC(name) void name(void *object)                                    \
    {                                                                    \
        if (--FIELD(object, s16, 0xAC) <= 0) {                          \
            sound_effect_stop(0xD2);                                     \
            sub_8082E1C(object, 6, 0, 0);                               \
            FIELD(object, void *, 0x4C) = sub_808750C;                  \
        }                                                                \
    }
DEFINE_COUNTDOWN_COMMAND_ACTION(sub_806D35C)
DEFINE_COUNTDOWN_COMMAND_ACTION(sub_806D390)
DEFINE_COUNTDOWN_CHILD_ACTION(sub_8069394)
DEFINE_COUNTDOWN_CHILD_ACTION(sub_80712B0)
