#include "common.h"
#include "runtime/functions.h"

void runtime_noop_interrupt_callback(void)
    __attribute__((section(".text.nullsub_16")));
void runtime_noop_interrupt_callback(void) {
}
__attribute__((section(".text.nullsub_16")))
const u16 nullsub_16_padding = 0;

void runtime_install_interrupt_callback(int interrupt, InterruptCallback callback)
    __attribute__((section(".text.sub_8018B78")));
void runtime_install_interrupt_callback(int interrupt, InterruptCallback callback) {
    int destination;
    int base;

    if (callback == NULL) {
        callback = runtime_noop_interrupt_callback;
    }

    REG_IME = 0;
    if (interrupt == 2) {
        destination = (int)&gGameState;
        base = 0x8C4;
    } else {
        base = 0x03000014;
        destination = interrupt * 4;
    }
    *(InterruptCallback*)(destination + base) = callback;
    REG_IME = 1;
}
