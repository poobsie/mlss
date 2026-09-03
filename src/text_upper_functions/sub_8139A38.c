#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.upper." #name)))
UnknownWord sub_813B380(UnknownWord, void*); /* extern */
extern UnknownWord sub_81397CC;

SEC(sub_8139A38) void sub_8139A38(UnknownWord arg0, void* arg1) {
    FIELD_AT(arg1, UnknownWord(**)(UnknownWord, void*), 0x198) = sub_813B380;
    FIELD_AT(arg1, UnknownWord**, 0x1A0) = &sub_81397CC;
    FIELD_AT(arg1, UnknownWord**, 0x1A4) = &sub_81397CC;
    sub_813B380(arg0, arg1);
}
