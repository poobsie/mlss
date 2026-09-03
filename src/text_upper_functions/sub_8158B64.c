#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.upper_gate." #name)))
u16* sub_815FA3C(void*);   /* extern */
UnknownWord sub_815FAA4(); /* extern */

SEC(sub_8158B64) void sub_8158B64(void* arg0) {
    sub_815FAA4();
    if (FIELD_AT(arg0, void**, 0x40) != NULL) {
        FIELD_AT(FIELD_AT(arg0, void**, 0x40), u16*, 0) = (u16)*sub_815FA3C(arg0);
        FIELD_AT(FIELD_AT(arg0, void**, 0x40), u16*, 2) = (u16)FIELD_AT(sub_815FA3C(arg0), u16*, 2);
    }
}
