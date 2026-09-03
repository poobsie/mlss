#include "global.h"

#define MB_SECTION(name) __attribute__((section(".text.mariobros_helpers_" #name)))

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
    void* field_30;
    void* field_34;
    void* field_38;
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
    u8* cursor;
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

struct MbStateObject {
    u8 field_00;
    u8 state;
    u8 pad_02[0x3C];
    u8 field_3E;
    u8 pad_3F[2];
    u8 field_41;
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

struct __attribute__((packed)) MbBits0A {
    u8 low : 3;
    u8 value : 4;
    u8 high : 1;
};

void sub_8F6F360(void*, void*);
void sub_8F6F364(void*, void*, void*);
void sub_8F95EC0(void*, void*);
void sub_8F6124C(void);
void sub_8F87BA0(void);
void sub_8F6D634(void*, struct MbStream*);
void sub_8F6D170(void);
void sub_8F5CC20(void*);
u8 sub_8F65EA0(void*);
void sub_8F66360(void*, u32);
void sub_8F8CCB4(void*, u32);
void sub_8F568DC(u32, u32, void*);
void sub_8F57F2C(void);

MB_SECTION(nullsub_12) void nullsub_12(void) {
}
MB_SECTION(nullsub_12) const u16 nullsub_12_padding = 0;
MB_SECTION(nullsub_9) void nullsub_9(void) {
}
MB_SECTION(nullsub_9) const u16 nullsub_9_padding = 0;
MB_SECTION(nullsub_13) void nullsub_13(void) {
}
MB_SECTION(nullsub_13) const u16 nullsub_13_padding = 0;
MB_SECTION(nullsub_14) void nullsub_14(void) {
}
MB_SECTION(nullsub_14) const u16 nullsub_14_padding = 0;

#define DEFINE_TABLE_CALL(name, offset, table)                                                         \
    MB_SECTION(name) void name(struct MbObject* obj) {                                                 \
        void** entries = (void**)(table);                                                              \
        u8 index = *((u8*)obj + (offset));                                                             \
        sub_8F6F360(obj, entries[index]);                                                              \
    }

extern void *gMarioData_08F9FE98[];
extern void *gMarioData_08FA02CC[];
extern void *gMarioData_08FA1528[];
extern void *gMarioData_08FA153C[];
extern void *gMarioData_08FA16CC[];
extern void *gMarioData_08FA186C[];
extern u32 gMarioData_08FA0444[];
extern u32 gMarioData_0201E78C[];

DEFINE_TABLE_CALL(sub_8F5FC2C, 4, gMarioData_08F9FE98)
DEFINE_TABLE_CALL(sub_8F63B14, 4, gMarioData_08FA02CC)
DEFINE_TABLE_CALL(sub_8F6B860, 2, gMarioData_08FA1528)
DEFINE_TABLE_CALL(sub_8F6C0C8, 4, gMarioData_08FA153C)
DEFINE_TABLE_CALL(sub_8F6C8CC, 2, gMarioData_08FA16CC)
DEFINE_TABLE_CALL(sub_8F6D148, 2, gMarioData_08FA186C)

#define DEFINE_DIRECT_HANDLER(name, table)                                                             \
    MB_SECTION(name) void name(struct MbObject* obj) {                                                 \
        u32 flags = obj->field_08;                                                                     \
        u32 offset = 4;                                                                                \
        u32* entries = (u32*)(table);                                                                  \
        offset &= flags;                                                                               \
        obj->field_18 = *(u32*)((u8*)entries + offset);                                                \
    }

DEFINE_DIRECT_HANDLER(sub_8F65118, gMarioData_08FA0444)
DEFINE_DIRECT_HANDLER(sub_8F8BA6C, gMarioData_0201E78C)

#define DEFINE_STACK_HANDLER(name, table)                                                              \
    MB_SECTION(name) void name(struct MbObject* obj) {                                                 \
        u32 offset = obj->field_08;                                                                    \
        struct MbPair choices = *(struct MbPair*)(table);                                              \
        offset &= 4;                                                                                   \
        obj->field_18 = *(u32*)((u8*)&choices + offset);                                               \
    }

#define DEFINE_FRAME_HANDLER(name, table)                                                              \
    MB_SECTION(name) void name(struct MbBitObject* obj) {                                              \
        u32 frame = obj->frame & 3;                                                                    \
        obj->field_18 = ((u32(*)[2])(table))[frame][obj->variant];                                     \
    }

#define DEFINE_FRAME_BITS(name, table)                                                                 \
    MB_SECTION(name) void name(struct MbObject* obj) {                                                 \
        u32 frame = ((struct MbBitObject*)obj)->frame;                                                 \
        frame &= 3;                                                                                    \
        ((struct MbBits0A*)&obj->field_0A)->value = ((u8*)(table))[frame] & 0xF;                        \
    }

DEFINE_FRAME_BITS(sub_8F61E58, 0x08FA0134)
DEFINE_FRAME_BITS(sub_8F624CC, 0x08FA01A4)
DEFINE_FRAME_BITS(sub_8F887AC, 0x0201E47C)
DEFINE_FRAME_BITS(sub_8F88E20, 0x0201E4EC)

#define DEFINE_OBJECT_INIT(name)                                                                       \
    MB_SECTION(name) void name(struct MbObject* obj) {                                                 \
        u32 zero = 0;                                                                                  \
        obj->field_0C = 9;                                                                             \
        obj->field_0B = zero;                                                                          \
        obj->field_0A |= 0x80;                                                                         \
        obj->field_04 = 4;                                                                             \
    }

MB_SECTION(sub_8F66A40) u32 sub_8F66A40(u8 value) {
    switch (value) {
    case 2:
        return 2;
    default:
        return 1;
    }
}
MB_SECTION(sub_8F8D394) u32 sub_8F8D394(u8 value) {
    switch (value) {
    case 2:
        return 2;
    default:
        return 1;
    }
}

#define DEFINE_STATE_RESET(name, callback)                                                            \
    MB_SECTION(name) void name(struct MbStateObject* obj) {                                           \
        if (obj->state <= 7) {                                                                        \
            callback(obj, 1);                                                                         \
            obj->field_3E = 0x80;                                                                     \
            obj->field_41 = 0;                                                                        \
            obj->state = 3;                                                                           \
        }                                                                                             \
    }

DEFINE_STATE_RESET(sub_8F663B4, sub_8F66360)
DEFINE_STATE_RESET(sub_8F8CD08, sub_8F8CCB4)

#define DEFINE_GLOBAL_INCREMENT(name)                                                                 \
    MB_SECTION(name) void name(void) {                                                                \
        u8* base = (u8*)0x03000F50;                                                                   \
        u8* root = *(u8**)(base + 0x447C);                                                            \
        u8* object = *(u8**)(root + 0x54);                                                            \
        sub_8F568DC(0x19, 0x58, *(void**)(object + 8));                                               \
        sub_8F57F2C();                                                                                \
        base[0xC5A]++;                                                                                \
    }

DEFINE_GLOBAL_INCREMENT(sub_8F58360)
DEFINE_GLOBAL_INCREMENT(sub_8F58398)

#define DEFINE_MAGIC_CLEAR(name)                                                                       \
    MB_SECTION(name) void name(u32* obj) {                                                             \
        u32* ptr = obj;                                                                                \
        if (ptr[13] == 0x68736D53)                                                                     \
            ptr[1] &= 0x7FFFFFFF;                                                                      \
    }

#define DEFINE_STREAM_FLAGS(name)                                                                      \
    MB_SECTION(name) void name(void* unused, struct MbStream* stream) {                                \
        u8 bits;                                                                                       \
        stream->field_16 = 0;                                                                          \
        stream->field_1A = 0;                                                                          \
        bits = stream->field_18 == 0 ? 0x0C : 3;                                                       \
        stream->field_00 |= bits;                                                                      \
    }

#define DEFINE_GLOBAL_CALL(name, callback, address)                                                    \
    MB_SECTION(name) void name(void* arg) {                                                            \
        callback(arg, *(void**)(address));                                                             \
    }

#define DEFINE_STREAM_STORE(name, field, adjust, bits)                                                 \
    MB_SECTION(name) void name(void* arg, struct MbStream* stream) {                                   \
        sub_8F6D634(arg, stream);                                                                      \
        stream->field = (u8)(*stream->cursor - (adjust));                                              \
        stream->field_00 |= (bits);                                                                    \
    }

#define DEFINE_CLAMP_BITS(name, table)                                                                 \
    MB_SECTION(name) void name(struct MbObject* obj) {                                                 \
        u32 frame = ((struct MbBitObject*)obj)->frame;                                                 \
        if (frame > 2)                                                                                 \
            frame = 2;                                                                                 \
        ((struct MbBits0A*)&obj->field_0A)->value = ((u8*)(table))[frame] & 0xF;                        \
    }

DEFINE_CLAMP_BITS(sub_8F5FCAC, 0x08F9FEE0)
DEFINE_CLAMP_BITS(sub_8F86600, 0x0201E228)

#define DEFINE_CLAMP_HANDLER(name, table)                                                              \
    MB_SECTION(name) void name(struct MbObject* obj) {                                                 \
        u32 frame = obj->field_09 & 7;                                                                 \
        u32 variant = (obj->field_08 >> 5) & 1;                                                        \
        if (frame > 2)                                                                                 \
            frame = 2;                                                                                 \
        obj->field_18 = ((u32*)(table))[variant + frame * 2];                                          \
    }

#define DEFINE_COMPLEX_HANDLER(name, table)                                                            \
    MB_SECTION(name) void name(struct MbObject* obj) {                                                 \
        u32 frame = obj->field_09 & 7;                                                                 \
        u32 variant = (obj->field_08 >> 5) & 1;                                                        \
        frame = (u8)(frame + *(u8*)obj->field_38);                                                     \
        if (frame > 3)                                                                                 \
            frame = 3;                                                                                 \
        obj->field_18 = ((u32*)(table))[variant + frame * 2];                                          \
    }

MB_SECTION(sub_8F648AC) void sub_8F648AC(struct MbObject* obj) {
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

#define DEFINE_COPY_256(name, address)                                                                 \
    MB_SECTION(name) void name(u16* src) {                                                             \
        u8 i = 0;                                                                                      \
        volatile u8* state = (volatile u8*)(address);                                                  \
        do {                                                                                           \
            ((u16*)*(u32*)(state + 0x24))[i] = src[i];                                                 \
            i++;                                                                                       \
        } while (i != 0);                                                                              \
        *(u8*)(*(u32*)(state + 0x24) + 2) = state[4];                                                  \
        *(u8*)(*(u32*)(state + 0x24) + 3) = state[1];                                                  \
    }

void _08F6F340(u32);

struct MbDeaEntry {
    void* arg;
    u16 pad_04;
    u16 index;
};
void sub_8F6E5D8(void*, void*);

MB_SECTION(sub_8F585B0) void sub_8F585B0(u16 value, u16* dst) {
    u16 i = 0;
    do {
        *dst++ = value;
        i++;
    } while (i <= 0x3FF);
}

void sub_8F61D74(void);

struct MbListNode {
    u8 pad_00[0x20];
    struct MbListNode* alternate;
    u8 pad_24[8];
    struct MbListNode* owner;
    struct MbListNode* prev;
    struct MbListNode* next;
};

struct MbTaggedHalfwords {
    u8 pad_00[0x24];
    u16 first;
    u16 second;
    u16 scale;
    u8 pad_2A[0x0A];
    u32 tag;
};
