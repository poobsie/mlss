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
