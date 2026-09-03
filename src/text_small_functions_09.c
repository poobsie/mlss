#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.small_functions_09." #name)))
extern UnknownWord sub_8100D18;
UnknownWord nullsub_4();
UnknownWord sub_8081E2C();
UnknownWord sub_80F75D8();

SEC(sub_8106E1C) void sub_8106E1C(void* arg0) {
    s32 temp_r4;
    void* temp_r1;

    temp_r1 = *(void**)0x03000FD8;
    if (FIELD_AT(temp_r1, s32*, 0x310) == 0) {
        temp_r4 = FIELD_AT(temp_r1, s32*, 0x7C);
        nullsub_4();
        sub_8081E2C(temp_r4 + 8);
        FIELD_AT(arg0, UnknownWord**, 4) = &sub_8100D18;
        sub_80F75D8(4);
    }
}
