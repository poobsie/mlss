#include "global.h"

#define FIELD_AT(ptr, type, offset) (*(type)((u8*)(ptr) + (offset)))
#define SECTION(name)               __attribute__((section(".text.early_code_helpers." #name)))

struct CallbackAt1A0 {
    u8 padding[0x1A0];
    void (*function)(void*, u8*, void*);
};

void sub_80FC1F8(void);
void sub_802FAE4(void*, void*, s32);
void sub_8029A0C(void*, void*, s32);
void sub_8139AA0(void*);
void sub_80514C4(void);

s32 sub_803E9F0(void* arg0) SECTION(sub_803E9F0);
s32 sub_803E9F0(void* arg0) {
    return 1 & FIELD_AT(arg0, u8*, 0x291);
}

void sub_801AF50(void) SECTION(sub_801AF50);
void sub_801AF50(void) {
    sub_80FC1F8();
}
SECTION(sub_801AF50) const u16 sub_801AF50_padding = 0;

void sub_801DC38(u8* arg0) SECTION(sub_801DC38);
void sub_801DC38(u8* arg0) {
    ((void (*)(s32, s32)) * (void**)(arg0 + 0x14))(*(s32*)arg0, *(s32*)(arg0 + 4));
}
SECTION(sub_801DC38) const u16 sub_801DC38_padding = 0;

void sub_803C538(void* arg0, void* arg1) SECTION(sub_803C538);
void sub_803C538(void* arg0, void* arg1) {
    sub_802FAE4(arg0, arg1, 1);
}

void sub_803C898(void* arg0, void* arg1) SECTION(sub_803C898);
void sub_803C898(void* arg0, void* arg1) {
    sub_8029A0C(arg0, arg1, 1);
}

void sub_8051614(void* arg0, u8* arg1) SECTION(sub_8051614);
void sub_8051614(void* arg0, u8* arg1) {
    struct CallbackAt1A0* object = (struct CallbackAt1A0*)arg1;
    object->function(arg0, arg1, &object->function);
}
SECTION(sub_8051614) const u16 sub_8051614_padding = 0;

void sub_80515DC(void* arg0, u8* arg1) SECTION(sub_80515DC);
void sub_80515DC(void* arg0, u8* arg1) {
    sub_8139AA0(arg1);
    *(void (**)(void))(arg1 + 0x198) = (void (*)(void))sub_8051614;
    *(void (**)(void))(arg1 + 0x1A0) = sub_80514C4;
}

void sub_8051608(void* arg0, u8* arg1) SECTION(sub_8051608);
void sub_8051608(void* arg0, u8* arg1) {
    sub_80515DC(arg0, arg1);
}
SECTION(sub_8051608) const u16 sub_8051608_padding = 0;
