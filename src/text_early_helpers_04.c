#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.text_early_helpers_04." #name)))
UnknownWord sub_805BFF0();
UnknownWord sub_80494D4();
UnknownWord sub_804FCD4();

SEC(sub_80297B8) void sub_80297B8(void* arg0) {
    if (((s32)(FIELD_AT(arg0, u16*, 0xFC) << 0x15) >> 0x1C) == 0) {
        sub_805BFF0(FIELD_AT(arg0, s32*, 0x304));
    }
}

SEC(sub_803C638) void sub_803C638(void* arg0) {
    u16 temp_r2;
    void* temp_r1;

    temp_r1 = FIELD_AT(arg0, void**, 0x200);
    temp_r2 = FIELD_AT(temp_r1, u16*, 4);
    if ((u32)(u16)(temp_r2 - 5) <= 4U) {
        sub_804FCD4(temp_r1);
        return;
    }
    if ((u32)(u16)(temp_r2 - 0xA) <= 2U) {
        sub_80494D4(temp_r1);
    }
}
