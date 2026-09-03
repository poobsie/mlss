#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.small_functions_10." #name)))
extern UnknownWord sub_8100E5C;
s32 sub_8082B00();
UnknownWord sub_8095584();
UnknownWord sub_80F7068();
UnknownWord sub_80F75B4();

SEC(sub_8106E58) void sub_8106E58(void* arg0) {
    void* temp_r2;

    if ((sub_8082B00() << 0x18) == 0) {
        temp_r2 = *(void**)0x03000FD8;
        if (!(4 & FIELD_AT(temp_r2, u8*, 0xB))) {
            sub_8095584(FIELD_AT(temp_r2, s32*, 0x7C) + 8);
            sub_80F7068(FIELD_AT(*(void**)0x03000FD8, u8*, 0x349), -1);
            FIELD_AT(*(void**)0x03000FD8, u8*, 0x349) = 0xFFU;
            FIELD_AT(arg0, UnknownWord**, 4) = &sub_8100E5C;
            sub_80F75B4(8);
        }
    }
}
