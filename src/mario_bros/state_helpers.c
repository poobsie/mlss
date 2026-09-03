#include "global.h"

#define MB_SECTION(name) __attribute__((section(".text.mariobros_helpers_" #name)))

struct MarioBrosStateController {
    u8 unknown00;
    u8 state;
    u8 unknown02[0x3C];
    u8 flags3E;
    u8 unknown3F[2];
    u8 value41;
};

void sub_8F66360(void*, u32);
void sub_8F8CCB4(void*, u32);
void sub_8F568DC(u32, u32, void*);
void sub_8F57F2C(void);

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
