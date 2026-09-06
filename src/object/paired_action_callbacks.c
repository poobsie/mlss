#include "audio/sound_effects.h"
#include "field/global_object_transitions.h"
#include "object/paired_action_callbacks.h"

#define SEC(symbol) \
    __attribute__((section(".text.paired_action_callbacks." #symbol)))
#define FIELD_OBJECT_RUNTIME (*(struct FieldObjectRuntime**)0x03000FD8)
#define RUNTIME_SCALE_BASE (*(u8**)0x03001038)
#define PRIMARY_ACTION_OWNER (FIELD_OBJECT_RUNTIME->primaryActionOwner)
#define SECONDARY_ACTION_OWNER (FIELD_OBJECT_RUNTIME->secondaryActionOwner)

typedef s32 (*RuntimeScaleFunction)(s32 scale, s32 distance);

extern u8 loc_8198220[];
extern u8 loc_819832C[];

void sub_80A339C(struct RuntimeObject* object);
void sub_80A3E68(struct RuntimeObject* object);
void sub_80A4288(struct RuntimeObject* object);
void sub_80A5428(struct RuntimeObject* object);
void sub_80A5808(struct RuntimeObject* object);
void sub_8082E1C(
    struct RuntimeObject* object, s32 animation, s32 command, s32 argument);
void sub_8087CE4(struct RuntimeObject* object);
void sub_80A6F78(struct RuntimeObject* object);
void sub_80AC950(struct RuntimeObject* object);
void sub_80B1508(struct RuntimeObject* object);
void sub_80B35C8(struct RuntimeObject* object);
void sub_80B95D8(struct RuntimeObject* object);
void sub_80B9624(struct RuntimeObject* object);

#define DEFINE_ACTION_POLL(symbol, name, owner, distance, next)          \
    SEC(symbol)                                                          \
    void name(struct RuntimeObject* caller)                              \
    {                                                                    \
        struct RuntimeObject* action = &(owner)->object;                 \
        RuntimeScaleFunction scale;                                     \
        s8* flags;                                                       \
                                                                         \
        if (action->visual->flags & 8) {                                \
            if ((action->flags76 & 6) == 2 ||                           \
                (action->flags76 & 6) == 4) {                           \
                scale = (RuntimeScaleFunction)(                         \
                    RUNTIME_SCALE_BASE + (loc_819832C - loc_8198220));  \
                action->unknown7A = scale(0x4000, distance);             \
                *(u16*)action->unknown7E = 0;                           \
                flags = (s8*)&action->flags79;                          \
                *flags &= -0x21;                                       \
            }                                                            \
            caller->update = next;                                      \
        }                                                                \
    }

DEFINE_ACTION_POLL(sub_80A3324, object_poll_primary_action_distance_15_a,
    PRIMARY_ACTION_OWNER, 15, sub_80A339C)
DEFINE_ACTION_POLL(sub_80A3DF0, object_poll_secondary_action_distance_4,
    SECONDARY_ACTION_OWNER, 4, sub_80A3E68)
DEFINE_ACTION_POLL(sub_80A4210, object_poll_secondary_action_distance_15_a,
    SECONDARY_ACTION_OWNER, 15, sub_80A4288)
DEFINE_ACTION_POLL(sub_80A53B0, object_poll_primary_action_distance_15_b,
    PRIMARY_ACTION_OWNER, 15, sub_80A5428)
DEFINE_ACTION_POLL(sub_80A5790, object_poll_primary_action_distance_18,
    PRIMARY_ACTION_OWNER, 18, sub_80A5808)

#define DEFINE_CLEAR_ACTION_THEN_CONTINUE(symbol, name, owner, next)     \
    SEC(symbol)                                                          \
    void name(struct RuntimeObject* caller)                              \
    {                                                                    \
        struct RuntimeObject* action = &(owner)->object;                 \
        s8* flags;                                                       \
                                                                         \
        sub_8087CE4(action);                                             \
        if (action->flags79 & 0x20) {                                   \
            if ((action->flags76 & 6) == 2 ||                           \
                (action->flags76 & 6) == 4) {                           \
                sub_8082E1C(action, 0, -1, 0);                          \
                flags = (s8*)&action->visual->flags11;                  \
                *flags &= -0x41;                                       \
                flags = (s8*)&action->visual->flags;                    \
                *flags &= -7;                                          \
            }                                                            \
            caller->update = next;                                      \
        }                                                                \
    }

DEFINE_CLEAR_ACTION_THEN_CONTINUE(sub_80AC5A4,
    object_clear_primary_action_then_continue_a, PRIMARY_ACTION_OWNER,
    sub_80A6F78)
DEFINE_CLEAR_ACTION_THEN_CONTINUE(sub_80B31F0,
    object_clear_primary_action_then_continue_b, PRIMARY_ACTION_OWNER,
    sub_80AC950)
DEFINE_CLEAR_ACTION_THEN_CONTINUE(sub_80B956C,
    object_clear_secondary_action_then_continue, SECONDARY_ACTION_OWNER,
    sub_80B35C8)

#define DEFINE_ACTION_SOUND_HANDOFF(                                    \
        symbol, name, owner, animation, command, next)                  \
    SEC(symbol)                                                          \
    void name(struct RuntimeObject* caller)                              \
    {                                                                    \
        struct RuntimeObject* action = &(owner)->object;                 \
        s8* flags;                                                       \
                                                                         \
        sub_8087CE4(action);                                             \
        if (action->flags79 & 0x20) {                                   \
            sound_effect_play(0x2E, -1);                               \
            if ((action->flags76 & 6) == 2 ||                           \
                (action->flags76 & 6) == 4) {                           \
                sub_8082E1C(action, animation, command, 0);             \
                flags = (s8*)&action->visual->flags;                    \
                *flags = (*flags & -7) | 2;                            \
            }                                                            \
            caller->update = next;                                      \
        }                                                                \
    }

DEFINE_ACTION_SOUND_HANDOFF(sub_80B93B0,
    object_primary_action_sound_2e_animation_13, PRIMARY_ACTION_OWNER,
    13, 0x2000, sub_80B95D8)
DEFINE_ACTION_SOUND_HANDOFF(sub_80B9420,
    object_secondary_action_sound_2e_animation_8, SECONDARY_ACTION_OWNER,
    8, 0x204D, sub_80B9624)

#define DEFINE_STOP_ACTION_WHEN_READY(symbol, name, owner)              \
    SEC(symbol)                                                          \
    void name(struct RuntimeObject* unused)                              \
    {                                                                    \
        struct RuntimeObject* action = &(owner)->object;                 \
        s8* flags;                                                       \
                                                                         \
        if (action->visual->flags & 8) {                                \
            sub_8082E1C(action, 0, -1, 0);                              \
            flags = (s8*)&action->visual->flags11;                      \
            *flags &= -0x41;                                           \
            flags = (s8*)&action->visual->flags;                        \
            *flags &= -7;                                              \
            action->update = 0;                                         \
        }                                                                \
    }

DEFINE_STOP_ACTION_WHEN_READY(sub_80B95D8,
    object_stop_primary_action_when_visual_ready, PRIMARY_ACTION_OWNER)
DEFINE_STOP_ACTION_WHEN_READY(sub_80B9624,
    object_stop_secondary_action_when_visual_ready, SECONDARY_ACTION_OWNER)
