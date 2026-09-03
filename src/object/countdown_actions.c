#include "global.h"
#include "audio/sound_effects.h"
#include "object/runtime_object.h"
#define SEC(name) __attribute__((section(".text.countdown_actions." #name)))
extern void sub_8082E1C(struct RuntimeObject*, s32, s32, s32);
extern void sub_808750C(struct RuntimeObject*);
extern void sub_807B7A8(struct RuntimeObjectState*);
extern void sub_807FE40(struct RuntimeObjectState*);
#define DEFINE_COUNTDOWN_CHILD_ACTION(name)                              \
    SEC(name) void name(struct RuntimeObject* object)                    \
    {                                                                    \
        if (--object->timer <= 0) {                                     \
            sub_807B7A8(object->state);                                 \
            sub_807FE40(object->state);                                 \
        }                                                                \
    }                                                                    \
    SEC(name) const u16 name##_padding = 0;
#define DEFINE_COUNTDOWN_COMMAND_ACTION(name)                            \
    SEC(name) void name(struct RuntimeObject* object)                    \
    {                                                                    \
        if (--object->timer <= 0) {                                     \
            sound_effect_stop(0xD2);                                     \
            sub_8082E1C(object, 6, 0, 0);                               \
            object->update = sub_808750C;                               \
        }                                                                \
    }
DEFINE_COUNTDOWN_COMMAND_ACTION(sub_806D35C)
DEFINE_COUNTDOWN_COMMAND_ACTION(sub_806D390)
DEFINE_COUNTDOWN_CHILD_ACTION(sub_8069394)
DEFINE_COUNTDOWN_CHILD_ACTION(sub_80712B0)
