#include "global.h"

#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.actor_activation_transitions." #name)))

typedef s32 (*SoundFunction)(s32, s32);

extern int loc_8198220();
extern int loc_819832C();
extern void sub_8087CE4(void *);

#define DEFINE_ACTOR_ACTIVATION_TRANSITION(name, actor_offset, kind, next) \
    extern void next(void);                                               \
    SEC(name) void name(void *object)                                     \
    {                                                                     \
        s32 mask;                                                         \
        s32 flag_value;                                                   \
        s32 state;                                                        \
        s32 result;                                                       \
        s32 zero;                                                         \
        volatile s16 *result_field;                                      \
        volatile s16 *zero_field;                                        \
        void *global = *(void **)0x03000FD8;                              \
        void *actor = FIELD(global, void *, actor_offset);                \
        volatile u8 *flags;                                               \
        sub_8087CE4((u8 *)actor + 8);                                    \
        flags = (u8 *)actor + 0x81;                                      \
        if (*flags & 0x20) {                                              \
            state = FIELD(actor, u8, 0x7E) & 6;                          \
            if (state == 2 || state == 4) {                              \
                result = ((SoundFunction)(*(u32 *)0x03001038             \
                    + ((u32)loc_819832C - (u32)loc_8198220)))(0x4000, kind); \
                result_field = (s16 *)((u8 *)actor + 0x82);             \
                zero = 0;                                                \
                *result_field = result;                                  \
                zero_field = (s16 *)((u8 *)actor + 0x86);               \
                *zero_field = zero;                                      \
                flag_value = *flags;                                     \
                mask = -0x21;                                            \
                flag_value &= mask;                                      \
                *flags = flag_value;                                     \
            }                                                             \
            FIELD(object, void *, 0x4C) = next;                          \
        }                                                                 \
    }

DEFINE_ACTOR_ACTIVATION_TRANSITION(sub_80A0AF4, 0x70, 2, sub_80A0B74)
DEFINE_ACTOR_ACTIVATION_TRANSITION(sub_80A1CC4, 0x74, 2, sub_80A1D44)
DEFINE_ACTOR_ACTIVATION_TRANSITION(sub_80A2E7C, 0x70, 8, sub_80A3B24)
DEFINE_ACTOR_ACTIVATION_TRANSITION(sub_80A3D70, 0x74, 11, sub_80A4A10)
