#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.upper." #name)))
UnknownWord process_add(void*, u8); /* extern */

SEC(tld_init_8127A94) void* tld_init_8127A94(void* arg0, u8 arg1) {
    process_add(arg0, arg1);
    FIELD_AT(arg0, s32*, 0x18) = 0x08CDC3C8;
    return arg0;
}
