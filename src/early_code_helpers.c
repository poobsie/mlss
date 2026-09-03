#include "global.h"

#define FIELD_AT(ptr, type, offset) (*(type)((u8*)(ptr) + (offset)))
#define SECTION(name)               __attribute__((section(".text.early_code_helpers." #name)))

struct CallbackAt1A0 {
    u8 padding[0x1A0];
    void (*function)(void*, u8*, void*);
};

void sub_8139AA0(void*);
void sub_80514C4(void);

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
