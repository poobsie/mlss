#include "global.h"

#define SEC(name)   __attribute__((section(".text.middle." #name)))
#define U8AT(p, o)  (*(u8*)((u8*)(p) + (o)))
#define U16AT(p, o) (*(u16*)((u8*)(p) + (o)))
#define U32AT(p, o) (*(u32*)((u8*)(p) + (o)))
#define PTRAT(p, o) (*(void**)((u8*)(p) + (o)))

extern void sub_807C298(void);
extern void sub_8087540(void*);
extern int sub_8082B00(void*);
extern void sub_80873B8(void*, int, int);
extern void sub_8047E50(void*, int);
extern void sub_807C1C8(int, int);
extern void sprite_hide_8021F20(void*);
extern void sprite_show_8020CBC(void*);
extern void process_remove(void*);

#define DECL_NEXT(name) extern void name(void*)
DECL_NEXT(sub_80D9B9C);
DECL_NEXT(sub_80D9BE0);
DECL_NEXT(sub_80DA0E0);
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

#define DEFINE_CALL_VOID(name, callee)                                                                 \
    SEC(name) void name(void) {                                                                        \
        callee();                                                                                      \
    }                                                                                                  \
    SEC(name) const u16 name##_padding = 0;

DEFINE_CALL_VOID(sub_80D2D28, sub_807C298)
DEFINE_CALL_VOID(sub_80DEC60, sub_807C298)

#define DEFINE_CHECK_UPDATE(name)                                                                      \
    SEC(name) void name(void* object) {                                                                \
        if (U8AT(PTRAT(object, 8), 0x12) & 8)                                                          \
            sub_8087540(object);                                                                       \
    }                                                                                                  \
    SEC(name) const u16 name##_padding = 0;

DEFINE_CHECK_UPDATE(sub_80D9984)
DEFINE_CHECK_UPDATE(sub_80D99D4)
DEFINE_CHECK_UPDATE(sub_80DA9E0)
DEFINE_CHECK_UPDATE(sub_80DA9FC)

#define DEFINE_SET_NEXT_IF_DONE(name, next)                                                            \
    SEC(name) void name(void* object) {                                                                \
        if (sub_8082B00(object) == 0)                                                                  \
            PTRAT(object, 0x4C) = (void*)(next);                                                       \
    }

DEFINE_SET_NEXT_IF_DONE(sub_80D9A7C, sub_80D9B9C)
DEFINE_SET_NEXT_IF_DONE(sub_80D9B08, sub_80D9BE0)
DEFINE_SET_NEXT_IF_DONE(sub_80DB844, sub_80DB1E4)
DEFINE_SET_NEXT_IF_DONE(sub_80DBD50, sub_80DBD88)
DEFINE_SET_NEXT_IF_DONE(sub_80DBD6C, sub_80DBDE8)
DEFINE_SET_NEXT_IF_DONE(sub_80DC4A4, sub_80DC4F4)
DEFINE_SET_NEXT_IF_DONE(sub_80DC4D8, sub_80DC554)
DEFINE_SET_NEXT_IF_DONE(sub_80DD6D0, sub_80DD740)
DEFINE_SET_NEXT_IF_DONE(sub_80DD6EC, sub_80DD76C)
DEFINE_SET_NEXT_IF_DONE(sub_80DD708, sub_80DD798)
DEFINE_SET_NEXT_IF_DONE(sub_80DD724, sub_80DD7C4)
DEFINE_SET_NEXT_IF_DONE(sub_80DEC44, sub_80DE670)
DEFINE_SET_NEXT_IF_DONE(sub_80DED30, sub_80DDAE4)

#define DEFINE_FLAG_NEXT(name, next)                                                                   \
    SEC(name) void name(void* object) {                                                                \
        if (U8AT(PTRAT(object, 8), 0x12) & 8)                                                          \
            PTRAT(object, 0x4C) = (void*)(next);                                                       \
    }

DEFINE_FLAG_NEXT(sub_80DA1EC, sub_80D9D5C)
DEFINE_FLAG_NEXT(sub_80DA208, sub_80DA264)
DEFINE_FLAG_NEXT(sub_80DA324, sub_80DA368)
DEFINE_FLAG_NEXT(sub_80DA3E0, sub_80DA3FC)

#define DEFINE_INIT_NEXT(name, arg, next)                                                              \
    SEC(name) void name(void* object) {                                                                \
        U16AT(object, 0xAC) = 0x30;                                                                    \
        sub_80873B8(object, arg, 0x1B);                                                                \
        PTRAT(object, 0x50) = (void*)(next);                                                           \
    }

DEFINE_INIT_NEXT(sub_80DAAA4, 4, sub_80DAB64)
DEFINE_INIT_NEXT(sub_80DAAC8, 2, sub_80DABD0)

#define DEFINE_SET_IDLE_IF_EMPTY(name)                                                                 \
    SEC(name) void name(void* object) {                                                                \
        if (U32AT(object, 0x80) == 0)                                                                  \
            PTRAT(object, 0x4C) = (void*)sub_808750C;                                                  \
    }

DEFINE_SET_IDLE_IF_EMPTY(sub_80DC3A0)
DEFINE_SET_IDLE_IF_EMPTY(sub_80DE948)

SEC(script_cmd_call) int script_cmd_call(void* unused, u8* state, u32* args) {
    if (args[0] == 1)
        U32AT(state, 0x10) = U32AT(state, 0);
    U32AT(state, 0) = args[1];
    return 1;
}
SEC(script_cmd_call) const u16 script_cmd_call_padding = 0;

SEC(script_cmd_end) int script_cmd_end(void* unused, u8* state) {
    U32AT(state, 4) = U32AT(state, 0);
    U32AT(state, 0x10) = 0;
    return 1;
}

SEC(sub_80F1AE4) int sub_80F1AE4(void* a, u32* dest, u32* src) {
    *dest = *src;
    return 1;
}

SEC(sub_80F7E80) int sub_80F7E80(void) {
    return 1;
}
SEC(sub_81218E0) int sub_81218E0(void) {
    return 0;
}
SEC(sub_80E92A8) void* sub_80E92A8(void** p) {
    return *p;
}

SEC(sub_80EA91C) int sub_80EA91C(void* a, u8* state, u32* src) {
    U32AT(state, 0x98) = *src;
    return 1;
}
SEC(sub_80EA91C) const u16 sub_80EA91C_padding = 0;

SEC(sub_8134B64) void sub_8134B64(u16* p) {
    p[0] = 0;
    p[1] = 0;
    p[2] = 0x10;
}

SEC(sub_8136688) void sub_8136688(u32* dest, u32* src) {
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
}
SEC(sub_8136688) const u16 sub_8136688_padding = 0;

SEC(sub_81218C8) void sub_81218C8(u8* p) {
    sprite_hide_8021F20(PTRAT(p, 0x30));
}
SEC(sub_81218D4) void sub_81218D4(u8* p) {
    sprite_show_8020CBC(PTRAT(p, 0x30));
}

SEC(sub_80F14C4) int sub_80F14C4(void* a, void* object, void* c, u16* arg) {
    sub_8047E50(object, *arg);
    return 1;
}

SEC(sub_80F80B4) int sub_80F80B4(void* a, void* b, int* args) {
    sub_807C1C8(args[0], args[1]);
    return 1;
}

SEC(sub_80EA904) int sub_80EA904(void* a, u8* state) {
    u8* count = state + 0xA6;
    --*count;
    U32AT(state, 0x58 + *count * 4) = 0;
    return 1;
}

SEC(sub_80EA928) int sub_80EA928(void* a, u8* state, u32* src) {
    u8* count = state + 0xA6;
    U32AT(state, 0x58 + *count * 4) = *src;
    ++*count;
    return 1;
}

SEC(sub_80EA514) void sub_80EA514(void* a, u8* state, u32 x, u32 y, u16 z, u8 q) {
    U32AT(state, 8) = x;
    U32AT(state, 0xC) = y;
    U16AT(state, 0xA2) = z;
    U8AT(state, 0xA5) = q;
}
SEC(sub_80EA514) const u16 sub_80EA514_padding = 0;

SEC(sub_80EA530) void sub_80EA530(void* a, u8* state, u32 x, u32 y, u16 z, u8 q) {
    U32AT(state, 0) = x;
    U32AT(state, 4) = y;
    U32AT(state, 0x10) = 0;
    U16AT(state, 0xA0) = z;
    U8AT(state, 0xA4) = q;
}
SEC(sub_80EA530) const u16 sub_80EA530_padding = 0;

SEC(sub_8127E38) u32 sub_8127E38(u32 value) {
    return (value - ((*(vu16*)0x02000008 & 0xC) << 12)) << 17 >> 22;
}

SEC(sub_80FAEEC) u8 sub_80FAEEC(u8* p) {
    return U8AT(PTRAT(p, 0x24), 0x9A1);
}

SEC(sub_80FB7E0) void* sub_80FB7E0(u16 index) {
    return ((void**)0x083D7458)[index];
}
SEC(sub_80FB7F0) void* sub_80FB7F0(u16 index) {
    return ((void**)0x0851FA00)[index];
}

SEC(get_field_object_count) u8 get_field_object_count(u16 index, u8* out) {
    u8* p = ((u8**)0x083D6C58)[index];
    *out = p[1] >> 3;
    return *out;
}

SEC(sub_80FB7BC) void* sub_80FB7BC(u16 index, u8* out) {
    u8* p = ((u8**)0x083D6C58)[index];
    *out = p[0] & 0x3F;
    return p - ((p[3] << 8) | p[2]);
}

SEC(sub_8108CBC) void sub_8108CBC(u8* p) {
    U16AT(p, 0x11E) &= 0xFFF;
}

SEC(sub_810D260) void* sub_810D260(u32 value, u8* base) {
    int offset = 0;
    do {
        value >>= 4;
        offset += 4;
    } while (value != 0);
    return base + offset;
}
