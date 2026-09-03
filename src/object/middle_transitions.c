#include "global.h"
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
