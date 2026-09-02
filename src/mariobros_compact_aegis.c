#include "global.h"

#define MB_SECTION(name) __attribute__((section(".text.mb_aegis_" #name)))

struct MbObject {
    u8 pad_00[4];
    u8 field_04;
    u8 pad_05;
    u16 field_06;
    u8 field_08;
    u8 field_09;
    u8 field_0A;
    u8 field_0B;
    u8 field_0C;
    u8 pad_0D[3];
    u32 field_10;
    u32 field_14;
    u32 field_18;
    u32 field_1C;
    u16 field_20;
    u8 pad_22[2];
    u16 field_24;
    u8 field_26;
    u8 pad_27[9];
    void *field_30;
    void *field_34;
    void *field_38;
};

struct MbStream {
    u8 field_00;
    u8 pad_01;
    u8 field_02;
    u8 pad_03[7];
    u8 field_0A;
    u8 pad_0B;
    u8 field_0C;
    u8 pad_0D;
    u8 field_0E;
    u8 field_0F;
    u8 pad_10[2];
    u8 field_12;
    u8 pad_13;
    u8 field_14;
    u8 pad_15;
    u8 field_16;
    u8 pad_17;
    u8 field_18;
    u8 pad_19;
    u8 field_1A;
    u8 field_1B;
    u8 pad_1C;
    u8 field_1D;
    u8 pad_1E[2];
    u32 field_20;
    u8 pad_24[4];
    u32 field_28;
    u32 field_2C;
    u32 field_30;
    u32 field_34;
    u8 pad_38[8];
    u8 *cursor;
    u32 saved[3];
};

struct MbScaleObject {
    u8 pad_00[0x1C];
    u16 field_1C;
    u16 field_1E;
    u16 field_20;
};

struct MbPair {
    u32 first;
    u32 second;
};

struct MbTaggedObject {
    u8 pad_00[4];
    u32 flags;
    u8 pad_08[0x2C];
    u32 tag;
};

struct MbBitObject {
    u8 pad_00[8];
    u8 low_08 : 2;
    u8 variant : 1;
    u8 high_08 : 5;
    u8 frame : 3;
    u8 high_09 : 5;
    u8 field_0A;
    u8 pad_0B[0x0D];
    u32 field_18;
};

void sub_8F6F360(void *, void *);
void sub_8F6F364(void *, void *, void *);
void sub_8F95EC0(void *, void *);
void sub_8F6124C(void);
void sub_8F87BA0(void);
void sub_8F6D634(void *, struct MbStream *);
void sub_8F6D170(void);
void sub_8F5CC20(void *);
u8 sub_8F65EA0(void *);

/* Unselected drafts remain local to this translation unit's discarded sections. */
#define nullsub_2 draft_nullsub_2
#define nullsub_11 draft_nullsub_11
#define sub_8F62FCC draft_sub_8F62FCC
#define sub_8F89920 draft_sub_8F89920
#define sub_8F5FC2C draft_sub_8F5FC2C
#define sub_8F63B14 draft_sub_8F63B14
#define sub_8F6B860 draft_sub_8F6B860
#define sub_8F6C0C8 draft_sub_8F6C0C8
#define sub_8F6C8CC draft_sub_8F6C8CC
#define sub_8F6D148 draft_sub_8F6D148
#define sub_8F66A40 draft_sub_8F66A40
#define sub_8F8D394 draft_sub_8F8D394
#define sub_8F6DD2C draft_sub_8F6DD2C
#define sub_8F948AC draft_sub_8F948AC
#define sub_8F5F3C8 draft_sub_8F5F3C8
#define sub_8F85D1C draft_sub_8F85D1C
#define sub_8F6E1F8 draft_sub_8F6E1F8
#define sub_8F6E20C draft_sub_8F6E20C
#define sub_8F94D78 draft_sub_8F94D78
#define sub_8F94D8C draft_sub_8F94D8C
#define sub_8F6F210 draft_sub_8F6F210
#define sub_8F6DE98 draft_sub_8F6DE98
#define sub_8F6118C draft_sub_8F6118C
#define sub_8F611DC draft_sub_8F611DC
#define sub_8F5FCAC draft_sub_8F5FCAC
#define sub_8F60670 draft_sub_8F60670
#define sub_8F86600 draft_sub_8F86600
#define sub_08F86FC4 draft_sub_08F86FC4
#define sub_8F65690 draft_sub_8F65690
#define sub_8F63634 draft_sub_8F63634
#define sub_8F64880 draft_sub_8F64880
#define sub_8F65118 draft_sub_8F65118
#define sub_8F8BA6C draft_sub_8F8BA6C
#define sub_8F5DFC4 draft_sub_8F5DFC4
#define sub_8F63D08 draft_sub_8F63D08
#define sub_8F84918 draft_sub_8F84918
#define sub_8F8A65C draft_sub_8F8A65C
#define sub_8F61E58 draft_sub_8F61E58
#define sub_8F624CC draft_sub_8F624CC
#define sub_8F887AC draft_sub_8F887AC
#define sub_8F88E20 draft_sub_8F88E20
#define sub_8F5D0C0 draft_sub_8F5D0C0
#define sub_8F5C06C draft_sub_8F5C06C
#define sub_8F6DEA4 draft_sub_8F6DEA4
#define sub_8F51DA0 draft_sub_8F51DA0
#define sub_8F5E604 draft_sub_8F5E604
#define sub_8F6F1F0 draft_sub_8F6F1F0
#define sub_8F59844 draft_sub_8F59844
#define sub_8F6DD48 draft_sub_8F6DD48
#define sub_8F6D67C draft_sub_8F6D67C
#define sub_8F6D6E0 draft_sub_8F6D6E0
#define sub_8F6D724 draft_sub_8F6D724
#define sub_8F6D738 draft_sub_8F6D738
#define sub_8F6D74C draft_sub_8F6D74C
#define sub_8F6D760 draft_sub_8F6D760
#define sub_8F6D798 draft_sub_8F6D798
#define sub_8F6D6C0 draft_sub_8F6D6C0
#define sub_8F6D774 draft_sub_8F6D774
#define sub_8F6D780 draft_sub_8F6D780
#define sub_8F6D6CC draft_sub_8F6D6CC
#define sub_8F5FC44 draft_sub_8F5FC44
#define sub_8F86598 draft_sub_8F86598
#define sub_8F61E30 draft_sub_8F61E30
#define sub_8F624A4 draft_sub_8F624A4
#define sub_8F88784 draft_sub_8F88784
#define sub_8F88DF8 draft_sub_8F88DF8
#define sub_8F6DDE4 draft_sub_8F6DDE4
#define sub_8F94964 draft_sub_8F94964
#define sub_8F64B84 draft_sub_8F64B84
#define sub_8F57344 draft_sub_8F57344
#define sub_8F5C8CC draft_sub_8F5C8CC
#define sub_8F50BC0 draft_sub_8F50BC0
#define sub_08F7E6C8 draft_sub_08F7E6C8
#define sub_8F60638 draft_sub_8F60638
#define sub_08F86F8C draft_sub_08F86F8C
#define sub_8F51F88 draft_sub_8F51F88
#define sub_8F6CA90 draft_sub_8F6CA90
#define sub_8F51344 draft_sub_8F51344
#define sub_8F83030 draft_sub_8F83030
#define sub_8F5DFE4 draft_sub_8F5DFE4
#define sub_8F632B8 draft_sub_8F632B8
#define sub_8F6D5B0 draft_sub_8F6D5B0
#define sub_8F6DE00 draft_sub_8F6DE00

MB_SECTION(nullsub_12) void nullsub_12(void) {}
MB_SECTION(nullsub_12) const u16 nullsub_12_padding = 0;
MB_SECTION(nullsub_9) void nullsub_9(void) {}
MB_SECTION(nullsub_9) const u16 nullsub_9_padding = 0;
MB_SECTION(nullsub_13) void nullsub_13(void) {}
MB_SECTION(nullsub_13) const u16 nullsub_13_padding = 0;
MB_SECTION(nullsub_14) void nullsub_14(void) {}
MB_SECTION(nullsub_14) const u16 nullsub_14_padding = 0;
MB_SECTION(nullsub_2) void nullsub_2(void) {}
MB_SECTION(nullsub_2) const u16 nullsub_2_padding = 0;
MB_SECTION(nullsub_11) void nullsub_11(void) {}
MB_SECTION(nullsub_11) const u16 nullsub_11_padding = 0;

#define DEFINE_TABLE_CALL(name, offset, table) \
    MB_SECTION(name) void name(struct MbObject *obj) { \
        sub_8F6F360(obj, ((void **)(table))[*((u8 *)obj + (offset))]); \
    }

DEFINE_TABLE_CALL(sub_8F5FC2C, 4, 0x08F9FE98)
DEFINE_TABLE_CALL(sub_8F63B14, 4, 0x08FA02CC)
DEFINE_TABLE_CALL(sub_8F6B860, 2, 0x08FA1528)
DEFINE_TABLE_CALL(sub_8F6C0C8, 4, 0x08FA153C)
DEFINE_TABLE_CALL(sub_8F6C8CC, 2, 0x08FA16CC)
DEFINE_TABLE_CALL(sub_8F6D148, 2, 0x08FA186C)

#define DEFINE_DIRECT_HANDLER(name, table) \
    MB_SECTION(name) void name(struct MbObject *obj) { \
        u32 offset = obj->field_08; \
        offset &= 4; \
        obj->field_18 = *(u32 *)((u8 *)(table) + offset); \
    }

DEFINE_DIRECT_HANDLER(sub_8F65118, 0x08FA0444)
DEFINE_DIRECT_HANDLER(sub_8F8BA6C, 0x0201E78C)

#define DEFINE_STACK_HANDLER(name, table) \
    MB_SECTION(name) void name(struct MbObject *obj) { \
        u32 offset = obj->field_08; \
        struct MbPair choices = *(struct MbPair *)(table); \
        offset &= 4; \
        obj->field_18 = *(u32 *)((u8 *)&choices + offset); \
    }

DEFINE_STACK_HANDLER(sub_8F5DFC4, 0x08F9FD50)
DEFINE_STACK_HANDLER(sub_8F63D08, 0x08FA02D4)
DEFINE_STACK_HANDLER(sub_8F84918, 0x0201E098)
DEFINE_STACK_HANDLER(sub_8F8A65C, 0x0201E61C)

#define DEFINE_FRAME_HANDLER(name, table) \
    MB_SECTION(name) void name(struct MbBitObject *obj) { \
        u32 frame = obj->frame & 3; \
        obj->field_18 = ((u32 (*)[2])(table))[frame][obj->variant]; \
    }

#define DEFINE_FRAME_BITS(name, table) \
    MB_SECTION(name) void name(struct MbObject *obj) { \
        u32 frame = obj->field_09 & 7; \
        u32 bits; \
        frame &= 3; \
        bits = ((u8 *)(table))[frame] & 0xF; \
        bits <<= 3; \
        obj->field_0A = (obj->field_0A & ~0x78) | bits; \
    }

DEFINE_FRAME_HANDLER(sub_8F61E30, 0x08FA0114)
DEFINE_FRAME_BITS(sub_8F61E58, 0x08FA0134)
DEFINE_FRAME_HANDLER(sub_8F624A4, 0x08FA0184)
DEFINE_FRAME_BITS(sub_8F624CC, 0x08FA01A4)
DEFINE_FRAME_HANDLER(sub_8F88784, 0x0201E45C)
DEFINE_FRAME_BITS(sub_8F887AC, 0x0201E47C)
DEFINE_FRAME_HANDLER(sub_8F88DF8, 0x0201E4CC)
DEFINE_FRAME_BITS(sub_8F88E20, 0x0201E4EC)

#define DEFINE_OBJECT_INIT(name) \
    MB_SECTION(name) void name(struct MbObject *obj) { \
        u32 zero = 0; \
        obj->field_0C = 9; \
        obj->field_0B = zero; \
        obj->field_0A |= 0x80; \
        obj->field_04 = 4; \
    }

DEFINE_OBJECT_INIT(sub_8F62FCC)
MB_SECTION(sub_8F62FCC) const u16 sub_8F62FCC_padding = 0;
DEFINE_OBJECT_INIT(sub_8F89920)
MB_SECTION(sub_8F89920) const u16 sub_8F89920_padding = 0;

MB_SECTION(sub_8F66A40) u32 sub_8F66A40(u8 value) { return value == 2 ? 2 : 1; }
MB_SECTION(sub_8F8D394) u32 sub_8F8D394(u8 value) { return value == 2 ? 2 : 1; }

#define DEFINE_MAGIC_CLEAR(name) \
    MB_SECTION(name) void name(u32 *obj) { \
        u32 *ptr = obj; \
        if (ptr[13] == 0x68736D53) ptr[1] &= 0x7FFFFFFF; \
    }

DEFINE_MAGIC_CLEAR(sub_8F6DDE4)
DEFINE_MAGIC_CLEAR(sub_8F94964)

#define DEFINE_STREAM_FLAGS(name) \
    MB_SECTION(name) void name(void *unused, struct MbStream *stream) { \
        u8 bits; \
        stream->field_16 = 0; \
        stream->field_1A = 0; \
        bits = stream->field_18 == 0 ? 0x0C : 3; \
        stream->field_00 |= bits; \
    }

DEFINE_STREAM_FLAGS(sub_8F6DD2C)
DEFINE_STREAM_FLAGS(sub_8F948AC)

MB_SECTION(sub_8F5F3C8) void sub_8F5F3C8(struct MbObject *obj) {
    obj->field_10 = ((u32 (*)(u32, u32))sub_8F6124C)(obj->field_10, obj->field_18);
    obj->field_14 += obj->field_1C;
}

MB_SECTION(sub_8F85D1C) void sub_8F85D1C(struct MbObject *obj) {
    obj->field_10 = ((u32 (*)(u32, u32))sub_8F87BA0)(obj->field_10, obj->field_18);
    obj->field_14 += obj->field_1C;
}

#define DEFINE_GLOBAL_CALL(name, callback, address) \
    MB_SECTION(name) void name(void *arg) { callback(arg, *(void **)(address)); }

DEFINE_GLOBAL_CALL(sub_8F6E1F8, sub_8F6F360, 0x03006AE8)
DEFINE_GLOBAL_CALL(sub_8F6E20C, sub_8F6F360, 0x03006AEC)
DEFINE_GLOBAL_CALL(sub_8F94D78, sub_8F95EC0, 0x03006A28)
DEFINE_GLOBAL_CALL(sub_8F94D8C, sub_8F95EC0, 0x03006A2C)

MB_SECTION(sub_8F6F210) void sub_8F6F210(void *a, void *b) {
    sub_8F6F364(a, b, *(void **)0x03006A60);
}

MB_SECTION(sub_8F6D67C) void sub_8F6D67C(void *unused, struct MbStream *stream) {
    if (stream->field_02 != 0) {
        stream->field_02--;
        stream->cursor = (u8 *)stream->saved[stream->field_02];
    }
}

#define DEFINE_STREAM_STORE(name, field, adjust, bits) \
    MB_SECTION(name) void name(void *arg, struct MbStream *stream) { \
        sub_8F6D634(arg, stream); \
        stream->field = (u8)(*stream->cursor - (adjust)); \
        stream->field_00 |= (bits); \
    }

DEFINE_STREAM_STORE(sub_8F6D6E0, field_0A, 0, 0x0C)
DEFINE_STREAM_STORE(sub_8F6D724, field_12, 0, 0x03)
DEFINE_STREAM_STORE(sub_8F6D738, field_14, 0x40, 0x03)
DEFINE_STREAM_STORE(sub_8F6D74C, field_0E, 0x40, 0x0C)
DEFINE_STREAM_STORE(sub_8F6D760, field_0F, 0, 0x0C)
DEFINE_STREAM_STORE(sub_8F6D798, field_0C, 0x40, 0x0C)

MB_SECTION(sub_8F6D6C0) void sub_8F6D6C0(void *arg, struct MbStream *stream) {
    sub_8F6D634(arg, stream);
    stream->field_1D = *stream->cursor;
}

MB_SECTION(sub_8F6D774) void sub_8F6D774(void *arg, struct MbStream *stream) {
    sub_8F6D634(arg, stream);
    stream->field_1B = *stream->cursor;
}

MB_SECTION(sub_8F6D780) void sub_8F6D780(void *arg, struct MbStream *stream) {
    u8 value;
    sub_8F6D634(arg, stream);
    value = *stream->cursor;
    if (stream->field_18 != value) {
        stream->field_18 = value;
        stream->field_00 |= 0x0F;
    }
}

MB_SECTION(sub_8F6D6CC) void sub_8F6D6CC(struct MbScaleObject *obj, struct MbStream *stream) {
    u32 value;
    sub_8F6D634(obj, stream);
    value = *stream->cursor * 2;
    obj->field_1C = value;
    obj->field_20 = value * obj->field_1E >> 8;
}

MB_SECTION(sub_8F6DE98) void sub_8F6DE98(void) { sub_8F6D170(); }

MB_SECTION(sub_8F6118C) void sub_8F6118C(struct MbObject *obj) {
    obj->field_24--;
    if (obj->field_24 == 0) sub_8F5CC20(obj);
}

MB_SECTION(sub_8F611DC) void sub_8F611DC(struct MbObject *obj) {
    if (sub_8F65EA0(obj)) obj->field_04++;
}

#define DEFINE_CLAMP_BITS(name, table) \
    MB_SECTION(name) void name(struct MbObject *obj) { \
        u32 frame = obj->field_09 & 7; \
        if (frame > 2) frame = 2; \
        obj->field_0A = (obj->field_0A & ~0x78) | ((((u8 *)(table))[frame] & 0xF) << 3); \
    }

DEFINE_CLAMP_BITS(sub_8F5FCAC, 0x08F9FEE0)
DEFINE_CLAMP_BITS(sub_8F60670, 0x08F9FF8C)
DEFINE_CLAMP_BITS(sub_8F86600, 0x0201E228)
DEFINE_CLAMP_BITS(sub_08F86FC4, 0x0201E2D4)

#define DEFINE_CLAMP_HANDLER(name, table) \
    MB_SECTION(name) void name(struct MbObject *obj) { \
        u32 frame = obj->field_09 & 7; \
        u32 variant = (obj->field_08 >> 5) & 1; \
        if (frame > 2) frame = 2; \
        obj->field_18 = ((u32 *)(table))[variant + frame * 2]; \
    }

DEFINE_CLAMP_HANDLER(sub_8F5FC44, 0x08F9FEB0)
DEFINE_CLAMP_HANDLER(sub_8F86598, 0x0201E1F8)

MB_SECTION(sub_8F65690) void sub_8F65690(struct MbObject *obj) {
    u8 frame = obj->field_0B + 1;
    u8 variant = obj->field_0C;
    if (frame > 0x13) {
        frame = 0;
        variant ^= 1;
    }
    obj->field_06 = variant + 9;
    obj->field_0C = variant;
    obj->field_0B = frame;
}

MB_SECTION(sub_8F63634) void sub_8F63634(struct MbObject *obj) {
    u8 variant = obj->field_0C;
    u8 frame = obj->field_0B + 1;
    if (frame > 7) {
        frame = 0;
        variant++;
        if (variant > 4) variant = 1;
        obj->field_0C = variant;
    }
    obj->field_0B = frame;
}

MB_SECTION(sub_8F64880) void sub_8F64880(struct MbObject *obj) {
    u8 variant = obj->field_0C;
    u8 frame = obj->field_0B + 1;
    if (frame > 2) {
        frame = 0;
        variant++;
        if (variant > 3) variant = 1;
    }
    obj->field_0C = variant;
    obj->field_0B = frame;
}

MB_SECTION(sub_8F64B84) void sub_8F64B84(struct MbObject *obj) {
    obj->field_1C = 0xFFFFFE00;
    obj->field_0A |= 0x84;
    if (obj->field_26 != 0) obj->field_26 = 0;
}

MB_SECTION(sub_8F57344) void sub_8F57344(void) {
    u8 *base = *(u8 **)(0x03000F50 + 0x447C);
    u8 *value = base + 0x2D + *(u8 *)(*(u8 **)(base + 0x54) + 0x0C);
    u8 next = *value + 1;
    if (next > 0x62) next = 0x63;
    *value = next;
}

MB_SECTION(sub_8F5C8CC) void sub_8F5C8CC(void) {
    *(volatile u16 *)0x04000200 = 1;
    *(volatile u16 *)0x04000004 = 8;
    *(volatile u16 *)0x04000208 = 1;
    *(u8 *)(0x03000F50 + 0x0C4F) = 1;
    (*(u8 *)(0x03000F50 + 0x0C5A))++;
}

MB_SECTION(sub_8F50BC0) void sub_8F50BC0(void) {
    u16 keys = ~*(volatile u16 *)0x04000130;
    u16 *held = (u16 *)(0x03000F50 + 0x824);
    *(u16 *)(0x03000F50 + 0x826) = keys & ~*held;
    *held = keys;
}

MB_SECTION(sub_8F5D0C0) u16 sub_8F5D0C0(u16 value) {
    u16 next = (value + 2) & 0x083E;
    if ((next & 0x3E) == 0) next = (next + 0x800) & 0x800;
    return next;
}

MB_SECTION(sub_08F7E6C8) void sub_08F7E6C8(void) {
    u32 *dst = (u32 *)(0x03000F40 + 0x82C);
    u32 *src = (u32 *)0x0201D6F8;
    u32 first = src[0];
    u32 second = src[1];
    s32 count = 0x7E;
    do {
        dst[0] = first;
        dst[1] = second;
        dst[2] = first;
        dst[3] = second;
        dst += 4;
        count -= 2;
    } while (count >= 0);
}

#define DEFINE_COMPLEX_HANDLER(name, table) \
    MB_SECTION(name) void name(struct MbObject *obj) { \
        u32 frame = obj->field_09 & 7; \
        u32 variant = (obj->field_08 >> 5) & 1; \
        frame = (u8)(frame + *(u8 *)obj->field_38); \
        if (frame > 3) frame = 3; \
        obj->field_18 = ((u32 *)(table))[variant + frame * 2]; \
    }

DEFINE_COMPLEX_HANDLER(sub_8F60638, 0x08F9FF6C)
DEFINE_COMPLEX_HANDLER(sub_08F86F8C, 0x0201E2B4)

MB_SECTION(sub_8F648AC) void sub_8F648AC(struct MbObject *obj) {
    u8 variant = obj->field_0C;
    u8 frame = obj->field_0B;
    if (variant <= 5) {
        frame++;
        if (frame > 3) {
            frame = 0;
            variant++;
        }
        obj->field_0C = variant;
        obj->field_0B = frame;
    }
}
MB_SECTION(sub_8F648AC) const u16 sub_8F648AC_padding = 0;

MB_SECTION(sub_8F51F88) void sub_8F51F88(u8 value, u8 x, u8 y) {
    u8 *base = **(u8 ***)(0x03000F50 + 0x4480);
    base[((u32)y >> 3) * 32 + ((u32)x >> 3)] = value;
}

MB_SECTION(sub_8F6CA90) void sub_8F6CA90(struct MbObject *obj) {
    u8 angle = (obj->field_10 >> 8) + *(u8 *)(0x03000F50 + 0x0C5B);
    obj->field_24 = (angle >> 2) | ((angle << 6) >> 8);
    obj->field_0C = 0;
    obj->field_04 = 5;
}

#define DEFINE_COPY_256(name, address) \
    MB_SECTION(name) void name(u16 *src) { \
        u8 i = 0; \
        volatile u8 *state = (volatile u8 *)(address); \
        do { \
            ((u16 *)*(u32 *)(state + 0x24))[i] = src[i]; \
            i++; \
        } while (i != 0); \
        *(u8 *)(*(u32 *)(state + 0x24) + 2) = state[4]; \
        *(u8 *)(*(u32 *)(state + 0x24) + 3) = state[1]; \
    }

DEFINE_COPY_256(sub_8F51344, 0x03005940)
DEFINE_COPY_256(sub_8F83030, 0x03005910)

void _08F6F340(u32);
MB_SECTION(sub_8F5C06C) void sub_8F5C06C(void) {
    *(u32 *)0x0203FFF8 = 0;
    *(u8 *)0x0203FFFC = 0;
    *(u8 *)0x0203FFFF = (*(u8 *)0x0203FFFF & 0xFC) | 2;
    _08F6F340(0x9C);
}

struct MbDeaEntry { void *arg; u16 pad_04; u16 index; };
void sub_8F6E5D8(void *, void *);
MB_SECTION(sub_8F6DEA4) void sub_8F6DEA4(u16 index) {
    struct MbDeaEntry *entry = &((struct MbDeaEntry *)0x08FB5DA4)[index];
    void *callback = ((void **)0x08FB5C24)[entry->index * 3];
    sub_8F6E5D8(callback, entry->arg);
}

MB_SECTION(sub_8F51DA0) u32 sub_8F51DA0(struct MbObject *obj) {
    return *(u8 *)((u8 *)obj + 0x18) == 0xE9;
}

MB_SECTION(sub_8F585B0) void sub_8F585B0(u16 value, u16 *dst) {
    u16 i = 0;
    do {
        *dst++ = value;
        i++;
    } while (i <= 0x3FF);
}

void sub_8F61D74(void);
MB_SECTION(sub_8F5DFE4) void sub_8F5DFE4(void) {
    u8 *obj = *(u8 **)(0x03000F50 + 0x4480);
    if (obj[0x29] == 0) sub_8F61D74();
}

MB_SECTION(sub_8F5E604) void sub_8F5E604(struct MbObject *obj) {
    u8 variant = obj->field_0C;
    u8 frame = obj->field_0B + 1;
    if (frame > 7) {
        frame = 0;
        variant++;
        if (variant > 4) variant = 0;
        obj->field_0C = variant;
        obj->field_06 = variant + 1;
    }
    obj->field_0B = frame;
}

MB_SECTION(sub_8F632B8) void sub_8F632B8(struct MbObject *obj) {
    u8 *state = *(u8 **)(0x03000F50 + 0x4480);
    if (*(u8 *)obj->field_38 == 0)
        *(u16 *)(state + 0x18) = 0xF0;
    else
        *(u16 *)(state + 0x1C) = 0xF0;
}

struct MbListNode {
    u8 pad_00[0x20];
    struct MbListNode *alternate;
    u8 pad_24[8];
    struct MbListNode *owner;
    struct MbListNode *prev;
    struct MbListNode *next;
};

MB_SECTION(sub_8F6D5B0) void sub_8F6D5B0(struct MbListNode *node) {
    struct MbListNode *owner = node->owner;
    if (owner != 0) {
        struct MbListNode *next = node->next;
        struct MbListNode *prev = node->prev;
        if (prev != 0)
            prev->next = next;
        else
            owner->alternate = next;
        if (next != 0) next->prev = prev;
        node->owner = 0;
    }
}

struct MbTaggedHalfwords {
    u8 pad_00[0x24];
    u16 first;
    u16 second;
    u16 scale;
    u8 pad_2A[0x0A];
    u32 tag;
};

MB_SECTION(sub_8F6DE00) void sub_8F6DE00(struct MbTaggedHalfwords *obj, u16 value) {
    if (obj->tag == 0x68736D53) {
        obj->second = value;
        obj->first = value;
        obj->scale = 0x100;
    }
}

MB_SECTION(sub_8F6F1F0) void sub_8F6F1F0(void *a, struct MbStream *stream) {
    u8 index = *stream->cursor++;
    sub_8F6F364(a, stream, ((void **)0x08FB4CD0)[index]);
}

MB_SECTION(sub_8F59844) void sub_8F59844(void) {
    u8 *base = (u8 *)0x03000F50;
    u32 zero = 0;
    *(u16 *)(base + 0x080A) = 0xE4;
    *(u16 *)(base + 0x0818) = 4;
    base[0x0C5A] = 0x16;
    base[0x0C50] = zero;
    base[0x0C51] = zero;
}

MB_SECTION(sub_8F6DD48) void sub_8F6DD48(void *unused, struct MbStream *stream) {
    *(volatile u8 *)stream->cursor++;
}
