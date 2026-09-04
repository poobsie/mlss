#include "global.h"
#include "audio/sound_effects.h"
#include "object/functions.h"

#define SEC(name)   __attribute__((section(".text.middle." #name)))
#define U8AT(p, o)  (*(u8*)((u8*)(p) + (o)))
#define U16AT(p, o) (*(u16*)((u8*)(p) + (o)))
#define U32AT(p, o) (*(u32*)((u8*)(p) + (o)))
#define PTRAT(p, o) (*(void**)((u8*)(p) + (o)))

void sub_807C298(void);
void sub_8087540(void*);
int sub_8082B00(void*);
void sub_80873B8(void*, int, int);
void sub_8082E1C(void*, s32, s32, s32);

#define DECL_NEXT(name) extern void name(void*)
DECL_NEXT(sub_80D9B9C);
DECL_NEXT(sub_80D9BE0);
DECL_NEXT(sub_80D9D5C);
DECL_NEXT(sub_80DA264);
DECL_NEXT(sub_80DA368);
DECL_NEXT(sub_80DA3FC);
DECL_NEXT(sub_80DAB64);
DECL_NEXT(sub_80DABD0);
DECL_NEXT(sub_80DB1E4);
DECL_NEXT(sub_80DBD88);
DECL_NEXT(sub_80DBDE8);
DECL_NEXT(sub_808750C);
DECL_NEXT(sub_80DC4F4);
DECL_NEXT(sub_80DC554);
DECL_NEXT(sub_80DD740);
DECL_NEXT(sub_80DD76C);
DECL_NEXT(sub_80DD798);
DECL_NEXT(sub_80DD7C4);
DECL_NEXT(sub_80DE670);
DECL_NEXT(sub_80DDAE4);
DECL_NEXT(sub_80D9C24);
DECL_NEXT(sub_80D9C6C);
DECL_NEXT(sub_80D9CB4);
DECL_NEXT(sub_80D9D08);
DECL_NEXT(sub_80D95A4);
DECL_NEXT(sub_80D90DC);
DECL_NEXT(sub_80D9F50);
DECL_NEXT(sub_80D9FB0);
DECL_NEXT(sub_80DA024);
DECL_NEXT(sub_80DA0E0);
DECL_NEXT(sub_80DA1EC);
DECL_NEXT(sub_80DA208);
DECL_NEXT(sub_80DA2C4);
DECL_NEXT(sub_80DA39C);
DECL_NEXT(sub_80DA098);
void sub_807F47C(void*);

#define OWNER_VARIANT(object) \
    (*(s16*)((u8*)PTRAT(PTRAT((object), 0x2C), 0x28) + 0xEC))
#define SET_VISUAL_MODE_2(object) do {                                  \
    u8* visual = PTRAT((object), 8);                                    \
    u8 flags = U8AT(visual, 0x12);                                      \
    s32 mask = 7;                                                       \
    mask = -mask;                                                       \
    mask &= flags;                                                      \
    mask |= 2;                                                          \
    U8AT(visual, 0x12) = mask;                                          \
} while (0)

#define DEFINE_VARIANT_SETUP(symbol, next)                               \
    SEC(symbol) void symbol(void* object)                                \
    {                                                                    \
        s32 variant = OWNER_VARIANT(object);                             \
        s32 animation;                                                    \
        if (variant == -1)                                               \
            animation = 2;                                                \
        else                                                              \
            animation = 6;                                                \
        sub_8082E1C(object, animation, 0, 0);                             \
        SET_VISUAL_MODE_2(object);                                        \
        PTRAT(object, 0x4C) = next;                                       \
    }

DEFINE_VARIANT_SETUP(sub_80D9B9C, sub_80D9C24)
DEFINE_VARIANT_SETUP(sub_80D9BE0, sub_80D9C6C)

#define DEFINE_VISUAL_ADVANCE(symbol, next)                              \
    SEC(symbol) void symbol(void* object)                                \
    {                                                                    \
        s32 variant;                                                     \
        s32 animation;                                                    \
        if (!(U8AT(PTRAT(object, 8), 0x12) & 8))                         \
            return;                                                      \
        variant = OWNER_VARIANT(object);                                 \
        if (variant == -1)                                               \
            animation = 3;                                                \
        else                                                              \
            animation = 7;                                                \
        sub_8082E1C(object, animation, 0, 0);                             \
        U16AT(object, 0xAC) = 0x18;                                       \
        PTRAT(object, 0x4C) = next;                                       \
    }

DEFINE_VISUAL_ADVANCE(sub_80D9C24, sub_80D9CB4)
DEFINE_VISUAL_ADVANCE(sub_80D9C6C, sub_80D9D08)

#define DEFINE_DELAYED_VARIANT_RETURN(symbol, next)                      \
    SEC(symbol) void symbol(void* object)                                \
    {                                                                    \
        s32 variant;                                                     \
        s32 animation;                                                    \
        (*(s16*)((u8*)object + 0xAC))--;                                  \
        if (*(s16*)((u8*)object + 0xAC) >= 0)                            \
            return;                                                      \
        variant = OWNER_VARIANT(object);                                 \
        if (variant == -1)                                               \
            animation = 4;                                                \
        else                                                              \
            animation = 8;                                                \
        sub_8082E1C(object, animation, 0, 0);                             \
        SET_VISUAL_MODE_2(object);                                        \
        PTRAT(object, 0x4C) = next;                                       \
    }

DEFINE_DELAYED_VARIANT_RETURN(sub_80D9CB4, sub_80D95A4)
DEFINE_DELAYED_VARIANT_RETURN(sub_80D9D08, sub_80D90DC)

SEC(sub_80D9E9C) void sub_80D9E9C(void* object)
{
    (*(s16*)((u8*)object + 0xAC))--;
    if (*(s16*)((u8*)object + 0xAC) < 0)
        PTRAT(object, 0x4C) = sub_80D9F50;
}

#define DEFINE_SOUND_38_TRANSITION(symbol, clearTimer, next)             \
    SEC(symbol) void symbol(void* object)                                \
    {                                                                    \
        if (clearTimer)                                                   \
            U16AT(object, 0xAC) = 0;                                      \
        sub_8082E1C(object, 2, 0, 0);                                    \
        sound_effect_play(0x38, SOUND_VOLUME_UNCHANGED);                  \
        SET_VISUAL_MODE_2(object);                                        \
        PTRAT(object, 0x4C) = next;                                       \
    }

DEFINE_SOUND_38_TRANSITION(sub_80D9EBC, 0, sub_80D9FB0)
DEFINE_SOUND_38_TRANSITION(sub_80D9EF4, 1, sub_80DA024)

SEC(sub_80D9F34) void sub_80D9F34(void* object)
{
    if (*(s16*)((u8*)PTRAT(object, 0x28) + 0xF6) != 0)
        PTRAT(object, 0x4C) = sub_80DA0E0;
}

#define DEFINE_VALUE80_CLEAR_ADVANCE(symbol, delay, next)               \
    SEC(symbol) void symbol(void* object)                                \
    {                                                                    \
        if (U32AT(object, 0x80) != 0)                                    \
            return;                                                      \
        sub_8082E1C(object, 3, 0, 0);                                    \
        SET_VISUAL_MODE_2(object);                                        \
        U16AT(object, 0xAC) = delay;                                      \
        PTRAT(object, 0x4C) = next;                                       \
    }

DEFINE_VALUE80_CLEAR_ADVANCE(sub_80DA100, 8, sub_80DA1EC)
DEFINE_VALUE80_CLEAR_ADVANCE(sub_80DA140, 0x20, sub_80DA208)

SEC(sub_80DA224) void sub_80DA224(void* object)
{
    if (U32AT(object, 0x80) != 0)
        return;
    sound_effect_play(0xAF, SOUND_VOLUME_UNCHANGED);
    sub_8082E1C(object, 3, 0, 0);
    SET_VISUAL_MODE_2(object);
    PTRAT(object, 0x4C) = sub_80DA2C4;
}

SEC(sub_80DA368) void sub_80DA368(void* object)
{
    s16* timer = (s16*)((u8*)object + 0xAC);
    (*timer)--;
    if (*timer < 0) {
        sub_8082E1C(object, 6, 0, 0);
        *timer = 0;
        PTRAT(object, 0x4C) = sub_80DA39C;
    }
}

SEC(sub_80DA480) void sub_80DA480(void* object)
{
    s16* timer = (s16*)((u8*)object + 0xAC);
    (*timer)--;
    if (*timer < 0) {
        sub_807F47C(object);
        sub_8082E1C(object, 6, 0, 0);
        *timer = 8;
        PTRAT(object, 0x4C) = sub_80DA098;
    }
}

#define DEFINE_CALL_VOID(symbol, name, callee)                          \
    SEC(symbol) void name(void) { callee(); }                           \
    SEC(symbol) const u16 symbol##_padding = 0;

DEFINE_CALL_VOID(sub_80D2D28, object_invoke_shared_terminal_action_a, sub_807C298)
DEFINE_CALL_VOID(sub_80DEC60, object_invoke_shared_terminal_action_b, sub_807C298)

#define DEFINE_CHECK_UPDATE(symbol, name)                               \
    SEC(symbol) void name(void* object) {                               \
        if (U8AT(PTRAT(object, 8), 0x12) & 8)                           \
            sub_8087540(object);                                        \
    }                                                                   \
    SEC(symbol) const u16 symbol##_padding = 0;

DEFINE_CHECK_UPDATE(sub_80D9984, object_finish_when_visual_complete_a)
DEFINE_CHECK_UPDATE(sub_80D99D4, object_finish_when_visual_complete_b)
DEFINE_CHECK_UPDATE(sub_80DA9E0, object_finish_when_visual_complete_c)
DEFINE_CHECK_UPDATE(sub_80DA9FC, object_finish_when_visual_complete_d)

#define DEFINE_SET_NEXT_IF_DONE(symbol, name, next)                     \
    SEC(symbol) void name(void* object) {                               \
        if (sub_8082B00(object) == 0)                                   \
            PTRAT(object, 0x4C) = (void*)(next);                        \
    }

DEFINE_SET_NEXT_IF_DONE(sub_80D9A7C, object_advance_when_ready_a, sub_80D9B9C)
DEFINE_SET_NEXT_IF_DONE(sub_80D9B08, object_advance_when_ready_b, sub_80D9BE0)
DEFINE_SET_NEXT_IF_DONE(sub_80DB844, object_advance_when_ready_c, sub_80DB1E4)
DEFINE_SET_NEXT_IF_DONE(sub_80DBD50, object_advance_when_ready_d, sub_80DBD88)
DEFINE_SET_NEXT_IF_DONE(sub_80DBD6C, object_advance_when_ready_e, sub_80DBDE8)
DEFINE_SET_NEXT_IF_DONE(sub_80DC4A4, object_advance_when_ready_f, sub_80DC4F4)
DEFINE_SET_NEXT_IF_DONE(sub_80DC4D8, object_advance_when_ready_g, sub_80DC554)
DEFINE_SET_NEXT_IF_DONE(sub_80DD6D0, object_advance_when_ready_h, sub_80DD740)
DEFINE_SET_NEXT_IF_DONE(sub_80DD6EC, object_advance_when_ready_i, sub_80DD76C)
DEFINE_SET_NEXT_IF_DONE(sub_80DD708, object_advance_when_ready_j, sub_80DD798)
DEFINE_SET_NEXT_IF_DONE(sub_80DD724, object_advance_when_ready_k, sub_80DD7C4)
DEFINE_SET_NEXT_IF_DONE(sub_80DEC44, object_advance_when_ready_l, sub_80DE670)
DEFINE_SET_NEXT_IF_DONE(sub_80DED30, object_advance_when_ready_m, sub_80DDAE4)

#define DEFINE_FLAG_NEXT(symbol, name, next)                            \
    SEC(symbol) void name(void* object) {                               \
        if (U8AT(PTRAT(object, 8), 0x12) & 8)                           \
            PTRAT(object, 0x4C) = (void*)(next);                        \
    }

DEFINE_FLAG_NEXT(sub_80DA1EC, object_advance_when_visual_complete_a, sub_80D9D5C)
DEFINE_FLAG_NEXT(sub_80DA208, object_advance_when_visual_complete_b, sub_80DA264)
DEFINE_FLAG_NEXT(sub_80DA324, object_advance_when_visual_complete_c, sub_80DA368)
DEFINE_FLAG_NEXT(sub_80DA3E0, object_advance_when_visual_complete_d, sub_80DA3FC)

#define DEFINE_INIT_NEXT(symbol, name, argument, next)                  \
    SEC(symbol) void name(void* object) {                               \
        U16AT(object, 0xAC) = 0x30;                                     \
        sub_80873B8(object, argument, 0x1B);                            \
        PTRAT(object, 0x50) = (void*)(next);                            \
    }

DEFINE_INIT_NEXT(sub_80DAAA4, object_initialize_followup_with_argument_4, 4, sub_80DAB64)
DEFINE_INIT_NEXT(sub_80DAAC8, object_initialize_followup_with_argument_2, 2, sub_80DABD0)

#define DEFINE_SET_IDLE_IF_EMPTY(symbol, name)                          \
    SEC(symbol) void name(void* object) {                               \
        if (U32AT(object, 0x80) == 0)                                   \
            PTRAT(object, 0x4C) = (void*)sub_808750C;                   \
    }

DEFINE_SET_IDLE_IF_EMPTY(sub_80DC3A0, object_return_to_idle_when_value80_clear_a)
DEFINE_SET_IDLE_IF_EMPTY(sub_80DE948, object_return_to_idle_when_value80_clear_b)
