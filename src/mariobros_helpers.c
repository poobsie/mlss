#include "global.h"
#include "mario_bros/object.h"

#define MB_SECTION(name) __attribute__((section(".text.mariobros_helpers_" #name)))

struct MarioBrosStateController {
    u8 unknown00;
    u8 state;
    u8 unknown02[0x3C];
    u8 flags3E;
    u8 unknown3F[2];
    u8 value41;
};

void sub_8F6F360(void*, void*);
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
    MB_SECTION(name) void name(struct MarioBrosObject* obj) {                                         \
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
    MB_SECTION(name) void name(struct MarioBrosObject* obj) {                                         \
        u32 flags = obj->flags08;                                                                      \
        u32 offset = 4;                                                                                \
        u32* entries = (u32*)(table);                                                                  \
        offset &= flags;                                                                               \
        obj->value18 = *(u32*)((u8*)entries + offset);                                                 \
    }

DEFINE_DIRECT_HANDLER(sub_8F65118, gMarioData_08FA0444)
DEFINE_DIRECT_HANDLER(sub_8F8BA6C, gMarioData_0201E78C)

#define DEFINE_FRAME_BITS(name, table)                                                                 \
    MB_SECTION(name) void name(struct MarioBrosObject* obj) {                                         \
        u32 frame = ((struct MarioBrosDisplayFrame*)&obj->displayFrame)->frame;                         \
        frame &= 3;                                                                                    \
        ((struct MarioBrosFlags0A*)&obj->flags0A)->tableValue = ((u8*)(table))[frame] & 0xF;            \
    }

DEFINE_FRAME_BITS(sub_8F61E58, 0x08FA0134)
DEFINE_FRAME_BITS(sub_8F624CC, 0x08FA01A4)
DEFINE_FRAME_BITS(sub_8F887AC, 0x0201E47C)
DEFINE_FRAME_BITS(sub_8F88E20, 0x0201E4EC)

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
    MB_SECTION(name) void name(struct MarioBrosStateController* obj) {                                \
        if (obj->state <= 7) {                                                                        \
            callback(obj, 1);                                                                         \
            obj->flags3E = 0x80;                                                                      \
            obj->value41 = 0;                                                                         \
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

#define DEFINE_CLAMP_BITS(name, table)                                                                 \
    MB_SECTION(name) void name(struct MarioBrosObject* obj) {                                         \
        u32 frame = ((struct MarioBrosDisplayFrame*)&obj->displayFrame)->frame;                         \
        if (frame > 2)                                                                                 \
            frame = 2;                                                                                 \
        ((struct MarioBrosFlags0A*)&obj->flags0A)->tableValue = ((u8*)(table))[frame] & 0xF;            \
    }

DEFINE_CLAMP_BITS(sub_8F5FCAC, 0x08F9FEE0)
DEFINE_CLAMP_BITS(sub_8F86600, 0x0201E228)

MB_SECTION(sub_8F648AC) void sub_8F648AC(struct MarioBrosObject* obj) {
    u8 variant = obj->animationVariant;
    u8 frame = obj->animationFrame;
    if (variant <= 5) {
        frame++;
        if (frame > 3) {
            frame = 0;
            variant++;
        }
        obj->animationVariant = variant;
        obj->animationFrame = frame;
    }
}
MB_SECTION(sub_8F648AC) const u16 sub_8F648AC_padding = 0;

MB_SECTION(sub_8F585B0) void sub_8F585B0(u16 value, u16* dst) {
    u16 i = 0;
    do {
        *dst++ = value;
        i++;
    } while (i <= 0x3FF);
}
