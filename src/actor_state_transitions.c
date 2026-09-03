#include "global.h"

#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.actor_state_transitions." #name)))

typedef s32 (*SoundFunction)(s32, s32);

extern int loc_8198220();
extern int loc_819832C();

#define DEFINE_ACTOR_STATE(name, primary, secondary, next)                \
    extern void next(void);                                               \
    SEC(name) void name(void *object)                                     \
    {                                                                     \
        s32 inactive;                                                     \
        s32 mask;                                                         \
        s32 flag_value;                                                   \
        s32 state;                                                        \
        void *global = *(void **)0x03000FD8;                              \
        void *actor = FIELD(global, void *, primary);                     \
        volatile u8 *flags;                                               \
        inactive = FIELD(FIELD(global, void *, secondary), s32, 0x54);   \
        if (inactive == 0) {                                              \
            state = FIELD(actor, u8, 0x7E) & 6;                           \
            if (state == 2 || state == 4) {                              \
                FIELD(actor, s16, 0x82) =                                \
                    ((SoundFunction)(*(u32 *)0x03001038                   \
                        + ((u32)loc_819832C - (u32)loc_8198220)))(0x4000, 16); \
                FIELD(actor, s16, 0x86) = inactive;                      \
                flags = (u8 *)actor + 0x81;                              \
                flag_value = *flags;                                     \
                mask = -0x21;                                           \
                flag_value &= mask;                                      \
                *flags = flag_value;                                     \
            }                                                             \
            FIELD(object, void *, 0x4C) = next;                          \
        }                                                                 \
    }

DEFINE_ACTOR_STATE(sub_80A6F78, 0x70, 0x74, sub_80A6FEC)
DEFINE_ACTOR_STATE(sub_80AC950, 0x70, 0x74, sub_80AC9C4)
DEFINE_ACTOR_STATE(sub_80B992C, 0x70, 0x74, sub_80C0BE4)
DEFINE_ACTOR_STATE(sub_80CD18C, 0x70, 0x74, sub_80CD200)
