#include "global.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.landing_transitions." #name)))

extern void sub_8082E1C(struct RuntimeObject*, s32, s32, s32);

#define DEFINE_LANDING_TRANSITION(name, next)                            \
    extern void next(struct RuntimeObject*);                             \
    SEC(name) void name(struct RuntimeObject* object)                    \
    {                                                                    \
        s16 *velocity = &object->verticalVelocity;                       \
        u16 current;                                                     \
        s32 step;                                                        \
        s32 position;                                                    \
        s32 floor;                                                       \
        volatile u8 *flags;                                              \
        s32 flag_value;                                                  \
        s32 mask;                                                        \
        step = object->verticalAcceleration;                            \
        current = *velocity;                                             \
        current += step;                                                 \
        *velocity = current;                                             \
        position = object->positionZBase + *velocity;                   \
        object->verticalPosition = position;                            \
        floor = object->state->floorHeight;                             \
        if (position <= floor) {                                         \
            flags = &object->flags77;                                   \
            flag_value = *flags;                                        \
            mask = -8;                                                   \
            flag_value &= mask;                                         \
            *flags = flag_value;                                        \
            object->verticalPosition = object->state->floorHeight;      \
            sub_8082E1C(object, 8, 0x204D, 0);                          \
            object->update = next;                                      \
        }                                                                \
    }

DEFINE_LANDING_TRANSITION(sub_808EFFC, sub_808F0AC)
DEFINE_LANDING_TRANSITION(sub_808FFF8, sub_80900A8)
DEFINE_LANDING_TRANSITION(sub_8090608, sub_80906B8)
DEFINE_LANDING_TRANSITION(sub_8090974, sub_8090A24)
DEFINE_LANDING_TRANSITION(sub_8090D70, sub_8090E20)
