#include "global.h"
#include "mario_bros/callback.h"
#include "mario_bros/object.h"

#define MB_SECTION(name) __attribute__((section(".text.mariobros_helpers_" #name)))

extern void *gMarioData_08F9FE98[];
extern void *gMarioData_08FA02CC[];
extern void *gMarioData_08FA1528[];
extern void *gMarioData_08FA153C[];
extern void *gMarioData_08FA16CC[];
extern void *gMarioData_08FA186C[];
extern u32 gMarioData_08FA0444[];
extern u32 gMarioData_0201E78C[];

#define DEFINE_TABLE_CALL(name, offset, table)                                                         \
    MB_SECTION(name) void name(struct MarioBrosObject* obj) {                                         \
        void** entries = (void**)(table);                                                              \
        u8 index = *((u8*)obj + (offset));                                                             \
        mario_bros_call_callback_with_object(obj, entries[index]);                                    \
    }

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
