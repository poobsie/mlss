#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
#define SEC(name) __attribute__((section(".text.small_functions_11." #name)))
extern UnknownWord sub_8106E58;
UnknownWord sub_8081EAC();
UnknownWord sub_80F75D8();

SEC(sub_8106EB0) void sub_8106EB0(void* arg0) {
    void* temp_r1;

    temp_r1 = *(void**)0x03000FD8;
    if (FIELD_AT(temp_r1, s32*, 0x310) == 0) {
        sub_8081EAC(FIELD_AT(temp_r1, u8*, 0x349));
        FIELD_AT(arg0, UnknownWord**, 4) = &sub_8106E58;
        sub_80F75D8(4);
    }
}
