#include "global.h"

#define SEC(name) __attribute__((section(".text.mariobros_helpers_late." #name)))

SEC(sub_8F591F8) void sub_8F591F8(void) {
    u8 row;

    for (row = 0; row <= 3; row++) {
        u8 column;
        u16* dst = (u16*)(0x0600EAD8 + row * 0x40);

        for (column = 0; column <= 6; column++)
            *dst++ = 0;
    }
}
