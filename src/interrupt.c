#include "global.h"
#include "common.h"

void nullsub_16(void) {
}

void sub_8018B78(int interrupt, void (*callback)(void)) {
    int destination;
    int base;

    if (callback == NULL) {
        callback = nullsub_16;
    }

    REG_IME = 0;
    if (interrupt == 2) {
        destination = (int)&gGameState;
        base = 0x8C4;
    } else {
        base = 0x03000014;
        destination = interrupt * 4;
    }
    *(void (**)(void))(destination + base) = callback;
    REG_IME = 1;
}
