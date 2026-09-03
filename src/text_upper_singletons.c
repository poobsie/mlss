#include "global.h"

#define SEC(name) __attribute__((section(".text.text_upper_singletons." #name)))

SEC(sub_81251DC) s32 sub_81251DC(void) {
    return *(s32*)0x03000FFC + 0x1FF8;
}
