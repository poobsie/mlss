#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.upper." #name)))
UnknownWord free_heap_8018DA8(void*); /* extern */
UnknownWord sub_81617F4(s32, s32);    /* extern */
UnknownWord sub_8161C08(s32, s32);    /* extern */

SEC(sub_8158000) void sub_8158000(void* arg0, s32 arg1) {
    s32 temp_r0;
    s32 temp_r0_2;

    FIELD_AT(arg0, s32*, 4) = 0x08CDC4D0;
    temp_r0 = FIELD_AT(arg0, s32*, 8);
    if (temp_r0 != 0) {
        sub_81617F4(temp_r0, 3);
    }
    temp_r0_2 = FIELD_AT(arg0, s32*, 0xC);
    if (temp_r0_2 != 0) {
        sub_8161C08(temp_r0_2, 3);
    }
    FIELD_AT(arg0, s32*, 4) = 0x08CDCA30;
    if (1 & arg1) {
        free_heap_8018DA8(arg0);
    }
}
