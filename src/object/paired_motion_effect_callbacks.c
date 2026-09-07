#include "object/paired_motion_effect_callbacks.h"

#define SEC(symbol) \
    __attribute__((section(".text.paired_motion_effect_callbacks." #symbol)))
#define RUNTIME_SCALE_BASE (*(u8**)0x03001038)

typedef s32 (*RuntimeScaleFunction)(s32 scale, s32 distance);

extern u8 loc_8198220[];
extern u8 loc_819832C[];

void sub_8082E1C(
    struct RuntimeObject* object, s32 animation, s32 command, s32 argument);
void sub_810DD7C(
    struct RuntimeObject* object, struct RuntimeObject* owner, s32 value);

void sub_809B504(struct RuntimeObject* object);
void sub_809B738(struct RuntimeObject* object);
void sub_809B754(struct RuntimeObject* object);
void sub_809BA44(struct RuntimeObject* object);

#define DEFINE_FIXED_HEIGHT_MOTION(symbol, name, distance, next)           \
    SEC(symbol)                                                           \
    void name(struct RuntimeObject* object)                               \
    {                                                                    \
        RuntimeScaleFunction scale;                                      \
        s8* flags;                                                       \
                                                                         \
        object->currentPositionY += 0x100;                               \
        object->verticalPosition = 0x2600;                               \
        if (object->state->valueF6 != 0) {                  \
            scale = (RuntimeScaleFunction)(                              \
                RUNTIME_SCALE_BASE + (loc_819832C - loc_8198220));       \
            object->unknown7A = scale(0x4000, distance);                 \
            *(u16*)&object->unknown7E[0] = 0;                            \
            flags = (s8*)&object->flags79;                              \
            *flags &= -0x21;                                            \
        }                                                               \
        object->update = next;                                          \
    }

DEFINE_FIXED_HEIGHT_MOTION(
    sub_809B370, object_begin_fixed_height_motion_step_24, 0x18,
    sub_809B504)
DEFINE_FIXED_HEIGHT_MOTION(
    sub_809B960, object_begin_fixed_height_motion_step_40, 0x28,
    sub_809BA44)

#define DEFINE_ATTACH_OWNER_TRANSITION(symbol, name, next)               \
    SEC(symbol)                                                          \
    void name(struct RuntimeObject* object)                              \
    {                                                                   \
        struct RuntimeObject* owner = object->positionOwner;            \
        s8* flags;                                                      \
                                                                        \
        if (owner->positionZBase == 0 && (owner->flags76 & 0x3E) == 2)  \
            sub_810DD7C(object, owner, 0xFF);                            \
        if (object->visual->flags & 8) {                                \
            sub_8082E1C(object, 3, 0x40C2, 0);                          \
            flags = (s8*)&object->visual->flags;                        \
            *flags = (*flags & -7) | 2;                                \
            object->update = next;                                     \
        }                                                              \
    }

DEFINE_ATTACH_OWNER_TRANSITION(
    sub_809B678, object_attach_owner_then_start_animation_3_a, sub_809B738)
DEFINE_ATTACH_OWNER_TRANSITION(
    sub_809B6D8, object_attach_owner_then_start_animation_3_b, sub_809B754)
