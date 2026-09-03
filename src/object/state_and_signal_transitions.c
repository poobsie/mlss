#include "global.h"
#include "audio/sound_effects.h"
#include "object/runtime_object.h"
#define SEC(name) __attribute__((section(".text.state_and_signal_transitions." #name)))
extern s32 sub_8086D80(struct RuntimeObject*);
extern s32 sub_80871A8(struct RuntimeObject*);
extern void sub_8082E1C(struct RuntimeObject*, s32, s32, s32);
extern void sub_8089EC4(struct RuntimeObject*);
#define DEFINE_STATE_RESET(name, poll)                                    \
    SEC(name) s32 name(struct RuntimeObject* object)                     \
    {                                                                    \
        s32 result = poll(object);                                       \
        if (result == 0) {                                               \
            object->update = sub_8089EC4;                               \
            object->secondaryTimer /= 2;                                \
            object->stateValueB0 = result;                              \
            object->verticalVelocity = result;                          \
            sub_8082E1C(object, 1, 0, 0);                               \
        }                                                                \
        return result;                                                   \
    }
DEFINE_STATE_RESET(sub_8089B4C, sub_8086D80)
DEFINE_STATE_RESET(sub_8089B90, sub_80871A8)

#define DEFINE_SIGNAL_TRANSITION(name, command, next)                    \
    extern void next(struct RuntimeObject*);                             \
    SEC(name) void name(struct RuntimeObject* object)                    \
    {                                                                    \
        s16 *timer = &object->secondaryTimer;                            \
        if (--*timer <= 0) {                                             \
            sound_effect_play(0x54, SOUND_VOLUME_UNCHANGED);                                 \
            *timer = 10;                                                 \
        }                                                                \
        if (object->visual->flags & 8) {                                \
            sub_8082E1C(object, command, 0, 0);                          \
            object->update = next;                                      \
        }                                                                \
    }
DEFINE_SIGNAL_TRANSITION(sub_807972C, 13, sub_8079A90)
DEFINE_SIGNAL_TRANSITION(sub_8079A90, 0, sub_8077ECC)
